#include "XmlRead.h"

XMlRead::XMlRead(QWidget *parent)
    : QWidget(parent)
{
    treeView = new QTreeView(this);
    model = new QStandardItemModel(treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Name"));

    QFile file("test.xml");
    bool fileOpen = file.open(QIODevice::ReadOnly);
    qDebug()<<"fileOpen:"<<fileOpen;
    if(fileOpen)
    {
        QDomDocument doc;
        bool docSetContent = doc.setContent(&file);
        qDebug()<<"doc.setContent(&file):"<<docSetContent;
        //setContent是将指定的内容指定给QDomDocument解析
        if(docSetContent)
        {
            QDomElement root = doc.documentElement();
            rootItem=new QStandardItem();
            listDom(root,rootItem);
        }
    }
    model->appendRow(rootItem);
    treeView->setModel(model);

    printItemInfo(rootItem,4);

}

void XMlRead::printItemInfo(QStandardItem* parentItem,int blankSize)
{
    int size=parentItem->rowCount();
    for(int i=0;i<size;i++)
    {
        QStandardItem*childItem=parentItem->child(i);
        if(childItem->data(IsFolderRole).toBool())
        {
            QString str;
            int tmpSize=blankSize;
            while(tmpSize--)
            {
                str+=" ";
            }
            str+=QString("Folder:")+childItem->data(FolderPathRole).toString();
            qDebug()<<str;
            printItemInfo(childItem,blankSize+4);
        }
        else
        {
            QString str;
            int tmpSize=blankSize;
            while(tmpSize--)
            {
                str+=" ";
            }
            str+=QString("File:")+childItem->data(FileNameRole).toString();
            qDebug()<<str;
        }
    }
}

XMlRead::~XMlRead()
{

}

void XMlRead::listDom(QDomElement &docElem,QStandardItem *parentItem)
{
    QDomElement childElt=docElem.firstChildElement();
    QStandardItem*item;
    while(childElt.isNull()==false)
    {
        if(childElt.tagName() == "Folder")
        {
            QString pathStr=childElt.attribute("Path");//获取Path的内容
            QString str=pathStr;
            int index=str.lastIndexOf("/");//获取最后一个"/"的节点
            if(index!=-1)
            {
                 int size=str.size();
                 str=str.right(size-index-1);
                 item=new QStandardItem();
                 item->setData(str,Qt::DisplayRole);
                 QColor col(Qt::red);
                 item->setData(col,Qt::TextColorRole);

                 item->setData(true,IsFolderRole);
                 item->setData(pathStr,FolderPathRole);
                 item->setData(pathStr,Qt::ToolTipRole);
                 parentItem->appendRow(item);
                 qDebug()<<"folder:"<<str;
            }
            listDom(childElt,item);
        }
        else
        {
            QString str = childElt.attribute("Name");
            item=new QStandardItem();
            item->setData(str,Qt::DisplayRole);
            item->setData(false,IsFolderRole);
            item->setData(str,FileNameRole);
            item->setData(QString("I am a file"),Qt::ToolTipRole);
            parentItem->appendRow(item);
            qDebug()<<"file:"<<str;
        }
        childElt=childElt.nextSiblingElement();
    }

}
