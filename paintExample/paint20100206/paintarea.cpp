#include "paintarea.h"
#include <QPainter>

PaintArea::PaintArea()
{
    image = QImage(400,300,QImage::Format_RGB32);  //�����ĳ�ʼ����С��Ϊ400*300��ʹ��32λ��ɫ
    backColor = qRgb(255,255,255);    //������ʼ������ɫʹ�ð�ɫ
    image.fill(backColor);
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)  //������������
    {
        lastPoint = event->pos();   //������ָ��ĵ�ǰ������Ϊ��ʼ����
    }
}
void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)   //������������ŵ�ͬʱ�ƶ����
    {
        endPoint = event->pos();  //������ָ��ĵ�ǰ������Ϊ��ֹ����
        paint(image);   //����ͼ��
    }
}
void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)   //����������ͷ�
    {
        endPoint = event->pos();
        paint(image);
    }
}

void PaintArea::paint(QImage &theImage)
{
    QPainter pp(&theImage);   //��theImage�ϻ�ͼ
    pp.drawLine(lastPoint,endPoint);   //����ʼ�������ֹ�������ֱ��
    lastPoint = endPoint;  //����ֹ�����Ϊ��ʼ����
    update();   //���и��½�����ʾ�������𴰿��ػ��¼����ػ洰��
}
