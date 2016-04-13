#include "clientinfo.h"
#include "userdata.h"
#include <QString>
#include <QTcpSocket>
#include <QtGui>
#include <QAbstractSocket>
#include <QDebug>
ClientInfo::ClientInfo()
{
    ClientSocket_init();
}
void ClientInfo::ClientSocket_init()
{
    ClientSocket->connect(ClientSocket,SIGNAL(readyRead()),this,SLOT(ReadData_Client()));
}
void ClientInfo::ReadData_Client()
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
