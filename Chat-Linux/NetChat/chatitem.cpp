#include "chatitem.h"
#include <msggroupbox.h>
#include <QHBoxLayout>
#include <QShortcut>
#include <QIODevice>
#include <QDateTime>
#include <QScrollBar>
#include <filetransfer.h>
#include <QSound>
ChatItem::ChatItem(QWidget *parent) :
    QWidget(parent)
{

}
ChatItem::ChatItem(UserData::UserInfo *it)
{
    init();
    user = it;
    Name->setText(it->UserName);
    Status->setText(UserData::Status[it->UserStatus.toInt()]);
    PS->setText(it->UserPS);
    IP = QHostAddress(it->UserIP);
    Port = it->UserPort.toInt();
    ChatNoteInit();
}


void ChatItem::ChatNoteInit()
{
    ChatNote.setFileName("./UserInfo/"+UserData::OwnInfo.UserID+"/"+user->UserID+".txt");
    if(!ChatNote.open(QIODevice::ReadWrite))
    {
        ChatNote.close();
        return;
    }

    QTextStream in(&ChatNote);
    QString line;
    while (!in.atEnd())
    {
        line=in.readLine();
        if(line == "")
        {
            continue;
        }
        MsgGroupBox *Msg = new MsgGroupBox(line);
        Msg->setFixedHeight(60);
        Chat_Widget->setFixedHeight(Chat_Widget->height()+Msg->height());
        Chat_Layout->addWidget(Msg);

    }


    ScrollBar->setMaximum(this->height());
    ScrollBar->setSliderPosition(ScrollBar->maximum());


}
void ChatItem::init()
{
    Num =0;
    //所有成员变量进行初始化
    Send_UdpSocket = new QUdpSocket(this);
    Chat_Widget = new QWidget;
    Chat_Layout = new QVBoxLayout;
    Chat_Widget->setLayout(Chat_Layout);
    Status = new QLabel(this);
    Name= new QLabel(this);
    PS= new QLabel(this);
    Chat_ScrollArea = new QScrollArea(this);
    Chat_TextEdit = new QTextEdit(this);
    Send_PushButton =new QPushButton(this);
    Expression_PushButton =new QPushButton(this);
    File_PushButton = new QPushButton(this);
    Camera_PushButton = new QPushButton(this);
    Clear_PushButton = new QPushButton(this);

    Close_PushButton = new QPushButton(this);
    ScrollBar=Chat_ScrollArea->verticalScrollBar();
    Chat_ScrollArea->setWidget(Chat_Widget);

    //设置控件位置
    Chat_Widget->setGeometry(0,0,600,60);
    Name->setGeometry(20,10,80,30);
    Status->setGeometry(110,15,50,20);
    PS->setGeometry(30,40,200,20);
    Chat_ScrollArea->setGeometry(10,60,600,270);
    Chat_ScrollArea->setMinimumSize(600,270);
    Chat_TextEdit->setGeometry(10,380,450,90);
    Expression_PushButton->setGeometry(10,340,30,30);
    File_PushButton->setGeometry(60,340,30,30);
    Camera_PushButton->setGeometry(110,340,30,30);
    Clear_PushButton->setGeometry(160,340,30,30);
    Close_PushButton->setGeometry(560,10,20,20);
    Send_PushButton->setGeometry(480,420,100,50);

    //设置控件样式表
    Name->setStyleSheet("font-size:18pt;color:white;");
    Status->setStyleSheet("font-size:12pt;color:red;");
    PS->setStyleSheet("font-size:15pt;color:white;");
    Chat_ScrollArea->setStyleSheet("QWidget{background-color: rgba(255, 255, 255, 0);}QScrollArea{background-color: rgba(255, 255, 255, 59);}");
    Chat_TextEdit->setStyleSheet("background-color: rgba(255, 255, 255, 59);");
    Send_PushButton->setStyleSheet(
                "QPushButton{color: white;font: bold 13pt;border:none;min-height: 24px;min-width: 60px;border-image: url(:/images/images/button-login.svg);}QPushButton:hover{color: lightgray; border-image: url(:/images/images/button-login-hover.svg);}QPushButton:pressed {color: lightgray;border-image: url(:/images/images/button-login-press.svg);padding-top: -15px;padding-bottom: -17px;}"
                );
    Expression_PushButton->setStyleSheet("QPushButton{border:none;}");
    File_PushButton->setStyleSheet("QPushButton{border:none;}");

    Camera_PushButton->setStyleSheet("QPushButton{border:none;}");
    Clear_PushButton->setStyleSheet("QPushButton{border:none;}");
    Close_PushButton->setStyleSheet("QPushButton{border-image: url(:/images/images/button-quit.svg); border:none;  } QPushButton:hover{border:none;border-image: url(:/images/images/button-quit.svg);} QPushButton:pressed{border:none;border-image: url(:/images/images/button-quit.svg);}");
    Close_PushButton->setFocusPolicy(Qt::NoFocus);
    Expression_PushButton->setFocusPolicy(Qt::NoFocus);
    File_PushButton->setFocusPolicy(Qt::NoFocus);
    Camera_PushButton->setFocusPolicy(Qt::NoFocus);
    Clear_PushButton->setFocusPolicy(Qt::NoFocus);
    Send_PushButton->setFocusPolicy(Qt::NoFocus);
    Send_PushButton->setText("发送");

    Expression_PushButton->setIcon(QIcon("face.ico"));
    Expression_PushButton->setIconSize(QSize(30,30));
    File_PushButton->setIcon(QIcon("file.ico"));
    File_PushButton->setIconSize(QSize(30,30));
    Camera_PushButton->setIcon(QIcon("camera.ico"));
    Camera_PushButton->setIconSize(QSize(30,30));
    Clear_PushButton->setIcon(QIcon("clear.ico"));
    Clear_PushButton->setIconSize(QSize(30,30));

    //滚动条初始化
    Chat_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Chat_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //槽链接
    connect(Send_PushButton,SIGNAL(clicked()),this, SLOT(SendMessage()));
    connect(Close_PushButton,SIGNAL(clicked()),this,SLOT(Close()));
    connect(File_PushButton,SIGNAL(clicked()),this,SLOT(FileTransferWindow()));
    connect(Clear_PushButton,SIGNAL(clicked()),this,SLOT(ClearMsg()));
}

void ChatItem::FileTransferWindow()
{

    fileTransfer = new FileTransfer;
    fileTransfer->Init(user);
    fileTransfer->show();

}

void ChatItem::ClearMsg()
{
    ChatNote.resize(0);
    ChatNote.close();
//    Chat_Layout->


}
void ChatItem::Close()
{
    ChatNote.close();
    this->close();

//    fileTransfer->close();
    emit CloseCurrentWidget();

}

void ChatItem::SendMessage()
{
    if(this->Chat_TextEdit->toPlainText() == "")
    {
        return;
    }
    QTextStream out(&ChatNote);
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    QString Record = "0|"+time+"|"+user->UserID+"|"+Chat_TextEdit->toPlainText();
    MsgGroupBox *newMsg = new MsgGroupBox(Record);

    QByteArray information = (UserData::OwnInfo.UserID+"|"+user->UserID+"|"+this->Chat_TextEdit->toPlainText()).toLatin1();
    Send_UdpSocket->writeDatagram(information,information.size(),IP,Port);

    out<<Record<<endl;
    newMsg->setFixedHeight(60);
    ++Num;
    Chat_Widget->setFixedHeight(Chat_Widget->height()+newMsg->height());
    Chat_Layout->addWidget(newMsg);

    Chat_TextEdit->clear();
    ScrollBar->setMaximum(this->height());
    ScrollBar->setSliderPosition(ScrollBar->maximum());

}

void ChatItem::ReciveMessage(QString msg)
{

    QTextStream out(&ChatNote);

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    QString Record = "1|"+time+"|"+user->UserID+"|"+msg;
    out<<Record<<endl;
    MsgGroupBox *newMsg = new MsgGroupBox(Record);
    newMsg->setFixedHeight(60);
    ++Num;
    Chat_Widget->setFixedHeight(Chat_Widget->height()+newMsg->height());
    Chat_Layout->addWidget(newMsg);
    ScrollBar->setMaximum(this->height());
    ScrollBar->setSliderPosition(ScrollBar->maximum());
}
