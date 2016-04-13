#include "clientsocket.h"
#include "userdata.h"
#include <QString>
#include <QtGui>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QDebug>
#include "userdata.h"


ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{


     Server_UdpSocket = new QUdpSocket(this);
     connect( this, SIGNAL(readyRead()), this, SLOT(ReadData_Client()) );
}
void ClientSocket::ReadData_Client()
{
    QByteArray qba= this->readAll(); //读取
    QString str = QString::fromLocal8Bit(qba);
    QString ss=QVariant(qba).toString();
    str = str.trimmed();
    ss = ss.trimmed();
    QString ip =this->peerAddress().toString();
    QString port = tr("%1").arg(this->peerPort());
    qDebug()<<ss;
    if(ss.startsWith("#Login#"))
    {
        QStringList user = ss.split("#");
        bool result = false;
        if(UserData::Verify(user[2],user[3]))
        {
            UserData::Client newClient;
            newClient.ClientID = user[2];
            newClient.IP =ip;
            newClient.Port = port;
            newClient.Status = user[4];
            newClient.online = true;
            UserData::Client_List.append(newClient);
            result = true;
//            this->write(QString("%1").arg(result).toLocal8Bit());
            QString OwnInfo="&"+UserData::GetUserInfo(newClient.ClientID)+"&";
            QString FriendsInfo = UserData::GetFriendsInfo(newClient.ClientID) +"&";
            QString UserGroupInfo = UserData::GetUserGroup(newClient.ClientID);
            qDebug()<<OwnInfo;
            qDebug()<<FriendsInfo;
            qDebug()<<UserGroupInfo;

            this->write(OwnInfo.toLocal8Bit());//个人信息
            this->write(FriendsInfo.toLocal8Bit());//好友信息
//            qDebug()<<"******************************************";
//            qDebug()<<FriendsInfo;
            QVector<UserData::Client>::iterator it = UserData::Client_List.begin();
            for(;it != UserData::Client_List.end();++it)
            {
                if(UserData::IsFriend(newClient.ClientID,it->ClientID))
                {

                    QString update = newClient.ClientID+"|"+newClient.IP+"|"+newClient.Port+"|";
                    if(newClient.Status == "2")//隐身
                        update.append("0");
                    else
                    {
                        update.append(newClient.Status);

                    }

                    QByteArray information = QString("#Update#"+update).toLatin1();
//                    qDebug()<<QString("#Update#"+update);
                    Server_UdpSocket->writeDatagram(information,information.size(),QHostAddress(it->IP),it->Port.toInt());
                }

            }

        }
        else
            this->write(QString("%1").arg(result).toLatin1());

    }



}
