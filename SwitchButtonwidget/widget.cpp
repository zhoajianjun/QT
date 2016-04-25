#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_btn=new SwitchButton(this);
}

Widget::~Widget()
{
    delete ui;
}
