#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QMenu>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_menuBtn=new QPushButton(this);
    m_menuBtn->setGeometry(100,100,35,25);
    m_menu=new QMenu();
    m_menu->setFixedWidth(50);
    m_menu->addAction(tr("AA"));
    m_menu->addAction(tr("BB"));
    m_menu->addAction(tr("CC"));
    m_menu->addSeparator();
    m_menu->addAction(tr("DD"));
    m_menu->addAction(tr("EE"));
    m_AactionAboutQt = new QAction(tr("&About Qt"), this);
    connect(m_AactionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    m_menu->addAction(m_AactionAboutQt);

    connect(m_menuBtn,&QPushButton::clicked,this,&Widget::on_menuBtn_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_menuBtn_clicked()
{
    m_menu->exec(this->mapToGlobal(QPoint(100,125)));
}
