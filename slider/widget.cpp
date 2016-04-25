#include "widget.h"
#include "ui_widget.h"
#include "slider.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    slider=new Slider(this);
    slider->setGeometry(20,20,500,20);

}

Widget::~Widget()
{
    delete ui;
}
