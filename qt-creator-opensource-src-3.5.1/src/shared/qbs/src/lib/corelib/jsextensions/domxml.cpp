/****************************************************************************
**
** Copyright (C) 2015 BogDan Vatra <bogdan@kde.org>
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

#include "domxml.h"

#include <QFile>
#include <QScriptEngine>


namespace qbs {
namespace Internal {

void initializeJsExtensionXml(QScriptValue extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    QScriptValue obj = engine->newQMetaObject(&XmlDomDocument::staticMetaObject, engine->newFunction(&XmlDomDocument::ctor));
    extensionObject.setProperty(QLatin1String("XmlDomDocument"), obj);
    obj = engine->newQMetaObject(&XmlDomNode::staticMetaObject, engine->newFunction(&XmlDomNode::ctor));
    extensionObject.setProperty(QLatin1String("XmlDomElement"), obj);
}

QScriptValue XmlDomDocument::ctor(QScriptContext *context, QScriptEngine *engine)
{
    XmlDomDocument *xml = 0;
    switch (context->argumentCount()) {
    case 0:
        xml = new XmlDomDocument(context);
        break;
    case 1:
        xml = new XmlDomDocument(context, context->argument(0).toString());
        break;
    default:
        return context->throwError(QLatin1String("DomXml(QString file = QLatin1String(\"\"))"));
    }
    QScriptValue obj = engine->newQObject(xml, QScriptEngine::ScriptOwnership);
    return obj;
}

QScriptValue XmlDomDocument::documentElement()
{
    return engine()->newQObject(new XmlDomNode(m_domDocument.documentElement()), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomDocument::createElement(const QString &tagName)
{
    return engine()->newQObject(new XmlDomNode(m_domDocument.createElement(tagName)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomDocument::createCDATASection(const QString &value)
{
    return engine()->newQObject(new XmlDomNode(m_domDocument.createCDATASection(value)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomDocument::createTextNode(const QString &value)
{
    return engine()->newQObject(new XmlDomNode(m_domDocument.createTextNode(value)), QScriptEngine::ScriptOwnership);
}

bool XmlDomDocument::setContent(const QString &content)
{
    return m_domDocument.setContent(content);
}

QString XmlDomDocument::toString(int indent)
{
    return m_domDocument.toString(indent);
}

void XmlDomDocument::save(const QString &filePath, int indent)
{
    QFile f(filePath);
    if (!f.open(QIODevice::WriteOnly)) {
        context()->throwError(QString::fromLatin1("unable to open '%1'")
                              .arg(filePath));
        return;
    }

    QByteArray buff(m_domDocument.toByteArray(indent));
    if (buff.size() != f.write(buff))
    {
        context()->throwError(f.errorString());
        f.close();
        return;
    }

    f.close();
    if (f.error() != QFile::NoError)
        context()->throwError(f.errorString());
}

void XmlDomDocument::load(const QString &filePath)
{
    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        context()->throwError(QString::fromLatin1("unable to open '%1'")
                              .arg(filePath));
        return;
    }

    QString errorMsg;
    if (!m_domDocument.setContent(&f, &errorMsg)) {
        context()->throwError(errorMsg);
        return;
    }
}

XmlDomDocument::XmlDomDocument(QScriptContext *context, const QString &name):m_domDocument(name)
{
    Q_UNUSED(context)
    m_domNode = m_domDocument;
}

QScriptValue XmlDomNode::ctor(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(context)
    return engine->newQObject(new XmlDomNode(), QScriptEngine::ScriptOwnership);
}

bool XmlDomNode::isElement() const
{
    return m_domNode.isElement();
}

bool XmlDomNode::isCDATASection() const
{
    return m_domNode.isCDATASection();
}

bool XmlDomNode::isText() const
{
    return m_domNode.isText();
}

QString XmlDomNode::attribute(const QString &name, const QString &defValue)
{
    QDomElement el = m_domNode.toElement();
    if (el.isNull()) {
        context()->throwError(QString::fromLatin1("Node '%1' is not an element node").arg(m_domNode.nodeName()));
        return defValue;
    }
    return el.attribute(name, defValue);
}

void XmlDomNode::setAttribute(const QString &name, const QString &value)
{
    QDomElement el = m_domNode.toElement();
    if (el.isNull()) {
        context()->throwError(QString::fromLatin1("Node '%1' is not an element node").arg(m_domNode.nodeName()));
        return;
    }
    el.setAttribute(name, value);
}

bool XmlDomNode::hasAttribute(const QString &name) const
{
    QDomElement el = m_domNode.toElement();
    if (el.isNull()) {
        context()->throwError(QString::fromLatin1("Node '%1' is not an element node").arg(m_domNode.nodeName()));
        return false;
    }
    return el.hasAttribute(name);
}

QString XmlDomNode::tagName() const
{
    QDomElement el = m_domNode.toElement();
    if (el.isNull()) {
        context()->throwError(QString::fromLatin1("Node '%1' is not an element node").arg(m_domNode.nodeName()));
        return QString();
    }
    return el.tagName();
}

void XmlDomNode::setTagName(const QString &name)
{
    QDomElement el = m_domNode.toElement();
    if (el.isNull()) {
        context()->throwError(QString::fromLatin1("Node '%1' is not an element node").arg(m_domNode.nodeName()));
        return;
    }
    el.setTagName(name);
}

QString XmlDomNode::text() const
{
    QDomElement el = m_domNode.toElement();
    if (el.isNull()) {
        context()->throwError(QString::fromLatin1("Node '%1' is not an element node").arg(m_domNode.nodeName()));
        return QString();
    }
    return el.text();
}

QString XmlDomNode::data() const
{
    if (m_domNode.isText())
        return m_domNode.toText().data();
    if (m_domNode.isCDATASection())
        return m_domNode.toCDATASection().data();
    if (m_domNode.isCharacterData())
        return m_domNode.toCharacterData().data();
    context()->throwError(QString::fromLatin1("Node '%1' is not a character data node").arg(m_domNode.nodeName()));
    return QString();
}

void XmlDomNode::setData(const QString &v) const
{
    if (m_domNode.isText())
        return m_domNode.toText().setData(v);
    if (m_domNode.isCDATASection())
        return m_domNode.toCDATASection().setData(v);
    if (m_domNode.isCharacterData())
        return m_domNode.toCharacterData().setData(v);
    context()->throwError(QString::fromLatin1("Node '%1' is not a character data node").arg(m_domNode.nodeName()));
    return;
}

void XmlDomNode::clear()
{
    m_domNode.clear();
}

bool XmlDomNode::hasAttributes() const
{
    return m_domNode.hasAttributes();
}

bool XmlDomNode::hasChildNodes() const
{
    return m_domNode.hasChildNodes();
}

QScriptValue XmlDomNode::parentNode() const
{
    return engine()->newQObject(new XmlDomNode(m_domNode.parentNode()), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::firstChild(const QString &tagName)
{
    if (tagName.isEmpty())
        return engine()->newQObject(new XmlDomNode(m_domNode.firstChild()), QScriptEngine::ScriptOwnership);
    return engine()->newQObject(new XmlDomNode(m_domNode.firstChildElement(tagName)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::lastChild(const QString &tagName) const
{
    if (tagName.isEmpty())
        return engine()->newQObject(new XmlDomNode(m_domNode.lastChild()), QScriptEngine::ScriptOwnership);
    return engine()->newQObject(new XmlDomNode(m_domNode.lastChildElement(tagName)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::previousSibling(const QString &tagName) const
{
    if (tagName.isEmpty())
        return engine()->newQObject(new XmlDomNode(m_domNode.previousSibling()), QScriptEngine::ScriptOwnership);
    return engine()->newQObject(new XmlDomNode(m_domNode.previousSiblingElement(tagName)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::nextSibling(const QString &tagName) const
{
    if (tagName.isEmpty())
        return engine()->newQObject(new XmlDomNode(m_domNode.nextSibling()), QScriptEngine::ScriptOwnership);
    return engine()->newQObject(new XmlDomNode(m_domNode.nextSiblingElement(tagName)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::appendChild(QScriptValue newChild)
{
    XmlDomNode *newNode = qobject_cast<XmlDomNode*>(newChild.toQObject());
    if (!newNode) {
        context()->throwError(QString::fromLatin1("First argument is not a XmlDomNode object"));
        return QScriptValue();
    }
    return engine()->newQObject(new XmlDomNode(m_domNode.appendChild(newNode->m_domNode)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::insertBefore(const QScriptValue &newChild, const QScriptValue &refChild)
{
    XmlDomNode *newNode = qobject_cast<XmlDomNode*>(newChild.toQObject());
    if (!newNode) {
        context()->throwError(QString::fromLatin1("First argument is not a XmlDomNode object"));
        return QScriptValue();
    }

    XmlDomNode *refNode = qobject_cast<XmlDomNode*>(refChild.toQObject());
    if (!refNode) {
        context()->throwError(QString::fromLatin1("Second argument is not a XmlDomNode object"));
        return QScriptValue();
    }

    return engine()->newQObject(new XmlDomNode(m_domNode.insertBefore(newNode->m_domNode, refNode->m_domNode)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::insertAfter(const QScriptValue &newChild, const QScriptValue &refChild)
{
    XmlDomNode *newNode = qobject_cast<XmlDomNode*>(newChild.toQObject());
    if (!newNode) {
        context()->throwError(QString::fromLatin1("First argument is not a XmlDomNode object"));
        return QScriptValue();
    }

    XmlDomNode *refNode = qobject_cast<XmlDomNode*>(refChild.toQObject());
    if (!refNode) {
        context()->throwError(QString::fromLatin1("Second argument is not a XmlDomNode object"));
        return QScriptValue();
    }

    return engine()->newQObject(new XmlDomNode(m_domNode.insertAfter(newNode->m_domNode, refNode->m_domNode)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::replaceChild(const QScriptValue &newChild, const QScriptValue &oldChild)
{
    XmlDomNode *newNode = qobject_cast<XmlDomNode*>(newChild.toQObject());
    if (!newNode) {
        context()->throwError(QString::fromLatin1("First argument is not a XmlDomNode object"));
        return QScriptValue();
    }

    XmlDomNode *oldNode = qobject_cast<XmlDomNode*>(oldChild.toQObject());
    if (!oldNode) {
        context()->throwError(QString::fromLatin1("Second argument is not a XmlDomNode object"));
        return QScriptValue();
    }

    return engine()->newQObject(new XmlDomNode(m_domNode.replaceChild(newNode->m_domNode, oldNode->m_domNode)), QScriptEngine::ScriptOwnership);
}

QScriptValue XmlDomNode::removeChild(const QScriptValue &oldChild)
{
    XmlDomNode *oldNode = qobject_cast<XmlDomNode*>(oldChild.toQObject());
    if (!oldNode) {
        context()->throwError(QString::fromLatin1("First argument is not a XmlDomNode object"));
        return QScriptValue();
    }

    return engine()->newQObject(new XmlDomNode(m_domNode.removeChild(oldNode->m_domNode)), QScriptEngine::ScriptOwnership);
}

XmlDomNode::XmlDomNode(const QDomNode &other)
{
    m_domNode = other;
}

} // namespace Internal
} // namespace qbs
