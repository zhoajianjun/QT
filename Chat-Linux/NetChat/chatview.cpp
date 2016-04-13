#include "chatview.h"
#include "ui_chatview.h"
#include <QPainter>
#include <QMouseEvent>
#include <chatitem.h>
#include <QHBoxLayout>

ChatView* ChatView::w = NULL;
ChatView::ChatView()
{
    form_init();

    contentsWidget = new QListWidget(this);
    contentsWidget->setIconSize(QSize(40,55));
    contentsWidget->setCurrentRow(0);
    contentsWidget->setStyleSheet("background-color: rgb(69, 171, 243);");
    pagesWidget = new QStackedWidget(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setMargin(0);
    horizontalLayout->setAlignment(this,Qt::AlignLeft);
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget,1);
    horizontalLayout->setStretchFactor(contentsWidget,1);
    horizontalLayout->setStretchFactor(pagesWidget,6);
    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));


}

void ChatView::addChat(UserData::UserInfo *it)
{
    //判定是否已存在此聊天窗口

    for(int i=0;i <Chating_UserId.count();++i)
    {
        if(it->UserID == Chating_UserId.at(i))
        {
            pagesWidget->setCurrentIndex(i);
            contentsWidget->setCurrentRow(i);
            return;

        }

    }


    ChatItem *newChat = new ChatItem(it);
    pagesWidget->addWidget(newChat);//添加至界面堆栈
    Chating_Widget.append(newChat);//添加至界面容器

    connect(newChat,SIGNAL(CloseCurrentWidget()),this,SLOT(CloseChat()));//绑定关闭函数

    Chating_UserId.append(it->UserID);
    QListWidgetItem *ChatFriend = new QListWidgetItem(contentsWidget);
    ChatFriend->setIcon(QPixmap(UserData::AvatarPath+it->UserAvatar));
    ChatFriend->setText(it->UserName);
    ChatFriend->setTextAlignment(Qt::AlignCenter);
    ChatFriend->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    contentsWidget->setCurrentRow(contentsWidget->count()-1);
    pagesWidget->setCurrentIndex(contentsWidget->currentRow());

}

void ChatView::CloseChat()
{
//删除已存界面和帐号等信息
    pagesWidget->removeWidget(pagesWidget->currentWidget());
    Chating_Widget.removeAt(contentsWidget->currentRow());
    Chating_UserId.removeAt(contentsWidget->currentRow());
    QListWidgetItem *item = contentsWidget->takeItem(contentsWidget->currentRow());
    delete item;
    if(pagesWidget->count()>0)
    {//仍有界面存在的话，设到第一项，没有界面的话，关闭窗口
        pagesWidget->setCurrentIndex(0);
        contentsWidget->setCurrentRow(0);
    }else{
        this->close();
    }
}


void ChatView::addMsg(int row, QString newMsg)
{
//收到信息的用户聊天窗口增加消息
    Chating_Widget.at(row)->ReciveMessage(newMsg);
}


ChatView::~ChatView()
{
    delete ui;
}
void ChatView::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
///
/// 以下为界面初始化函数
///

void ChatView::form_init()
{
    this->setGeometry(100,100,720,480);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

}
void ChatView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(0,0,QPixmap("./ChatImages/ChatView.png"));//绘制图片到窗口
}

void ChatView::mousePressEvent(QMouseEvent *event)

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

void ChatView::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口

        event->accept();
    }
}
