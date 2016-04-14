#ifndef XMLREAD_H
#define XMLREAD_H

#include <QtWidgets>
#include <QtCore>
#include <QtXml>


class XMlRead : public QWidget
{
    Q_OBJECT
public:
    enum
    {
        FolderPathRole=Qt::UserRole+2,
        FileNameRole,
        IsFolderRole
    };

    XMlRead(QWidget *parent = 0);
    ~XMlRead();
    void listDom(QDomElement &docElem,QStandardItem *parentItem);
    void printItemInfo(QStandardItem* parentItem,int blankSize);
private:
    QTreeView *treeView;
    QStandardItemModel *model;
    QStandardItem *rootItem;
};

#endif // XMLREAD_H
