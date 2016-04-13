#include "groupitem.h"
#include "userdata.h"
#include "chatview.h"
#include <QEvent>
#include <friendslist.h>
GroupItem::GroupItem(QWidget *parent ,int x,int y,UserData::UserInfo *user) :
    QWidget(parent)
{

    this->setGeometry(x,y,260,75);
    init(user);
    this->installEventFilter(this);
    w = ChatView::getInstance();

}


bool GroupItem::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == this) {
        if (event->type() == QEvent::MouseButtonRelease) { //随便判断什么事件都可以了
            w->addChat(user);
            w->show();
            return true;
        } else {
            return false;
        }
    } else {
        return GroupItem::eventFilter(obj, event);
    }
}

void GroupItem::init(UserData::UserInfo *user)
{

    this->user = user;
    groupbox = new QGroupBox(this);
    groupbox->setStyleSheet("QGroupBox {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E0E0E0, stop: 1 #FFFFFF);border: 2px solid gray;border-radius: 5px;margin-top: 0px; /* leave space at the top for the title */}");
    groupbox->setGeometry(0,0,260,70);
    Avatar = new QLabel(groupbox);
    Status = new QLabel(groupbox);
    Name= new QLabel(groupbox);
    PS= new QLabel(groupbox);
    Avatar->setGeometry(5,5,50,50);
    Name->setGeometry(60,10,50,20);
    Status->setGeometry(210,10,50,20);
    PS->setGeometry(60,40,200,20);

    Name->setText(user->UserName);
    Status->setText(UserData::Status[user->UserStatus.toInt()]);
    if(user->UserStatus =="1")
    {
        Status->setStyleSheet("color:red;");
    }
    PS->setText(user->UserPS);
    avatar_images =QPixmap(UserData::AvatarPath+user->UserAvatar);
    Avatar->setScaledContents(true);
    Avatar->setPixmap(QPixmap(UserData::AvatarPath+user->UserAvatar));

    //    Avatar->show();

}
