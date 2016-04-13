#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
#include <QVector>
#include <QPixmap>
#include <QTcpSocket>
#include <QUdpSocket>
class UserData
{
public:
    UserData();
    typedef struct User_{
        QString UserID;
        QString Password;
        QString Client_Status;
        bool AutoLogin;
        bool RememberPwd;
    }User;


    typedef struct User_Status{
        QString UserID;
        QString UserIP;
        QString UserPort;
        QString UserStatus;
        void SetValue(QStringList sl)
        {
            UserID =sl[0];
            UserIP = sl[1];
            UserPort = sl[2];
            UserStatus = sl[3];

        }
    }UserStatus;
    typedef struct User_Info{

        /**
         * 基本信息
         */
        QString UserID;
        QString UserName;
        QString UserSex;
        QString UserAge;
        QString UserAddress;
        QString UserPS;
        QString UserAvatar;
        /**
         * IP地址和端口号以及目前状态
         */
        QString UserIP;
        QString UserPort;
        QString UserStatus;

        void SetValue(QStringList sl)
        {
                UserID = sl[0];
                UserName = sl[1];
                UserSex = sl[2];
                UserAge = sl[3];
                UserAddress = sl[4];
                UserPS = sl[5];
                UserAvatar = sl[6];
                UserIP = sl[7];
                UserPort = sl[8];
                UserStatus = sl[9];
        }
//        QPixmap AvatarPhoto;
    }UserInfo;




    typedef struct Friends_Info{
        QString GroupName;
        int Num;
        QVector<UserInfo> UserInfo_List;
    }FriendInfo;

//    static void Link();



    static QString LoginImagesPath;
    static QString FriendsImagesPath;
    static QString ChatViewImagesPath;
    static QString AvatarPath;
    static User Current_User;
    static QVector<User> User_List;
    static UserInfo OwnInfo;
    static UserData::User newUser;
    static UserData::UserInfo newUserInfo;
    static QVector<FriendInfo> Current_FriendInfo;
    static bool ChatWindow;
    static QString getIP();
    static QString getPort();
    static QUdpSocket *udpSocket;
    static qint32 port;
    static QStringList Status;

private slots:


};

#endif // USERDATA_H
