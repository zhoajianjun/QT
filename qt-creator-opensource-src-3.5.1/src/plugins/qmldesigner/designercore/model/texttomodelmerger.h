/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
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

#ifndef TEXTTOMODELMERGER_H
#define TEXTTOMODELMERGER_H

#include "qmldesignercorelib_global.h"
#include "import.h"
#include "nodelistproperty.h"
#include "modelnode.h"

#include <qmljs/qmljsscopechain.h>

#include <QStringList>
#include <QTimer>

namespace QmlDesigner {

class RewriterView;

namespace Internal {

class DifferenceHandler;
class ReadingContext;

class TextToModelMerger
{
    TextToModelMerger(const TextToModelMerger&);
    TextToModelMerger &operator=(const TextToModelMerger&);

public:
    TextToModelMerger(RewriterView *reWriterView);
    bool isActive() const;

    void setupImports(const QmlJS::Document::Ptr &doc, DifferenceHandler &differenceHandler);
    void setupPossibleImports(const QmlJS::Snapshot &snapshot, const QmlJS::ViewerContext &viewContext);
    void setupUsedImports();
    bool load(const QString &data, DifferenceHandler &differenceHandler);

    RewriterView *view() const
    { return m_rewriterView; }

    const QmlJS::ScopeChain *scopeChain() const
    { return m_scopeChain.data(); }

    const QmlJS::Document *document() const
    { return m_document.data(); }

    const QmlJS::ViewerContext &vContext() const
    { return m_vContext; }

protected:
    void setActive(bool active);

public:
    void syncNode(ModelNode &modelNode,
                  QmlJS::AST::UiObjectMember *astNode,
                  ReadingContext *context,
                  DifferenceHandler &differenceHandler);
    QmlDesigner::PropertyName syncScriptBinding(ModelNode &modelNode,
                              const QString &prefix,
                              QmlJS::AST::UiScriptBinding *script,
                              ReadingContext *context,
                              DifferenceHandler &differenceHandler);
    void syncNodeId(ModelNode &modelNode, const QString &astObjectId,
                    DifferenceHandler &differenceHandler);
    void syncNodeProperty(AbstractProperty &modelProperty,
                          QmlJS::AST::UiObjectBinding *binding,
                          ReadingContext *context,
                          DifferenceHandler &differenceHandler);
    void syncExpressionProperty(AbstractProperty &modelProperty,
                                const QString &javascript,
                                const TypeName &astType,
                                DifferenceHandler &differenceHandler);
    void syncSignalHandler(AbstractProperty &modelProperty,
                           const QString &javascript,
                           DifferenceHandler &differenceHandler);
    void syncArrayProperty(AbstractProperty &modelProperty,
                           const QList<QmlJS::AST::UiObjectMember *> &arrayMembers,
                           ReadingContext *context,
                           DifferenceHandler &differenceHandler);
    void syncVariantProperty(AbstractProperty &modelProperty,
                             const QVariant &astValue,
                             const TypeName &astType,
                             DifferenceHandler &differenceHandler);
    void syncNodeListProperty(NodeListProperty &modelListProperty,
                              const QList<QmlJS::AST::UiObjectMember *> arrayMembers,
                              ReadingContext *context,
                              DifferenceHandler &differenceHandler);
    ModelNode createModelNode(const TypeName &typeName,
                              int majorVersion,
                              int minorVersion,
                              bool isImplicitComponent,
                              QmlJS::AST::UiObjectMember *astNode,
                              ReadingContext *context,
                              DifferenceHandler &differenceHandler);
    QStringList syncGroupedProperties(ModelNode &modelNode,
                                      const QString &name,
                                      QmlJS::AST::UiObjectMemberList *members,
                                      ReadingContext *context,
                                      DifferenceHandler &differenceHandler);

    void setupComponentDelayed(const ModelNode &node, bool synchron);
    void setupCustomParserNodeDelayed(const ModelNode &node, bool synchron);

    void delayedSetup();
private:
    void setupCustomParserNode(const ModelNode &node);
    void setupComponent(const ModelNode &node);

    static QString textAt(const QmlJS::Document::Ptr &doc,
                          const QmlJS::AST::SourceLocation &location);
    static QString textAt(const QmlJS::Document::Ptr &doc,
                          const QmlJS::AST::SourceLocation &from,
                          const QmlJS::AST::SourceLocation &to);

private:
    RewriterView *m_rewriterView;
    bool m_isActive;
    QSharedPointer<const QmlJS::ScopeChain> m_scopeChain;
    QmlJS::Document::Ptr m_document;
    QTimer m_setupTimer;
    QSet<ModelNode> m_setupComponentList;
    QSet<ModelNode> m_setupCustomParserList;
    QmlJS::ViewerContext m_vContext;
};

class DifferenceHandler
{
public:
    DifferenceHandler(TextToModelMerger *textToModelMerger):
            m_merger(textToModelMerger)
    {}
    virtual ~DifferenceHandler()
    {}

    virtual void modelMissesImport(const QmlDesigner::Import &import) = 0;
    virtual void importAbsentInQMl(const QmlDesigner::Import &import) = 0;
    virtual void bindingExpressionsDiffer(BindingProperty &modelProperty,
                                          const QString &javascript,
                                          const TypeName &astType) = 0;
    virtual void signalHandlerSourceDiffer(SignalHandlerProperty &modelProperty,
                                          const QString &javascript) = 0;
    virtual void shouldBeBindingProperty(AbstractProperty &modelProperty,
                                         const QString &javascript,
                                         const TypeName &astType) = 0;
    virtual void shouldBeSignalHandlerProperty(AbstractProperty &modelProperty,
                                         const QString &javascript) = 0;
    virtual void shouldBeNodeListProperty(AbstractProperty &modelProperty,
                                          const QList<QmlJS::AST::UiObjectMember *> arrayMembers,
                                          ReadingContext *context) = 0;
    virtual void variantValuesDiffer(VariantProperty &modelProperty, const QVariant &qmlVariantValue, const TypeName &dynamicTypeName) = 0;
    virtual void shouldBeVariantProperty(AbstractProperty &modelProperty, const QVariant &qmlVariantValue, const TypeName &dynamicTypeName) = 0;
    virtual void shouldBeNodeProperty(AbstractProperty &modelProperty,
                                      const TypeName &typeName,
                                      int majorVersion,
                                      int minorVersion,
                                      QmlJS::AST::UiObjectMember *astNode,
                                      ReadingContext *context) = 0;
    virtual void modelNodeAbsentFromQml(ModelNode &modelNode) = 0;
    virtual ModelNode listPropertyMissingModelNode(NodeListProperty &modelProperty,
                                                   ReadingContext *context,
                                                   QmlJS::AST::UiObjectMember *arrayMember) = 0;
    virtual void typeDiffers(bool isRootNode,
                             ModelNode &modelNode,
                             const TypeName &typeName,
                             int majorVersion,
                             int minorVersion,
                             QmlJS::AST::UiObjectMember *astNode,
                             ReadingContext *context) = 0;
    virtual void propertyAbsentFromQml(AbstractProperty &modelProperty) = 0;
    virtual void idsDiffer(ModelNode &modelNode, const QString &qmlId) = 0;
    virtual bool isValidator() const = 0;

protected:
    TextToModelMerger *m_merger;
};

class ModelValidator: public DifferenceHandler
{
public:
    ModelValidator(TextToModelMerger *textToModelMerger):
            DifferenceHandler(textToModelMerger)
    {}
    ~ModelValidator()
    {}

    virtual void modelMissesImport(const QmlDesigner::Import &import);
    virtual void importAbsentInQMl(const QmlDesigner::Import &import);
    virtual void bindingExpressionsDiffer(BindingProperty &modelProperty,
                                          const QString &javascript,
                                          const TypeName &astType);
    virtual void shouldBeBindingProperty(AbstractProperty &modelProperty,
                                         const QString &javascript,
                                         const TypeName &astType);
    virtual void signalHandlerSourceDiffer(SignalHandlerProperty &modelProperty,
                                          const QString &javascript);
    virtual void shouldBeSignalHandlerProperty(AbstractProperty &modelProperty,
                                         const QString &javascript);
    virtual void shouldBeNodeListProperty(AbstractProperty &modelProperty,
                                          const QList<QmlJS::AST::UiObjectMember *> arrayMembers,
                                          ReadingContext *context);
    virtual void variantValuesDiffer(VariantProperty &modelProperty, const QVariant &qmlVariantValue, const TypeName &dynamicTypeName);
    virtual void shouldBeVariantProperty(AbstractProperty &modelProperty, const QVariant &qmlVariantValue, const TypeName &dynamicTypeName);
    virtual void shouldBeNodeProperty(AbstractProperty &modelProperty,
                                      const TypeName &typeName,
                                      int majorVersion,
                                      int minorVersion,
                                      QmlJS::AST::UiObjectMember *astNode,
                                      ReadingContext *context);
    virtual void modelNodeAbsentFromQml(ModelNode &modelNode);
    virtual ModelNode listPropertyMissingModelNode(NodeListProperty &modelProperty,
                                                   ReadingContext *context,
                                                   QmlJS::AST::UiObjectMember *arrayMember);
    virtual void typeDiffers(bool isRootNode,
                             ModelNode &modelNode,
                             const TypeName &typeName,
                             int majorVersion,
                             int minorVersion,
                             QmlJS::AST::UiObjectMember *astNode,
                             ReadingContext *context);
    virtual void propertyAbsentFromQml(AbstractProperty &modelProperty);
    virtual void idsDiffer(ModelNode &modelNode, const QString &qmlId);
    virtual bool isValidator() const {return false; }
};

class ModelAmender: public DifferenceHandler
{
public:
    ModelAmender(TextToModelMerger *textToModelMerger):
            DifferenceHandler(textToModelMerger)
    {}
    ~ModelAmender()
    {}

    virtual void modelMissesImport(const QmlDesigner::Import &import);
    virtual void importAbsentInQMl(const QmlDesigner::Import &import);
    virtual void bindingExpressionsDiffer(BindingProperty &modelProperty,
                                          const QString &javascript,
                                          const TypeName &astType);
    virtual void shouldBeBindingProperty(AbstractProperty &modelProperty,
                                         const QString &javascript,
                                         const TypeName &astType);
    virtual void signalHandlerSourceDiffer(SignalHandlerProperty &modelProperty,
                                          const QString &javascript);
    virtual void shouldBeSignalHandlerProperty(AbstractProperty &modelProperty,
                                         const QString &javascript);
    virtual void shouldBeNodeListProperty(AbstractProperty &modelProperty,
                                          const QList<QmlJS::AST::UiObjectMember *> arrayMembers,
                                          ReadingContext *context);
    virtual void variantValuesDiffer(VariantProperty &modelProperty, const QVariant &qmlVariantValue, const TypeName &dynamicType);
    virtual void shouldBeVariantProperty(AbstractProperty &modelProperty, const QVariant &qmlVariantValue, const TypeName &dynamicTypeName);
    virtual void shouldBeNodeProperty(AbstractProperty &modelProperty,
                                      const TypeName &typeName,
                                      int majorVersion,
                                      int minorVersion,
                                      QmlJS::AST::UiObjectMember *astNode,
                                      ReadingContext *context);
    virtual void modelNodeAbsentFromQml(ModelNode &modelNode);
    virtual ModelNode listPropertyMissingModelNode(NodeListProperty &modelProperty,
                                                   ReadingContext *context,
                                                   QmlJS::AST::UiObjectMember *arrayMember);
    virtual void typeDiffers(bool isRootNode,
                             ModelNode &modelNode,
                             const TypeName &typeName,
                             int majorVersion,
                             int minorVersion,
                             QmlJS::AST::UiObjectMember *astNode,
                             ReadingContext *context);
    virtual void propertyAbsentFromQml(AbstractProperty &modelProperty);
    virtual void idsDiffer(ModelNode &modelNode, const QString &qmlId);
    virtual bool isValidator() const {return true; }
};

} //Internal
} //QmlDesigner

#endif // TEXTTOMODELMERGER_H
