#include "mylabel.h"
#include <QDebug>
MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
}
void MyLabel::mouseReleaseEvent(QMouseEvent * ev)
{
Q_UNUSED(ev)
emit clicked();

    qDebug()<<"&&&&&&&&&&&&7";
}
