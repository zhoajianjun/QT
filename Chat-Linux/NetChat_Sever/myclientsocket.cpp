#include "myclientsocket.h"
#include "userdata.h"
#include <QString>
#include <QtGui>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QDebug>
myClientSocket::myClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(ReadData_Client())); //有可读的信息，触发读函数槽
}


void myClientSocket::ReadData_Client()
{
    QByteArray qba= this->readAll(); //读取
    QString ss=QVariant(qba).toString();
    ss = ss.trimmed();
    QString ip =this->peerAddress().toString();
    QString port = tr("%1").arg(this->peerPort());
    if(ss.startsWith("#Login#"))
    {
        QStringList user = ss.split("#");
        QString result = "false";
        if(UserData::Verify(user[2],user[3]))
        {
            this->ClientID = user[2];
            this->IP =ip;
            this->Port = port;
            result = "true";

        }
        this->write(result.toLatin1());
    }

    qDebug()<<"$$$$$$$$$"<<ss;

}
