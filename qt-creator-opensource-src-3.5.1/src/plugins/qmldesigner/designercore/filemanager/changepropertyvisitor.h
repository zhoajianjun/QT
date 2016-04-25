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

#ifndef CHANGEPROPERTYVISITOR_H
#define CHANGEPROPERTYVISITOR_H

#include "qmlrefactoring.h"
#include "qmlrewriter.h"

namespace QmlDesigner {
namespace Internal {

class ChangePropertyVisitor: public QMLRewriter
{
public:
    ChangePropertyVisitor(QmlDesigner::TextModifier &modifier,
                          quint32 parentLocation,
                          const QString &name,
                          const QString &value,
                          QmlRefactoring::PropertyType propertyType);

protected:
    virtual bool visit(QmlJS::AST::UiObjectDefinition *ast);
    virtual bool visit(QmlJS::AST::UiObjectBinding *ast);

private:
    void replaceInMembers(QmlJS::AST::UiObjectInitializer *initializer,
                          const QString &propertyName);
    void replaceMemberValue(QmlJS::AST::UiObjectMember *propertyMember, bool needsSemicolon);
    static bool isMatchingPropertyMember(const QString &propName,
                                         QmlJS::AST::UiObjectMember *member);
    static bool nextMemberOnSameLine(QmlJS::AST::UiObjectMemberList *members);

    void insertIntoArray(QmlJS::AST::UiArrayBinding* ast);

private:
    quint32 m_parentLocation;
    QString m_name;
    QString m_value;
    QmlRefactoring::PropertyType m_propertyType;
};

} // namespace Internal
} // namespace QmlDesigner

#endif // CHANGEPROPERTYVISITOR_H
