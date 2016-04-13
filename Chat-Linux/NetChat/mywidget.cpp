#include "mywidget.h"
#include <QMouseEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
}
void MyWidget::mousePressEvent(QMouseEvent *event)
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

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口
        event->accept();
    }
}
