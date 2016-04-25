#include "messagebox.h"
#include "iconhelper.h"

MessageBox::MessageBox(QWidget *parent)
    : QDialog(parent)
{
    InitStyle();
    SetMessage("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",0);
}

MessageBox::~MessageBox()
{

}

void MessageBox::InitStyle()
{
//    this->setProperty("Form", true);
//    this->setProperty("CanMove", true);
    resize(282,156);


    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    m_mainWidget=new QWidget(this);
    m_mainWidget->setGeometry(0,0,282,30);
    m_mainWidget->setStyleSheet("QWidget{"
                                "background:#EAF7FF;"
                                "border:1px solid #C0DCF2;"
                                "border-radius:0px;"
                                "}");
    m_lab=new QLabel(this);
    m_lab->setGeometry(0,0,30,30);
    m_labTitle=new QLabel(this);
    m_labTitle->setGeometry(30,0,width()-60,0);
    m_closeBtn=new QPushButton(this);
    m_closeBtn->setGeometry(width()-30,0,30,30);
    IconHelper::Instance()->SetIcon(m_lab, QChar(0xf015));
    IconHelper::Instance()->SetIcon(m_closeBtn, QChar(0xf00d));
    m_labIcoMain=new QLabel(this);
    m_labIcoMain->setGeometry(20,40,40,40);
    m_labIcoMain->setMinimumSize(QSize(40, 40));
    m_labIcoMain->setMaximumSize(QSize(40, 40));
    m_labInfo=new QLabel(this);
    m_labInfo->setGeometry(75,30,width()-100,30);
    setWindowTitle(m_labTitle->text());


    connect(m_closeBtn,&QPushButton::clicked,this,&MessageBox::close);
}

void MessageBox::SetMessage(QString msg, int type)
{

    if (type == 0) {
        m_labIcoMain->setStyleSheet("border-image: url(:/images/msg_info.png);");
        //ui->btnCancel->setVisible(false);
        m_labTitle->setText("提示");
    } else if (type == 1) {
       m_labIcoMain->setStyleSheet("border-image: url(:/images/msg_question.png);");
        m_labTitle->setText("询问");
    } else if (type == 2) {
        m_labIcoMain->setStyleSheet("border-image: url(:/images/msg_error.png);");
        //ui->btnCancel->setVisible(false);
        m_labTitle->setText("错误");
    }

    m_labInfo->setText(msg);
    this->setWindowTitle(m_labTitle->text());

}
