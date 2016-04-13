#include "logining.h"
#include "ui_logining.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "userdata.h"
#include "myhelper.h"
#include <QTimer>
#include "login.h"
#include "friendslist.h"
Logining::Logining(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logining)
{

    ui->setupUi(this);
    form_init();
    socket_init();

}
void Logining::socket_init()
{
    ui->login_button->setText("取消");
    tcpClient=new QTcpSocket(this);
    tcpClient->abort();//取消原有连接
    tcpClient->connectToHost("127.0.0.1",12345);
    if (tcpClient->waitForConnected(1000))
    {
        ui->CurrentStatus_label->setText("正在登录...");
        tcpClient->write(("#Login#"+UserData::Current_User.UserID+"#"+UserData::Current_User.Password
                          +"#"+UserData::Current_User.Client_Status).toLocal8Bit());

    }
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(ReadData()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}
void Logining::on_login_button_clicked()
{
    if(ui->login_button->text() == "取消")
    {
        tcpClient->disconnectFromHost();
        tcpClient->waitForDisconnected(1000);
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
        {
            ui->login_button->setText("登录");

        }
        tcpClient->abort();
        this->close();
        Login *w =new Login();
        w->show();
    }
    else {
        tcpClient->connectToHost("127.0.0.1",12345);
        if (tcpClient->waitForConnected(1000))
        {
            ui->CurrentStatus_label->setText("正在链接...");
            tcpClient->write(("#Login#"+UserData::Current_User.UserID+"#"+UserData::Current_User.Password
                              +"#"+UserData::Current_User.Client_Status).toLocal8Bit());
        }
    }

}

void Logining::ReadData()
{

    QByteArray buffer=tcpClient->readAll();
    QString s=QVariant(buffer).toString();
    if(buffer == "false")
    {
        ui->CurrentStatus_label->setText("密码或帐号错误!");
    }
    else
    {
        ui->CurrentStatus_label->setText("正在登录...");

        QStringList Info = s.split("&");
        QStringList OwnInfoString = Info[1].split("#");
        UserData::OwnInfo.SetValue(OwnInfoString);
        QStringList GroupsInfoString = Info[2].split("|");

        for(int i =0;i<GroupsInfoString.count()-1;i++)
        {
            QStringList FriendsInfoString = GroupsInfoString[i].split("@");
            UserData::FriendInfo fi;
            fi.GroupName = FriendsInfoString[0];
            UserData::UserInfo user;
            user.SetValue(FriendsInfoString[1].split("#"));
            bool is =false;

            for(QVector<UserData::FriendInfo>::iterator iter = UserData::Current_FriendInfo.begin(); iter!=UserData::Current_FriendInfo.end();++iter)
            {
                if(fi.GroupName == iter->GroupName)
                {
                    iter->Num +=1;
                    iter->UserInfo_List.append(user);
                    is =true;
                    break;
                }

            }
            if(!is)
            {

                fi.UserInfo_List.append(user);
                fi.Num =1;
                UserData::Current_FriendInfo.append(fi);
            }

        }

        FriendsList *w = new FriendsList();
        w->show();
        this->close();


    }

}

void Logining::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    ui->login_button->setText("登录");
    ui->CurrentStatus_label->setText("连接服务器失败");
}

void Logining::form_init()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    MyHelper::FormInCenter(this);
    progressBar_init();
    timer = new QTimer();
    timer->setInterval(10);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(ProgressValue()));
}

void Logining::ProgressValue()
{

//    Progress_value += 1;
    ++Progress_value %=100;
    ui->progressBar->setValue(Progress_value);

}
void Logining::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(50,0,QPixmap(UserData::LoginImagesPath));//绘制图片到窗口
}
Logining::~Logining()
{
    delete ui;
}

void Logining::progressBar_init()
{
    Progress_value = 0;
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(Progress_value);

}
void Logining::on_Close_pushButton_clicked()
{
    exit(0);
}

void Logining::mousePressEvent(QMouseEvent *event)

{

    if(event->button()==Qt::LeftButton)

    {

        dragPosition=event->globalPos()-frameGeometry().topLeft();

        event->accept();

    }

    if(event->button()==Qt::RightButton)
    {
    }
}

void Logining::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口

        event->accept();
    }
}

