#include "Xmltest.h"

Xmltest::Xmltest(QWidget *parent)
    : QWidget(parent)
{
    //QDomDocument doc= createFolderPathXml("F:\\testPath");
    QDomDocument doc= createFolderPathXml("C:\\Users\\Administrator\\Desktop\\XmlTest");


    QFile file("test.xml");
    if (!file.open(QIODevice::WriteOnly))
    {
        file.close();
        return ;
    }

    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

Xmltest::~Xmltest()
{

}

QDomDocument Xmltest::createFolderPathXml(QString path)
{
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement("root");
    doc.appendChild(root);

    checkFolderPath(path,root,doc);
    return doc;
}

void Xmltest::checkFolderPath(QString parentPath,QDomElement &parentElt,QDomDocument &doc)
{
    QDir pathDir=QDir(parentPath);
    qDebug()<<"checkFolderPath:"<<parentPath;

    QFileInfoList fileInfoList = pathDir.entryInfoList(QDir::NoFilter,QDir::Type);


    foreach(QFileInfo fileInfo, fileInfoList)
    {
        //在linux环境下,"."或".."看不到,这个判断是linux专用
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        //发现子目录
        if(fileInfo.isDir())
        {
            QString childPath=fileInfo.absoluteFilePath();
            QString folderName=fileInfo.dir().dirName();
            qDebug()<<"childPath"<<childPath<<"folderName"<<folderName;
            QDomElement childElt=doc.createElement("Folder");
            childElt.setAttribute("Path",childPath);
            parentElt.appendChild(childElt);
            //递归子文件夹
            checkFolderPath(childPath,childElt,doc);
        }
        //发现子文件
        else
        {
            QString fileName=fileInfo.fileName();
            QDomElement childElt=doc.createElement("File");
            childElt.setAttribute("Name",fileName);
            parentElt.appendChild(childElt);
            qDebug()<<"fileName"<<fileName;
        }
    }
}
