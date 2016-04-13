#include "login.h"
#include "ui_login.h"
#include "userdata.h"
#include <QDebug>
#include <QMessageBox>
#include <friendslist.h>
#include <register.h>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include <QIcon>
#include <myhelper.h>
#include <logining.h>
#include <QCryptographicHash>
#include <QMenu>
#include <QAction>
#include <QFile>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{

    ui->setupUi(this);

    init();
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

//    systemTrayIcon= new QSystemTrayIcon();
//    systemTrayIcon->setIcon(QIcon("./images/logo.png"));
//    systemTrayIcon->setVisible(true);
//    systemTrayIcon->setToolTip(tr("我是托盘图标"));
    MyHelper::FormInCenter(this);
    MyHelper::FormNotResize(this);
    Status_init();

    UserData::LoginImagesPath = "./images/LoginBack.png";
}
void Login::init()
{
    Status =QString("在线/隐身/忙碌/离开/求扰/勿扰/离线").split("/");
    ui->register_label->installEventFilter(this);//注册事件
    userFile.setFileName("./UserInfo/User.cookies");

    if(!userFile.open(QIODevice::ReadWrite))
    {
        userFile.close();
        return;
    }
//    QTextStream in(&userFile);
//    QString line;
//    while (!in.atEnd())
//    {
//        line=in.readLine();
//        if(line == "")
//        {
//            continue;
//        }
//        QStringList user = line.split("|");

//    }
//    if()
//    {
//    }
}
void Login::Status_init()
{
    QMenu * menu = ui->Status_pushButton->getmenu();
    QActionGroup *actionGroup = new QActionGroup(this);
    menu->setStyleSheet("QMenu {color: white;background-color:#E78261; border: 1px solid black;width:70px;}"
                        "QMenu::item {background-color: transparent; }"
                        "QMenu::item:selected { background-color: #FF781F;}");
    action[0] = new QAction(QIcon(":/images/images/imonline.png"), tr("在线"), this);
    action[1] = new QAction(QIcon(":/images/images/imhidden.png"), tr("隐身"), this);
    action[2] = new QAction(QIcon(":/images/images/imbusy.png"), tr("忙碌"), this);
    action[3] = new QAction(QIcon(":/images/images/imaway.png"), tr("离开"), this);
    action[4] = new QAction(QIcon(":/images/images/imcallme.png"), tr("求扰"), this);
    action[5] = new QAction(QIcon(":/images/images/imsilent.png"), tr("勿扰"), this);

    ImagesIcon[0] = ":/images/images/status-online-1.svg";
    ImagesIcon[1] = ":/images/images/status-hidden-1.svg";
    ImagesIcon[2] = ":/images/images/status-busy-1.svg";
    ImagesIcon[3] = ":/images/images/status-away-1.svg";
    ImagesIcon[4] = ":/images/images/status-callme-1.svg";
    ImagesIcon[5] = ":/images/images/status-silent-1.svg";
    for(int i =0;i<6;i++)
    {

        menu->addAction(actionGroup->addAction(action[i]));
        action[i]->setCheckable(true);
        connect(action[i], SIGNAL(triggered()), this, SLOT(Status_Changed()));
    }
    action[0]->setChecked(true);


}
void Login::on_login_button_clicked()
{

    UserData::Current_User.UserID = Login::ui->userid_comboBox->currentText();
    QByteArray pwd;
    pwd = QCryptographicHash::hash (Login::ui->password_text->text().toLatin1(), QCryptographicHash::Md5 );
    UserData::Current_User.Password =pwd.toHex();

    for(int i=0;i<6;i++)
    {
        if(action[i]->isChecked())
        {
            UserData::Current_User.Client_Status = tr("%1").arg(i+1);
        }

    }
    qDebug()<<UserData::Current_User.Client_Status;

    if(Login::ui->AutoLogin_checkBox->isChecked())
    {
        UserData::Current_User.AutoLogin = true;
        UserData::Current_User.RememberPwd = true;
    }
    else {
        UserData::Current_User.AutoLogin = false;
        if(Login::ui->RemeberPwd_checkBox->isChecked())
        {
            UserData::Current_User.RememberPwd = true;
        }
        else {
            UserData::Current_User.RememberPwd = false;
        }
    }

    Logining *w = new Logining();
    w->show();
    this->close();
}

void Login::Status_Changed()
{
    for(int i =0;i<6;i++)
    {
        if(action[i]->isChecked())
        {
            ui->Status_pushButton->setIcon(QIcon(ImagesIcon[i]));
//            ui->Status_pushButton->setIcon(QIcon(":/images/status-busy-1.svg"));
               UserData::Current_User.Client_Status = tr("%1").arg(i+1);
               break;
        }
    }
}

void Login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(50,0,QPixmap(UserData::LoginImagesPath));//绘制图片到窗口
}
Login::~Login()
{
    delete ui;
}
void Login::mousePressEvent(QMouseEvent *event)

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

void Login::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口

        event->accept();
    }
}

bool Login::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == Login::ui->register_label) {
        if (event->type() == QEvent::MouseButtonRelease) { //随便判断什么事件都可以了

            Register *r = new Register();
            this->close();
            r->show();

            return true;
        } else {
            return false;
        }
    } else {
        return Login::eventFilter(obj, event);
    }
}






void Login::on_pushButton_clicked()
{
    exit(0);
}





void Login::on_Min_pushButton_clicked()
{
    this->hide();
    //this->isMinimized();
    //    event->ignore();
    if (this->systemTrayIcon->isVisible()) {
        hide();
    }
}

void Login::on_AutoLogin_checkBox_clicked()
{
    if(ui->AutoLogin_checkBox->isChecked())
    {
        ui->RemeberPwd_checkBox->setChecked(true);
    }

}

void Login::on_RemeberPwd_checkBox_clicked()
{
    if(ui->AutoLogin_checkBox->isChecked())
    {
        ui->RemeberPwd_checkBox->setChecked(true);
    }
}

void Login::on_userid_comboBox_editTextChanged(const QString &arg1)
{
    QString path =UserData::AvatarPath + arg1+".png";
    QFile avatar(path);
    if(!avatar.exists())
    {
        return;
    }
    ui->avatar_label->setPixmap(QPixmap(path));

}
