/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of the Qt Build Suite.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms and
** conditions see http://www.qt.io/terms-conditions. For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/
#include "rulesapplicator.h"

#include "artifact.h"
#include "buildgraph.h"
#include "emptydirectoriesremover.h"
#include "productbuilddata.h"
#include "projectbuilddata.h"
#include "qtmocscanner.h"
#include "rulesevaluationcontext.h"
#include "transformer.h"

#include <jsextensions/moduleproperties.h>
#include <language/artifactproperties.h>
#include <language/builtindeclarations.h>
#include <language/language.h>
#include <language/preparescriptobserver.h>
#include <language/propertymapinternal.h>
#include <language/scriptengine.h>
#include <logging/translator.h>
#include <tools/error.h>
#include <tools/fileinfo.h>
#include <tools/scripttools.h>
#include <tools/qbsassert.h>

#include <QDir>
#include <QQueue>
#include <QScriptValueIterator>

namespace qbs {
namespace Internal {

RulesApplicator::RulesApplicator(const ResolvedProductPtr &product, const Logger &logger)
    : m_product(product)
    , m_mocScanner(0)
    , m_logger(logger)
{
}

RulesApplicator::~RulesApplicator()
{
    delete m_mocScanner;
}

void RulesApplicator::applyRuleInEvaluationContext(const RuleConstPtr &rule,
        const ArtifactSet &inputArtifacts)
{
    m_createdArtifacts.clear();
    m_invalidatedArtifacts.clear();
    RulesEvaluationContext::Scope s(m_product->topLevelProject()->buildData->evaluationContext.data());
    applyRule(rule, inputArtifacts);
}

void RulesApplicator::applyRule(const RuleConstPtr &rule, const ArtifactSet &inputArtifacts)
{
    if (inputArtifacts.isEmpty())
        return;

    m_rule = rule;
    m_completeInputSet = inputArtifacts;
    if (rule->name == QLatin1String("QtCoreMocRule")) {
        delete m_mocScanner;
        m_mocScanner = new QtMocScanner(m_product, scope(), m_logger);
    }
    QScriptValue prepareScriptContext = engine()->newObject();
    PrepareScriptObserver observer(engine());
    setupScriptEngineForFile(engine(), m_rule->prepareScript->fileContext, scope());
    setupScriptEngineForProduct(engine(), m_product, m_rule->module, prepareScriptContext, &observer);

    if (m_rule->multiplex) { // apply the rule once for a set of inputs
        doApply(inputArtifacts, prepareScriptContext);
    } else { // apply the rule once for each input
        foreach (Artifact * const inputArtifact, inputArtifacts) {
            ArtifactSet lst;
            lst += inputArtifact;
            doApply(lst, prepareScriptContext);
        }
    }
}

void RulesApplicator::handleRemovedRuleOutputs(const ArtifactSet &inputArtifacts,
        ArtifactSet outputArtifactsToRemove, const Logger &logger)
{
    ArtifactSet artifactsToRemove;
    const TopLevelProject *project = 0;
    foreach (Artifact *removedArtifact, outputArtifactsToRemove) {
        if (logger.traceEnabled()) {
            logger.qbsTrace() << "[BG] dynamic rule removed output artifact "
                                << removedArtifact->toString();
        }
        if (!project)
            project = removedArtifact->product->topLevelProject();
        project->buildData->removeArtifactAndExclusiveDependents(removedArtifact, logger, true,
                                                                 &artifactsToRemove);
    }
    // parents of removed artifacts must update their transformers
    foreach (Artifact *removedArtifact, artifactsToRemove) {
        foreach (Artifact *parent, removedArtifact->parentArtifacts())
            parent->product->registerArtifactWithChangedInputs(parent);
    }
    EmptyDirectoriesRemover(project, logger).removeEmptyParentDirectories(artifactsToRemove);
    foreach (Artifact *artifact, artifactsToRemove) {
        QBS_CHECK(!inputArtifacts.contains(artifact));
        delete artifact;
    }
}

static void copyProperty(const QString &name, const QScriptValue &src, QScriptValue dst)
{
    dst.setProperty(name, src.property(name));
}

static QStringList toStringList(const ArtifactSet &artifacts)
{
    QStringList lst;
    foreach (const Artifact *artifact, artifacts) {
        const QString str = artifact->filePath() + QLatin1String(" [")
                + artifact->fileTags().toStringList().join(QLatin1String(", ")) + QLatin1Char(']');
        lst << str;
    }
    return lst;
}

void RulesApplicator::doApply(const ArtifactSet &inputArtifacts, QScriptValue &prepareScriptContext)
{
    evalContext()->checkForCancelation();

    if (m_logger.debugEnabled()) {
        m_logger.qbsDebug() << QString::fromLatin1("[BG] apply rule ") << m_rule->toString()
                            << QString::fromLatin1(" ")
                            << toStringList(inputArtifacts).join(QLatin1String(",\n            "));
    }

    QList<QPair<const RuleArtifact *, Artifact *> > ruleArtifactArtifactMap;
    QList<Artifact *> outputArtifacts;

    m_transformer = Transformer::create();
    m_transformer->rule = m_rule;
    m_transformer->inputs = inputArtifacts;

    // create the output artifacts from the set of input artifacts
    Transformer::setupInputs(prepareScriptContext, inputArtifacts, m_rule->module->name);
    copyProperty(QLatin1String("inputs"), prepareScriptContext, scope());
    copyProperty(QLatin1String("input"), prepareScriptContext, scope());
    copyProperty(QLatin1String("product"), prepareScriptContext, scope());
    copyProperty(QLatin1String("project"), prepareScriptContext, scope());
    if (m_rule->isDynamic()) {
        outputArtifacts = runOutputArtifactsScript(inputArtifacts,
                    ScriptEngine::argumentList(m_rule->outputArtifactsScript->argumentNames,
                                               scope()));
        ArtifactSet newOutputs = ArtifactSet::fromNodeList(outputArtifacts);
        const ArtifactSet oldOutputs = collectOldOutputArtifacts(inputArtifacts);
        handleRemovedRuleOutputs(m_completeInputSet, oldOutputs - newOutputs, m_logger);
    } else {
        QSet<QString> outputFilePaths;
        foreach (const RuleArtifactConstPtr &ruleArtifact, m_rule->artifacts) {
            Artifact * const outputArtifact
                    = createOutputArtifactFromRuleArtifact(ruleArtifact, inputArtifacts,
                                                           &outputFilePaths);
            if (!outputArtifact)
                continue;
            outputArtifacts << outputArtifact;
            ruleArtifactArtifactMap << qMakePair(ruleArtifact.data(), outputArtifact);
        }
    }

    if (outputArtifacts.isEmpty())
        return;

    foreach (Artifact *outputArtifact, outputArtifacts) {
        // connect artifacts that match the file tags in explicitlyDependsOn
        foreach (const FileTag &fileTag, m_rule->explicitlyDependsOn)
            foreach (Artifact *dependency, m_product->lookupArtifactsByFileTag(fileTag))
                loggedConnect(outputArtifact, dependency, m_logger);

        outputArtifact->product->unregisterArtifactWithChangedInputs(outputArtifact);
    }

    if (inputArtifacts != m_transformer->inputs)
        m_transformer->setupInputs(prepareScriptContext);

    // change the transformer outputs according to the bindings in Artifact
    QScriptValue scriptValue;
    if (!ruleArtifactArtifactMap.isEmpty())
        engine()->currentContext()->pushScope(prepareScriptContext);
    for (int i = ruleArtifactArtifactMap.count(); --i >= 0;) {
        const RuleArtifact *ra = ruleArtifactArtifactMap.at(i).first;
        if (ra->bindings.isEmpty())
            continue;

        // expose attributes of this artifact
        Artifact *outputArtifact = ruleArtifactArtifactMap.at(i).second;
        outputArtifact->properties = outputArtifact->properties->clone();

        scope().setProperty(QLatin1String("fileName"),
                            engine()->toScriptValue(outputArtifact->filePath()));
        scope().setProperty(QLatin1String("fileTags"),
                            toScriptValue(engine(), outputArtifact->fileTags().toStringList()));

        QVariantMap artifactModulesCfg = outputArtifact->properties->value()
                .value(QLatin1String("modules")).toMap();
        for (int i=0; i < ra->bindings.count(); ++i) {
            const RuleArtifact::Binding &binding = ra->bindings.at(i);
            scriptValue = engine()->evaluate(binding.code);
            if (Q_UNLIKELY(engine()->hasErrorOrException(scriptValue))) {
                QString msg = QLatin1String("evaluating rule binding '%1': %2");
                throw ErrorInfo(msg.arg(binding.name.join(QLatin1Char('.')),
                                        engine()->lastErrorString(scriptValue)), binding.location);
            }
            setConfigProperty(artifactModulesCfg, binding.name, scriptValue.toVariant());
        }
        QVariantMap outputArtifactConfig = outputArtifact->properties->value();
        outputArtifactConfig.insert(QLatin1String("modules"), artifactModulesCfg);
        outputArtifact->properties->setValue(outputArtifactConfig);
    }
    if (!ruleArtifactArtifactMap.isEmpty())
        engine()->currentContext()->popScope();

    m_transformer->setupOutputs(engine(), prepareScriptContext);
    m_transformer->createCommands(m_rule->prepareScript, evalContext(),
            ScriptEngine::argumentList(m_rule->prepareScript->argumentNames, prepareScriptContext));
    if (Q_UNLIKELY(m_transformer->commands.isEmpty()))
        throw ErrorInfo(Tr::tr("There is a rule without commands: %1.")
                        .arg(m_rule->toString()), m_rule->prepareScript->location);
}

ArtifactSet RulesApplicator::collectOldOutputArtifacts(const ArtifactSet &inputArtifacts) const
{
    ArtifactSet result;
    foreach (Artifact *a, inputArtifacts) {
        foreach (Artifact *p, a->parentArtifacts()) {
            QBS_CHECK(p->transformer);
            if (p->transformer->rule == m_rule && p->transformer->inputs.contains(a))
                result += p;
        }
    }
    return result;
}

Artifact *RulesApplicator::createOutputArtifactFromRuleArtifact(
        const RuleArtifactConstPtr &ruleArtifact, const ArtifactSet &inputArtifacts,
        QSet<QString> *outputFilePaths)
{
    QScriptValue scriptValue = engine()->evaluate(ruleArtifact->filePath);
    if (Q_UNLIKELY(engine()->hasErrorOrException(scriptValue))) {
        throw ErrorInfo(Tr::tr("Error in Rule.Artifact fileName at %1: %2")
                        .arg(ruleArtifact->location.toString(),
                             engine()->lastErrorString(scriptValue)));
    }
    QString outputPath = FileInfo::resolvePath(m_product->buildDirectory(), scriptValue.toString());
    if (Q_UNLIKELY(outputFilePaths->contains(outputPath))) {
        throw ErrorInfo(Tr::tr("Rule %1 already created '%2'.")
                        .arg(m_rule->toString(), outputPath));
    }
    outputFilePaths->insert(outputPath);
    return createOutputArtifact(outputPath, ruleArtifact->fileTags, ruleArtifact->alwaysUpdated,
                                inputArtifacts);
}

Artifact *RulesApplicator::createOutputArtifact(const QString &filePath, const FileTags &fileTags,
        bool alwaysUpdated, const ArtifactSet &inputArtifacts)
{
    QString outputPath = filePath;
    // don't let the output artifact "escape" its build dir
    outputPath.replace(QLatin1String(".."), QLatin1String("dotdot"));
    outputPath = resolveOutPath(outputPath);

    Artifact *outputArtifact = lookupArtifact(m_product, outputPath);
    if (outputArtifact) {
        if (outputArtifact->transformer && outputArtifact->transformer->rule != m_rule) {
            QString e = Tr::tr("Conflicting rules for producing %1 %2 \n")
                    .arg(outputArtifact->filePath(),
                         QLatin1Char('[') +
                         outputArtifact->fileTags().toStringList().join(QLatin1String(", "))
                         + QLatin1Char(']'));
            QString str = QLatin1Char('[') + m_rule->inputs.toStringList().join(QLatin1String(", "))
               + QLatin1String("] -> [") + outputArtifact->fileTags().toStringList()
                    .join(QLatin1String(", ")) + QLatin1Char(']');

            e += QString::fromLatin1("  while trying to apply:   %1:%2:%3  %4\n")
                .arg(m_rule->prepareScript->location.filePath())
                .arg(m_rule->prepareScript->location.line())
                .arg(m_rule->prepareScript->location.column())
                .arg(str);

            e += QString::fromLatin1("  was already defined in:  %1:%2:%3  %4\n")
                .arg(outputArtifact->transformer->rule->prepareScript->location.filePath())
                .arg(outputArtifact->transformer->rule->prepareScript->location.line())
                .arg(outputArtifact->transformer->rule->prepareScript->location.column())
                .arg(str);

            throw ErrorInfo(e);
        }
        outputArtifact->clearTimestamp();
        m_invalidatedArtifacts += outputArtifact;
    } else {
        outputArtifact = new Artifact;
        outputArtifact->artifactType = Artifact::Generated;
        outputArtifact->setFilePath(outputPath);
        insertArtifact(m_product, outputArtifact, m_logger);
        m_createdArtifacts += outputArtifact;
    }

    outputArtifact->setFileTags(
                fileTags.isEmpty() ? m_product->fileTagsForFileName(outputArtifact->fileName())
                                   : fileTags);
    outputArtifact->alwaysUpdated = alwaysUpdated;
    outputArtifact->properties = m_product->moduleProperties;

    for (int i = 0; i < m_product->artifactProperties.count(); ++i) {
        const ArtifactPropertiesConstPtr &props = m_product->artifactProperties.at(i);
        if (outputArtifact->fileTags().matches(props->fileTagsFilter())) {
            outputArtifact->properties = props->propertyMap();
            break;
        }
    }

    // Let a positive value of qbs.install imply the file tag "installable".
    if (outputArtifact->properties->qbsPropertyValue(QLatin1String("install")).toBool())
        outputArtifact->addFileTag("installable");

    foreach (Artifact *inputArtifact, inputArtifacts) {
        QBS_CHECK(outputArtifact != inputArtifact);
        loggedConnect(outputArtifact, inputArtifact, m_logger);
    }

    outputArtifact->transformer = m_transformer;
    m_transformer->outputs.insert(outputArtifact);
    QBS_CHECK(m_rule->multiplex || m_transformer->inputs.count() == 1);

    return outputArtifact;
}

QList<Artifact *> RulesApplicator::runOutputArtifactsScript(const ArtifactSet &inputArtifacts,
        const QScriptValueList &args)
{
    QList<Artifact *> lst;
    QScriptValue fun = engine()->evaluate(m_rule->outputArtifactsScript->sourceCode);
    if (!fun.isFunction())
        throw ErrorInfo(QLatin1String("Function expected."),
                        m_rule->outputArtifactsScript->location);
    QScriptValue res = fun.call(QScriptValue(), args);
    if (res.isError() || engine()->hasUncaughtException())
        throw ErrorInfo(Tr::tr("Error while calling Rule.outputArtifacts: %1").arg(res.toString()),
                        m_rule->outputArtifactsScript->location);
    if (!res.isArray())
        throw ErrorInfo(Tr::tr("Rule.outputArtifacts must return an array of objects."),
                        m_rule->outputArtifactsScript->location);
    const quint32 c = res.property(QLatin1String("length")).toUInt32();
    for (quint32 i = 0; i < c; ++i)
        lst += createOutputArtifactFromScriptValue(res.property(i), inputArtifacts);
    return lst;
}

class ArtifactBindingsExtractor
{
    typedef QPair<QStringList, QVariant> NameValuePair;
    QList<NameValuePair> m_propertyValues;

    static QSet<QString> getArtifactItemPropertyNames()
    {
        QSet<QString> s;
        foreach (const PropertyDeclaration &pd,
                 BuiltinDeclarations::instance().declarationsForType(
                     QLatin1String("Artifact")).properties()) {
            s.insert(pd.name());
        }
        s.insert(QLatin1String("explicitlyDependsOn"));
        return s;
    }

    void extractPropertyValues(const QScriptValue &obj, QStringList fullName = QStringList())
    {
        QScriptValueIterator svit(obj);
        while (svit.hasNext()) {
            svit.next();
            const QString name = svit.name();
            if (fullName.isEmpty()) {
                // Ignore property names that are part of the Artifact item.
                static const QSet<QString> artifactItemPropertyNames
                        = getArtifactItemPropertyNames();
                if (artifactItemPropertyNames.contains(name))
                    continue;
            }

            const QScriptValue value = svit.value();
            fullName.append(name);
            if (value.isObject() && !value.isArray() && !value.isError() && !value.isRegExp())
                extractPropertyValues(value, fullName);
            else
                m_propertyValues.append(NameValuePair(fullName, value.toVariant()));
            fullName.removeLast();
        }
    }
public:
    ArtifactBindingsExtractor()
    {
    }

    void apply(Artifact *outputArtifact, const QScriptValue &obj)
    {
        extractPropertyValues(obj);
        if (m_propertyValues.isEmpty())
            return;

        outputArtifact->properties = outputArtifact->properties->clone();
        QVariantMap artifactCfg = outputArtifact->properties->value();
        foreach (const NameValuePair &nvp, m_propertyValues) {
            const QStringList valuePath = findValuePath(artifactCfg, nvp.first);
            if (valuePath.isEmpty()) {
                throw ErrorInfo(Tr::tr("Cannot set module property %1 on artifact %2.")
                                .arg(nvp.first.join(QLatin1Char('.')),
                                     outputArtifact->filePath()));
            }
            setConfigProperty(artifactCfg, valuePath, nvp.second);
        }
        outputArtifact->properties->setValue(artifactCfg);
    }

    QStringList findValuePath(const QVariantMap &cfg, const QStringList &nameParts)
    {
        QStringList tmp = nameParts;
        const QString propertyName = tmp.takeLast();
        const QString moduleName = tmp.join(QLatin1Char('.'));
        const QStringList modulePath = findModulePath(cfg, moduleName);
        if (modulePath.isEmpty())
            return modulePath;
        return QStringList(modulePath) << propertyName;
    }

    QStringList findModulePath(const QVariantMap &cfg, const QString &moduleName)
    {
        typedef QPair<QVariantMap, QStringList> MapAndPath;
        QQueue<MapAndPath> q;
        q.enqueue(MapAndPath(cfg.value(QLatin1String("modules")).toMap(),
                             QStringList(QLatin1String("modules"))));
        do {
            const MapAndPath current = q.takeFirst();
            const QVariantMap &mod = current.first;
            for (QVariantMap::const_iterator it = mod.constBegin(); it != mod.constEnd(); ++it) {
                const QVariantMap m = it.value().toMap();
                const QStringList currentPath = QStringList(current.second) << it.key();
                if (it.key() == moduleName)
                    return currentPath;
                q.enqueue(MapAndPath(m.value(QLatin1String("modules")).toMap(),
                                     QStringList(currentPath) << QLatin1String("modules")));
            }
        } while (!q.isEmpty());
        return QStringList();
    }
};

Artifact *RulesApplicator::createOutputArtifactFromScriptValue(const QScriptValue &obj,
        const ArtifactSet &inputArtifacts)
{
    if (!obj.isObject()) {
        throw ErrorInfo(Tr::tr("Elements of the Rule.outputArtifacts array must be "
                               "of Object type."), m_rule->outputArtifactsScript->location);
    }
    const QString filePath = FileInfo::resolvePath(m_product->buildDirectory(),
            obj.property(QLatin1String("filePath")).toVariant().toString());
    const FileTags fileTags = FileTags::fromStringList(
                obj.property(QLatin1String("fileTags")).toVariant().toStringList());
    const QVariant alwaysUpdatedVar = obj.property(QLatin1String("alwaysUpdated")).toVariant();
    const bool alwaysUpdated = alwaysUpdatedVar.isValid() ? alwaysUpdatedVar.toBool() : true;
    Artifact *output = createOutputArtifact(filePath, fileTags, alwaysUpdated, inputArtifacts);
    const FileTags explicitlyDependsOn = FileTags::fromStringList(
                obj.property(QLatin1String("explicitlyDependsOn")).toVariant().toStringList());
    foreach (const FileTag &tag, explicitlyDependsOn) {
        foreach (Artifact *dependency, m_product->lookupArtifactsByFileTag(tag)) {
            loggedConnect(output, dependency, m_logger);
        }
    }
    ArtifactBindingsExtractor().apply(output, obj);
    return output;
}

QString RulesApplicator::resolveOutPath(const QString &path) const
{
    QString buildDir = m_product->topLevelProject()->buildDirectory;
    QString result = FileInfo::resolvePath(buildDir, path);
    result = QDir::cleanPath(result);
    return result;
}

RulesEvaluationContextPtr RulesApplicator::evalContext() const
{
    return m_product->topLevelProject()->buildData->evaluationContext;
}

ScriptEngine *RulesApplicator::engine() const
{
    return evalContext()->engine();
}

QScriptValue RulesApplicator::scope() const
{
    return evalContext()->scope();
}

} // namespace Internal
} // namespace qbs
