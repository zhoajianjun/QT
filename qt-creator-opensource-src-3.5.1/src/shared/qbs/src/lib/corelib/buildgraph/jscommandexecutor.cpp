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

#include "jscommandexecutor.h"

#include "artifact.h"
#include "buildgraph.h"
#include "command.h"
#include "transformer.h"

#include <language/language.h>
#include <language/preparescriptobserver.h>
#include <language/scriptengine.h>
#include <logging/logger.h>
#include <tools/codelocation.h>
#include <tools/error.h>
#include <tools/qbsassert.h>

#include <QEventLoop>
#include <QMetaObject>
#include <QThread>
#include <QTimer>

namespace qbs {
namespace Internal {

struct JavaScriptCommandResult
{
    bool success;
    QString errorMessage;
    CodeLocation errorLocation;
};

class JsCommandExecutorThreadObject : public QObject
{
    Q_OBJECT
public:
    JsCommandExecutorThreadObject(const Logger &logger)
        : m_logger(logger)
        , m_scriptEngine(0)
    {
    }

    const JavaScriptCommandResult &result() const
    {
        return m_result;
    }

    Q_INVOKABLE void cancel()
    {
        QBS_ASSERT(m_scriptEngine, return);
        m_scriptEngine->abortEvaluation();
    }

signals:
    void finished();

public slots:
    void start(const JavaScriptCommand *cmd, Transformer *transformer)
    {
        try {
            doStart(cmd, transformer);
        } catch (const qbs::ErrorInfo &error) {
            setError(error.toString(), cmd->codeLocation());
        }

        emit finished();
    }

private:
    void doStart(const JavaScriptCommand *cmd, Transformer *transformer)
    {
        m_result.success = true;
        m_result.errorMessage.clear();
        ScriptEngine * const scriptEngine = provideScriptEngine();
        QScriptValue scope = scriptEngine->newObject();
        PrepareScriptObserver observer(scriptEngine);
        setupScriptEngineForFile(scriptEngine, transformer->rule->prepareScript->fileContext, scope);
        setupScriptEngineForProduct(scriptEngine, transformer->product(), transformer->rule->module, scope,
                                    &observer);
        transformer->setupInputs(scope);
        transformer->setupOutputs(scriptEngine, scope);

        for (QVariantMap::const_iterator it = cmd->properties().constBegin();
                it != cmd->properties().constEnd(); ++it) {
            scope.setProperty(it.key(), scriptEngine->toScriptValue(it.value()));
        }

        QScriptContext *ctx = scriptEngine->currentContext();
        ctx->pushScope(scope);
        scriptEngine->evaluate(cmd->sourceCode());
        ctx->popScope();
        transformer->propertiesRequestedInCommands
                += scriptEngine->propertiesRequestedInScript();
        scriptEngine->clearRequestedProperties();
        if (scriptEngine->hasUncaughtException()) {
            // ### We don't know the line number of the command's sourceCode property assignment.
            setError(scriptEngine->uncaughtException().toString(), cmd->codeLocation());
        }
    }

    void setError(const QString &errorMessage, const CodeLocation &codeLocation)
    {
        m_result.success = false;
        m_result.errorMessage = errorMessage;
        m_result.errorLocation = codeLocation;
    }

    ScriptEngine *provideScriptEngine()
    {
        if (!m_scriptEngine)
            m_scriptEngine = new ScriptEngine(m_logger, this);
        return m_scriptEngine;
    }

    Logger m_logger;
    ScriptEngine *m_scriptEngine;
    JavaScriptCommandResult m_result;
};


JsCommandExecutor::JsCommandExecutor(const Logger &logger, QObject *parent)
    : AbstractCommandExecutor(logger, parent)
    , m_thread(new QThread(this))
    , m_objectInThread(new JsCommandExecutorThreadObject(logger))
    , m_running(false)
{
    m_objectInThread->moveToThread(m_thread);
    connect(m_objectInThread, SIGNAL(finished()), this, SLOT(onJavaScriptCommandFinished()));
    connect(this, SIGNAL(startRequested(const JavaScriptCommand*,Transformer*)),
            m_objectInThread, SLOT(start(const JavaScriptCommand*,Transformer*)));
}

JsCommandExecutor::~JsCommandExecutor()
{
    waitForFinished();
    delete m_objectInThread;
    m_thread->quit();
    m_thread->wait();
}

void JsCommandExecutor::waitForFinished()
{
    if (!m_running)
        return;
    QEventLoop loop;
    loop.connect(m_objectInThread, SIGNAL(finished()), SLOT(quit()));
    loop.exec();
}

void JsCommandExecutor::doStart()
{
    QBS_ASSERT(!m_running, return);
    m_thread->start();

    if (dryRun()) {
        QTimer::singleShot(0, this, SIGNAL(finished())); // Don't call back on the caller.
        return;
    }

    m_running = true;
    emit startRequested(jsCommand(), transformer());
}

void JsCommandExecutor::cancel()
{
    if (!dryRun())
        QMetaObject::invokeMethod(m_objectInThread, "cancel", Qt::QueuedConnection);
}

void JsCommandExecutor::onJavaScriptCommandFinished()
{
    m_running = false;
    const JavaScriptCommandResult &result = m_objectInThread->result();
    ErrorInfo err;
    if (!result.success) {
        logger().qbsDebug() << "JS context:\n" << jsCommand()->properties();
        logger().qbsDebug() << "JS code:\n" << jsCommand()->sourceCode();
        err.append(tr("Error while executing JavaScriptCommand:"), result.errorLocation);
        err.append(result.errorMessage);
    }
    emit finished(err);
}

const JavaScriptCommand *JsCommandExecutor::jsCommand() const
{
    return static_cast<const JavaScriptCommand *>(command());
}

} // namespace Internal
} // namespace qbs

#include "jscommandexecutor.moc"
