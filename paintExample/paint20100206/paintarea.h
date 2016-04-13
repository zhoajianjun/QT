#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
class PaintArea : public QWidget
{
public:
    PaintArea();
protected:
    void paintEvent(QPaintEvent *);   //�ػ��¼�
    void mousePressEvent(QMouseEvent *);  //��갴���¼�
    void mouseMoveEvent(QMouseEvent *);   //����ƶ��¼�
    void mouseReleaseEvent(QMouseEvent *);   //����ͷ��¼�

    void paint(QImage& theImage);   //���л���
private:
    QImage image;    //QImage��������������ϻ�ͼ
    QRgb backColor;  //QRgb��ɫ���󣬴洢image�ı���ɫ

    QPoint lastPoint,endPoint; //��������������������ָ���ǰ����������
};
#endif // PAINTAREA_H
