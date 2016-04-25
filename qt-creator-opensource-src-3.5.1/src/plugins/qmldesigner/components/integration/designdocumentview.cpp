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

#include "designdocumentview.h"
#include <rewriterview.h>
#include <basetexteditmodifier.h>

#include <QApplication>
#include <QPlainTextEdit>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>

namespace QmlDesigner {

DesignDocumentView::DesignDocumentView(QObject *parent)
    : AbstractView(parent), m_modelMerger(this)
{
}

DesignDocumentView::~DesignDocumentView()
{
}

void DesignDocumentView::nodeCreated(const ModelNode & /*createdNode*/) {}
void DesignDocumentView::nodeAboutToBeRemoved(const ModelNode & /*removedNode*/) {}
void DesignDocumentView::nodeRemoved(const ModelNode & /*removedNode*/, const NodeAbstractProperty & /*parentProperty*/, AbstractView::PropertyChangeFlags /*propertyChange*/) {}
void DesignDocumentView::nodeAboutToBeReparented(const ModelNode & /*node*/, const NodeAbstractProperty & /*newPropertyParent*/, const NodeAbstractProperty & /*oldPropertyParent*/, AbstractView::PropertyChangeFlags /*propertyChange*/) {}
void DesignDocumentView::nodeReparented(const ModelNode & /*node*/, const NodeAbstractProperty & /*newPropertyParent*/, const NodeAbstractProperty & /*oldPropertyParent*/, AbstractView::PropertyChangeFlags /*propertyChange*/) {}
void DesignDocumentView::nodeIdChanged(const ModelNode& /*node*/, const QString& /*newId*/, const QString& /*oldId*/) {}
void DesignDocumentView::propertiesAboutToBeRemoved(const QList<AbstractProperty>& /*propertyList*/) {}
void DesignDocumentView::propertiesRemoved(const QList<AbstractProperty>& /*propertyList*/) {}
void DesignDocumentView::variantPropertiesChanged(const QList<VariantProperty>& /*propertyList*/, AbstractView::PropertyChangeFlags /*propertyChange*/) {}
void DesignDocumentView::bindingPropertiesChanged(const QList<BindingProperty>& /*propertyList*/, AbstractView::PropertyChangeFlags /*propertyChange*/) {}
void DesignDocumentView::signalHandlerPropertiesChanged(const QVector<SignalHandlerProperty> & /*propertyList*/,
                                                        AbstractView::PropertyChangeFlags /*propertyChange*/)
{}
void DesignDocumentView::rootNodeTypeChanged(const QString & /*type*/, int /*majorVersion*/, int /*minorVersion*/) {}

void DesignDocumentView::selectedNodesChanged(const QList<ModelNode> & /*selectedNodeList*/,
                          const QList<ModelNode> & /*lastSelectedNodeList*/) {}

void DesignDocumentView::nodeOrderChanged(const NodeListProperty & /*listProperty*/, const ModelNode & /*movedNode*/, int /*oldIndex*/) {}

void DesignDocumentView::scriptFunctionsChanged(const ModelNode &/*node*/, const QStringList &/*scriptFunctionList*/)
{
}

void DesignDocumentView::instancePropertyChange(const QList<QPair<ModelNode, PropertyName> > &/*propertyList*/)
{
}

void DesignDocumentView::instancesCompleted(const QVector<ModelNode> &/*completedNodeList*/)
{

}
void DesignDocumentView::instanceInformationsChange(const QMultiHash<ModelNode, InformationName> &/*informationChangeHash*/)
{

}

void DesignDocumentView::instancesRenderImageChanged(const QVector<ModelNode> &/*nodeList*/)
{

}

void DesignDocumentView::instancesPreviewImageChanged(const QVector<ModelNode> &/*nodeList*/)
{

}

void DesignDocumentView::instancesChildrenChanged(const QVector<ModelNode> &/*nodeList*/)
{

}

void DesignDocumentView::instancesToken(const QString &/*tokenName*/, int /*tokenNumber*/, const QVector<ModelNode> &/*nodeVector*/)
{

}

void DesignDocumentView::nodeSourceChanged(const ModelNode &, const QString & /*newNodeSource*/)
{

}

void DesignDocumentView::rewriterBeginTransaction()
{

}

void DesignDocumentView::rewriterEndTransaction()
{
}

void DesignDocumentView::currentStateChanged(const ModelNode &/*node*/)
{
}

void DesignDocumentView::importsChanged(const QList<Import> &/*addedImports*/, const QList<Import> &/*removedImports*/)
{

}

static QStringList arrayToStringList(const QByteArray &byteArray)
{
    QString str(QString::fromUtf8(byteArray));
    return str.split('\n');
}

static QByteArray stringListToArray(const QStringList &stringList)
{
    QString str;
    foreach (const QString &subString, stringList)
        str += subString + '\n';
    return str.toUtf8();
}

void DesignDocumentView::toClipboard() const
{
    QClipboard *clipboard = QApplication::clipboard();

    QMimeData *data = new QMimeData;

    data->setText(toText());
    QStringList imports;
    foreach (const Import &import, model()->imports())
        imports.append(import.toImportString());

    data->setData("QmlDesigner::imports", stringListToArray(imports));
    clipboard->setMimeData(data);
}

void DesignDocumentView::fromClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    fromText(clipboard->text());
    QStringList imports = arrayToStringList(clipboard->mimeData()->data("QmlDesigner::imports"));
//    foreach (const QString &importString, imports) {
//        Import import(Import::createLibraryImport();
//        model()->addImport(import); //### imports
//    }
}


QString DesignDocumentView::toText() const
{
    QScopedPointer<Model> outputModel(Model::create("QtQuick.Rectangle", 1, 0, model()));
    outputModel->setFileUrl(model()->fileUrl());
    QPlainTextEdit textEdit;

    QString imports;
    foreach (const Import &import, model()->imports()) {
        if (import.isFileImport())
            imports += QStringLiteral("import ") + QStringLiteral("\"") + import.file() + QStringLiteral("\"")+ QStringLiteral(";\n");
        else
            imports += QStringLiteral("import ") + import.url() + QStringLiteral(" ") + import.version() + QStringLiteral(";\n");
    }

    textEdit.setPlainText(imports +  QStringLiteral("Item {\n}\n"));
    NotIndentingTextEditModifier modifier(&textEdit);

    QScopedPointer<RewriterView> rewriterView(new RewriterView(RewriterView::Amend, 0));
    rewriterView->setCheckSemanticErrors(false);
    rewriterView->setTextModifier(&modifier);
    outputModel->setRewriterView(rewriterView.data());

    ModelMerger merger(rewriterView.data());

    merger.replaceModel(rootModelNode());

    ModelNode rewriterNode(rewriterView->rootModelNode());

    //get the text of the root item without imports
    return rewriterView->extractText(QList<ModelNode>() << rewriterNode).value(rewriterNode);
}

void DesignDocumentView::fromText(QString text)
{
    QScopedPointer<Model> inputModel(Model::create("QtQuick.Rectangle", 1, 0, model()));
    inputModel->setFileUrl(model()->fileUrl());
    QPlainTextEdit textEdit;
    QString imports;
    foreach (const Import &import, model()->imports())
        imports += QStringLiteral("import ") + import.toString(true) + QLatin1Char(';') + QLatin1Char('\n');

    textEdit.setPlainText(imports + text);
    NotIndentingTextEditModifier modifier(&textEdit);

    QScopedPointer<RewriterView> rewriterView(new RewriterView(RewriterView::Amend, 0));
    rewriterView->setCheckSemanticErrors(false);
    rewriterView->setTextModifier(&modifier);
    inputModel->setRewriterView(rewriterView.data());

    if (rewriterView->errors().isEmpty() && rewriterView->rootModelNode().isValid()) {
        ModelMerger merger(this);
        merger.replaceModel(rewriterView->rootModelNode());
    }
}

}// namespace QmlDesigner
