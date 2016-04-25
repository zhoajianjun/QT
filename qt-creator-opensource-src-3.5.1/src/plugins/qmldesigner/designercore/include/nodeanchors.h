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

#ifndef NODEANCHORS_H
#define NODEANCHORS_H


#include <QPointer>
#include <QSharedPointer>
#include "corelib_global.h"
#include <anchorline.h>
#include <nodestate.h>

namespace QmlDesigner {
    class Model;
    class NodeState;

    namespace Internal {
        class InternalNode;
        typedef QSharedPointer<InternalNode> InternalNodePointer;
        typedef QWeakPointer<InternalNode> InternalNodeWeakPointer;

        class InternalNodeState;
        typedef QSharedPointer<InternalNodeState> InternalNodeStatePointer;

        class TextToModelMerger;
    }
}

namespace QmlDesigner {

class CORESHARED_EXPORT NodeAnchors
{
    friend class NodeState;
    friend class ModelNode;
    friend class Internal::TextToModelMerger;

public:
    explicit NodeAnchors(const NodeState &nodeState);

    NodeAnchors(const NodeAnchors &other);
    NodeAnchors& operator=(const NodeAnchors &other);
    ~NodeAnchors();

    ModelNode modelNode() const;
    NodeState nodeState() const;

    bool isValid() const;

    void setAnchor(AnchorLine::Type sourceAnchorLineType,
                   const ModelNode &targetModelNode,
                   AnchorLine::Type targetAnchorLineType);
    bool canAnchor(AnchorLine::Type sourceAnchorLineType,
                   const ModelNode &targetModelNode,
                   AnchorLine::Type targetAnchorLineType) const;
    bool canAnchor(const ModelNode &targetModelNode) const;
    AnchorLine::Type possibleAnchorLines(AnchorLine::Type sourceAnchorLineType,
                                         const ModelNode &targetModelNode) const;
    AnchorLine localAnchor(AnchorLine::Type anchorLineType) const;
    AnchorLine anchor(AnchorLine::Type anchorLineType) const;
    void removeAnchor(AnchorLine::Type sourceAnchorLineType);
    void removeAnchors();
    bool hasLocalAnchor(AnchorLine::Type sourceAnchorLineType) const;
    bool hasAnchor(AnchorLine::Type sourceAnchorLineType) const;
    bool hasLocalAnchors() const;
    bool hasAnchors() const;
    void setMargin(AnchorLine::Type sourceAnchorLineType, double margin) const;
    bool hasMargin(AnchorLine::Type sourceAnchorLineType) const;
    double localMargin(AnchorLine::Type sourceAnchorLineType) const;
    double margin(AnchorLine::Type sourceAnchorLineType) const;
    void removeMargin(AnchorLine::Type sourceAnchorLineType);
    void removeMargins();

private: // functions
    NodeAnchors(const Internal::InternalNodeStatePointer &internalNodeState, Model *model);

private: //variables
    Internal::InternalNodePointer m_internalNode;
    Internal::InternalNodeStatePointer m_internalNodeState;
    QPointer<Model> m_model;
};

CORESHARED_EXPORT QDebug operator<<(QDebug debug, const NodeAnchors &anchors);
CORESHARED_EXPORT QTextStream& operator<<(QTextStream &stream, const NodeAnchors &anchors);

} // namespace QmlDesigner

#endif // NODEANCHORS_H
