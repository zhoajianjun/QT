#include "fileio.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QTextCodec>

FileIo::FileIo(QObject *parent) : QObject(parent)
{
   // datapath = getenv("")  + "";
    //qDebug() << "datapath: " + datapath;
}

QString FileIo::read()
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QString();
    }

    QFile file(mSource);
    QFileInfo fileInfo(file.fileName());

    QString fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextStream t( &file );
        t.setCodec(codec);

       do {
            line = t.readLine();
            fileContent +=line;
       } while (!line.isNull());

        file.close();
        return fileContent;
    } else {
        emit error("Unable to open the file");
        return QString();
    }

}

bool FileIo::write(const QString& data)
{
    if (mSource.isEmpty())
        return false;

    QFile file(mSource);
    QFileInfo fileInfo(file.fileName());
    if (!file.open(QFile::WriteOnly  |QFile::Append))
        return false;

    QTextStream out(&file);
    out <<data<<" ";


    file.close();

    return true;
}

void FileIo::clear()
{
   QFile file(datapath + mSource);
   file.resize(0);
   file.close();
}

/*QString FileIo::getenv(const QString envVarName) const
{
    QByteArray result = qgetenv(envVarName.toStdString().c_str());
    QString output = QString::fromLocal8Bit(result);
    qDebug() << envVarName << " value is: "  << output;
    return output;
}*/
/*QString FileIo::getabsoluteroute()
{
    QFile file(datapath + mSource);
    QFileInfo fileInfo(file.fileName());
   // qDebug() << "file path: " << fileInfo.absoluteFilePath();
    return  fileInfo.absoluteFilePath();
}*/
