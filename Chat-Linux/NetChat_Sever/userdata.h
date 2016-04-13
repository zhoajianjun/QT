#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
#include <QVector>
#include <QPixmap>
class UserData
{
public:
    UserData();
    static void Link();
    static void GetUser();
    static QString GetUserInfo(QString UserID);
    static QString GetFriendsInfo(QString UserID);
    static void CreateNewUser();
    static bool Verify(QString id,QString pwd);
    static bool IsFriend(QString id1,QString id2);
    static QString getIP();
    static QString GetGroupInfo(QString GroupID);
    static QString GetUserGroup(QString UserID);


    typedef struct User_{
        QString UserID;
        QString Password;
    }User;
    typedef struct User_Info{
        QString UserID;
        QString UserName;
        QString UserSex;
        QString UserAge;
        QString UserAddress;
        QString UserPS;
        QString UserAvatar;

        QString UserIP;
        QString UserPort;
        QString status;
//        QPixmap AvatarPhoto;
    }UserInfo;
    typedef struct Client_{
        QString ClientID;
        QString Status;
        QString IP;
        QString Port;
        bool online;
    }Client;
    static QVector<Client> Client_List;
    static QVector<User> User_List;
    static UserInfo FriendInfo;
    static UserData::User newUser;
    static UserData::UserInfo newUserInfo;
    static QVector<UserInfo> UserInfo_List;

    static QString port;
    static QString ip;

};

#endif // USERDATA_H
