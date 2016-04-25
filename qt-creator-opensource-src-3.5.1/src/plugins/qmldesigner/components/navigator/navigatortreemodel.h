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

#ifndef NAVIGATORTREEMODEL_H
#define NAVIGATORTREEMODEL_H

#include <modelnode.h>
#include <nodemetainfo.h>

#include <QStandardItem>
#include <QStandardItemModel>
#include <QPointer>

namespace QmlDesigner {

class Model;
class AbstractView;
class ModelNode;

#ifdef _LOCK_ITEMS_
    struct ItemRow {
        ItemRow()
            : idItem(0), lockItem(0), visibilityItem(0) {}
        ItemRow(QStandardItem *id, QStandardItem *lock, QStandardItem *visibility, const QMap<QString, QStandardItem *> &properties)
            : idItem(id), lockItem(lock), visibilityItem(visibility), propertyItems(properties) {}

        QList<QStandardItem*> toList() const {
            return QList<QStandardItem*>() << idItem << lockItem << visibilityItem;
        }

        QStandardItem *idItem;
        QStandardItem *lockItem;
        QStandardItem *visibilityItem;
        QMap<QString, QStandardItem *> propertyItems;
    };
#else
    struct ItemRow {
        ItemRow()
            : idItem(0), visibilityItem(0) {}
        ItemRow(QStandardItem *id, QStandardItem *visibility, const QMap<QString, QStandardItem *> &properties)
            : idItem(id), visibilityItem(visibility), propertyItems(properties) {}

        QList<QStandardItem*> toList() const {
            return QList<QStandardItem*>() << idItem << visibilityItem;
        }

        QStandardItem *idItem;
        QStandardItem *visibilityItem;
        QMap<QString, QStandardItem *> propertyItems;
    };
#endif

class NavigatorTreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    enum {
        InternalIdRole = Qt::UserRole
    };


    NavigatorTreeModel(QObject *parent = 0);
    ~NavigatorTreeModel();

    Qt::DropActions supportedDropActions() const;
    Qt::DropActions supportedDragActions() const;

    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data,
                      Qt::DropAction action,
                      int row,
                      int column,
                      const QModelIndex &parent);

    void setView(AbstractView *view);
    void clearView();

    QModelIndex indexForNode(const ModelNode &node) const;
    ModelNode nodeForIndex(const QModelIndex &index) const;
    bool hasNodeForIndex(const QModelIndex &index) const;

    bool isInTree(const ModelNode &node) const;
    bool isNodeInvisible(const QModelIndex &index) const;
    bool isNodeInvisible(const ModelNode &node) const;

    void addSubTree(const ModelNode &node);
    void removeSubTree(const ModelNode &node);
    void updateItemRow(const ModelNode &node);

    void setId(const QModelIndex &index, const QString &id);
    void setVisible(const QModelIndex &index, bool visible);

    void openContextMenu(const QPoint &p);

    ItemRow itemRowForNode(const ModelNode &node);
    bool blockItemChangedSignal(bool block);

private slots:
    void handleChangedItem(QStandardItem *item);

private:
    ItemRow createItemRow(const ModelNode &node);
    void updateItemRow(const ModelNode &node, ItemRow row);
    void handleChangedIdItem(QStandardItem *idItem, ModelNode &modelNode);
    void handleChangedVisibilityItem(QStandardItem *visibilityItem, ModelNode &modelNode);

    void moveNodesInteractive(NodeAbstractProperty &parentProperty, const QList<ModelNode> &modelNodes, int targetIndex);
    void handleInternalDrop(const QMimeData *mimeData, int rowNumber, const QModelIndex &dropModelIndex);
    void handleItemLibraryItemDrop(const QMimeData *mimeData, int rowNumber, const QModelIndex &dropModelIndex);
    void handleItemLibraryImageDrop(const QMimeData *mimeData, int rowNumber, const QModelIndex &dropModelIndex);

private:
    QHash<ModelNode, ItemRow> m_nodeItemHash;
    QPointer<AbstractView> m_view;

    bool m_blockItemChangedSignal;
};

} // namespace QmlDesigner

#endif // NAVIGATORTREEMODEL_H
