#include "userdata.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkInterface>
UserData::UserData()
{
}
QVector<UserData::User> UserData::User_List;
QVector<UserData::Client> UserData::Client_List;
QVector<UserData::UserInfo> UserData::UserInfo_List;
UserData::UserInfo UserData::FriendInfo;
UserData::UserInfo UserData::newUserInfo;
UserData::User UserData::newUser;
QString UserData::port ="23456";
QString UserData::ip = UserData::getIP();

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

void UserData::Link()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Chat");
    db.setUserName("root");
    db.setPassword("rcl");
    if(!db.open()){
        qDebug()<<"Unable to open database";
    }else{
        qDebug()<<"Database connection established";
    }
    db.exec("SET NAMES ’UTF8’");
}
bool UserData::Verify(QString id,QString pwd)
{
    QSqlQuery query;
    query.exec("SELECT * FROM User");
    while (query.next())
    {
        if(id ==query.value(0).toString())
        {
            if(pwd==query.value(1).toString())
            {
                return true;
            }
            else
                return false;
            break;
        }
    }
    return false;
}


bool UserData::IsFriend(QString id1, QString id2)
{
    QSqlQuery query;
    query.exec("SELECT FriendID FROM GroupTable WHERE UserID ="+ id1);

    while (query.next())
    {

        if(id2 ==query.value(0).toString())
        {
           return true;
        }

    }
    return false;

}
void UserData::GetUser()
{
    QSqlQuery query;
    query.exec("SELECT * FROM User");
    while (query.next())
    {
        User user;
        user.UserID = query.value(0).toString();//query.value()的参数只能是index
        user.Password = query.value(1).toString();
        User_List.append(user);
    }
}
QString UserData::GetUserInfo(QString UserID)
{
    QSqlQuery query;
    QString UserInfo;
    query.exec("SELECT * FROM UserInfo WHERE UserID ="+UserID);
    UserInfo =UserID;
    while(query.next())
    {
        for(int i = 1;i<7;i++)
        {
            UserInfo.append("#"+query.value(i).toString());
        }
    }

    QVector<UserData::Client>::const_iterator it = Client_List.begin();
    for(;it != Client_List.end(); ++it)
    {
        if(it->ClientID == UserID)
        {
            if(it->Status == "隐身")
            {

                UserInfo.append("#"+it->IP+"#"+it->Port+"#离线");
            }
            else
            {
                UserInfo.append("#"+it->IP+"#"+it->Port+"#"+it->Status);
            }

            return UserInfo;
        }
    }

    UserInfo.append("#"+UserData::ip+"#"+UserData::port+"#离线");
    return UserInfo;
}

QString UserData::GetFriendsInfo(QString UserID)
{
    QSqlQuery query;
    QString FriendInfo;
    query.exec("SELECT * FROM GroupTable where UserID ="+UserID);
    while(query.next())
    {
        FriendInfo.append(query.value(1).toString()+"@");
        FriendInfo.append(GetUserInfo(query.value(2).toString()));
        FriendInfo.append("|");
    }

    return FriendInfo;
}
QString UserData::GetUserGroup(QString UserID)
{
    QSqlQuery query;
    QString UserGroupInfo ="";
    query.exec("SELECT * FROM ChatGroup where UserID ="+UserID);
    while(query.next())
    {
        UserGroupInfo.append( GetGroupInfo(query.value(0).toString()) +"|");
    }

    return UserGroupInfo;
}

QString UserData::GetGroupInfo(QString GroupID)
{

    QString GroupInfo ="";
    QSqlQuery query1;
    QSqlQuery query2;
    query1.exec("SELECT * FROM ChatGroupInfo where ChatGroupID =" +GroupID);
    query2.exec("SELECT UserID FROM ChatGroup where ChatGroupID =" +GroupID);
    while(query1.next())
    {
        for(int i=0; i<3;++i)
        {
            GroupInfo.append(query1.value(i).toString()+"$");
        }
        GroupInfo.append(query1.value(3).toString()+"%");
    }

    while(query2.next())
    {
        GroupInfo.append(GetUserInfo(query2.value(0).toString())+"$");
    }

    return GroupInfo;
}

void UserData::CreateNewUser()
{
    //    INSERT INTO `Chat`.`UserInfo` (`UserID`, `UserName`, `UserSex`, `UserAge`, `UserAddress`, `UserPS`,) VALUES ('1', '李四', '男', '21', '芜湖', '程序猿！！！');
    bool value;
    QSqlQuery query;
    value =query.exec("INSERT INTO `Chat`.`User` (`UserID`, `Password`) VALUES ("+newUser.UserID+","+newUser.Password+")");

    if(value)
        qDebug()<<"User add sucessful!";
    else
        qDebug()<<"User add failed!";
    value=query.exec("INSERT INTO `Chat`.`UserInfo` (`UserID`, `UserName`, `UserSex`, `UserAge`, `UserAddress`, `UserPS`, `UserAvatar`) VALUES ('"+newUserInfo.UserID+"','"+newUserInfo.UserName+"','"+newUserInfo.UserSex+"','"+newUserInfo.UserAge+"','"+newUserInfo.UserAddress+"','"+newUserInfo.UserPS+"',LOAD_FILE('"+newUserInfo.UserAvatar+"'))");
    if(value)
        qDebug()<<"UserInfo add sucessful!";
    else
        qDebug()<<"UserInfo add failed!";

}




















