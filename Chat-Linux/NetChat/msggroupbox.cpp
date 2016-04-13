#include "msggroupbox.h"
#include <QDateTime>
#include <userdata.h>
MsgGroupBox::MsgGroupBox(int type,QString Avatar,QString Msg)
{
    init();
    QPixmap pix;
    pix.load(UserData::AvatarPath+Avatar);
    AvatarLabel->setPixmap(pix.scaled(pix.width()/2,pix.height()/2,Qt::KeepAspectRatio));

//    MsgLabel->setAlignment(Qt::AlignCenter);
    MsgLabel->setText(Msg);


    if(1 == type)
    {
        MsgLabel->setStyleSheet("color: white;font:18pt;");
        AvatarLabel->setGeometry(5,5,50,50);
        TimeLabel->setGeometry(50,5,50,30);
        TimeLabel->adjustSize();
        MsgLabel->setGeometry(50,25,80,30);
        MsgLabel->adjustSize();
        MsgLabel->setAlignment(Qt::AlignLeft);
    }
    else{

        MsgLabel->setStyleSheet("color: rgb(169, 49, 229);font:18pt;");
        AvatarLabel->setGeometry(this->width()-125,5,50,50);
        TimeLabel->setGeometry(AvatarLabel->x()-TimeLabel->width()-5,5,50,30);
        TimeLabel->adjustSize();
        MsgLabel->adjustSize();
        MsgLabel->setGeometry(AvatarLabel->x()-MsgLabel->width()-5,25,80,30);
        MsgLabel->adjustSize();
        MsgLabel->setAlignment(Qt::AlignRight);

    }

}
MsgGroupBox::MsgGroupBox(QString Record)
{

    init();
    QStringList record = Record.split("|");
    QPixmap pix;
    TimeLabel->setText(record[1]);
    TimeLabel->adjustSize();

    MsgLabel->setText(record[3]);
    if(0 == record[0].toInt())
    {
        pix.load(UserData::AvatarPath+UserData::OwnInfo.UserAvatar);
        AvatarLabel->setPixmap(pix.scaled(pix.width()/2,pix.height()/2,Qt::KeepAspectRatio));

        MsgLabel->setStyleSheet("color: rgb(169, 49, 229);font:18pt;");
        AvatarLabel->setGeometry(this->width()-125,5,50,50);
        TimeLabel->setGeometry(AvatarLabel->x()-TimeLabel->width()-5,5,50,30);
        TimeLabel->adjustSize();
        MsgLabel->adjustSize();
        MsgLabel->setGeometry(AvatarLabel->x()-MsgLabel->width()-5,25,80,30);
        MsgLabel->adjustSize();
        MsgLabel->setAlignment(Qt::AlignRight);

    }
    else{
        pix.load(UserData::AvatarPath+record[2]+".png");
        AvatarLabel->setPixmap(pix.scaled(pix.width()/2,pix.height()/2,Qt::KeepAspectRatio));
        MsgLabel->setStyleSheet("color: white;font:18pt;");
        AvatarLabel->setGeometry(5,5,50,50);
        TimeLabel->setGeometry(50,5,50,30);
        TimeLabel->adjustSize();
        MsgLabel->adjustSize();
        MsgLabel->setGeometry(50,25,80,30);
        MsgLabel->adjustSize();
        MsgLabel->setAlignment(Qt::AlignLeft);
    }

}

void MsgGroupBox::init()
{
    AvatarLabel = new QLabel(this);
    MsgLabel = new QLabel(this);
    TimeLabel = new QLabel(this);

    TimeLabel->setStyleSheet("color: rgb(58, 106, 218);");
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    TimeLabel->setText(time);
    TimeLabel->adjustSize();
}
