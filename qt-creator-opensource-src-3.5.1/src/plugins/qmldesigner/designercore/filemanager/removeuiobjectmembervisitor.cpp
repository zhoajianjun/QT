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

#include "removeuiobjectmembervisitor.h"

#include <qmljs/parser/qmljsast_p.h>

#include <QDebug>

using namespace QmlDesigner;
using namespace QmlDesigner::Internal;
using namespace QmlJS;
using namespace QmlJS::AST;

RemoveUIObjectMemberVisitor::RemoveUIObjectMemberVisitor(TextModifier &modifier,
                                                         quint32 objectLocation):
    QMLRewriter(modifier),
    objectLocation(objectLocation)
{
}

bool RemoveUIObjectMemberVisitor::preVisit(Node *ast)
{
    parents.push(ast);

    return true;
}

void RemoveUIObjectMemberVisitor::postVisit(Node *)
{
    parents.pop();
}

bool RemoveUIObjectMemberVisitor::visit(UiPublicMember *ast) { return visitObjectMember(ast); }
bool RemoveUIObjectMemberVisitor::visit(UiObjectDefinition *ast) { return visitObjectMember(ast); }
bool RemoveUIObjectMemberVisitor::visit(UiSourceElement *ast) { return visitObjectMember(ast); }
bool RemoveUIObjectMemberVisitor::visit(UiObjectBinding *ast) { return visitObjectMember(ast); }
bool RemoveUIObjectMemberVisitor::visit(UiScriptBinding *ast) { return visitObjectMember(ast); }
bool RemoveUIObjectMemberVisitor::visit(UiArrayBinding *ast) { return visitObjectMember(ast); }

// FIXME: duplicate code in the QmlJS::Rewriter class, remove this
bool RemoveUIObjectMemberVisitor::visitObjectMember(UiObjectMember *ast)
{
    const quint32 memberStart = ast->firstSourceLocation().offset;

    if (memberStart == objectLocation) {
        // found it
        int start = objectLocation;
        int end = ast->lastSourceLocation().end();

        if (UiArrayBinding *parentArray = containingArray())
            extendToLeadingOrTrailingComma(parentArray, ast, start, end);
        else
            includeSurroundingWhitespace(start, end);

        includeLeadingEmptyLine(start);
        replace(start, end - start, QStringLiteral(""));

        setDidRewriting(true);

        return false;
    } else if (ast->lastSourceLocation().end() <= objectLocation) {
        // optimization: if the location of the object-to-be-removed is not inside the current member, skip any children
        return false;
    } else {
        // only visit children if the rewriting isn't done yet.
        return !didRewriting();
    }
}

UiArrayBinding *RemoveUIObjectMemberVisitor::containingArray() const
{
    if (parents.size() > 2) {
        if (cast<UiArrayMemberList*>(parents[parents.size() - 2]))
            return cast<UiArrayBinding*>(parents[parents.size() - 3]);
    }

    return 0;
}

// FIXME: duplicate code in the QmlJS::Rewriter class, remove this
void RemoveUIObjectMemberVisitor::extendToLeadingOrTrailingComma(UiArrayBinding *parentArray,
                                                                 UiObjectMember *ast,
                                                                 int &start,
                                                                 int &end) const
{
    UiArrayMemberList *currentMember = 0;
    for (UiArrayMemberList *it = parentArray->members; it; it = it->next) {
        if (it->member == ast) {
            currentMember = it;
            break;
        }
    }

    if (!currentMember)
        return;

    if (currentMember->commaToken.isValid()) {
        // leading comma
        start = currentMember->commaToken.offset;
        if (includeSurroundingWhitespace(start, end))
            --end;
    } else if (currentMember->next && currentMember->next->commaToken.isValid()) {
        // trailing comma
        end = currentMember->next->commaToken.end();
        includeSurroundingWhitespace(start, end);
    } else {
        // array with 1 element, so remove the complete binding
        start = parentArray->firstSourceLocation().offset;
        end = parentArray->lastSourceLocation().end();
        includeSurroundingWhitespace(start, end);
    }
}
