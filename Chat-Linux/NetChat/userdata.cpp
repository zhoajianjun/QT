#include "userdata.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTcpSocket>
#include <QNetworkInterface>
UserData::UserData()
{
}
QVector<UserData::User> UserData::User_List;
//QVector<UserData::UserInfo> UserData::UserInfo_List;
UserData::UserInfo UserData::OwnInfo;
UserData::User UserData::Current_User ={"","","0",false,false};
UserData::UserInfo UserData::newUserInfo;
UserData::User UserData::newUser;
QString UserData::LoginImagesPath= "./images/LoginBack.png";
QString UserData::FriendsImagesPath= ":/images/images/FriendBack2.png";
QString UserData::ChatViewImagesPath= ":/images/ChatImages/ChatView.png";
QString UserData::AvatarPath = "./avatar/";
QVector<UserData::FriendInfo> UserData::Current_FriendInfo;
bool UserData::ChatWindow = false;

QStringList UserData::Status = QString("离线|在线|离线|忙碌|离开|求扰|勿扰").split("|");

QUdpSocket *UserData::udpSocket =NULL;
qint32 UserData::port;
QString UserData::getIP()
{
    //QList是Qt中一个容器模板类，是一个数组指针？
    QList<QHostAddress> list = QNetworkInterface::allAddresses();//此处的所有地址是指ipv4和ipv6的地址
    //foreach (variable, container),此处为按照容器list中条目的顺序进行迭代
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}





























