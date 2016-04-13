#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
class PaintArea : public QWidget
{
public:
    PaintArea();
    void setImageSize(int width,int height);
    void setImageColor(QColor color);

    bool isModified() const { return modified; }  //�жϻ��������Ƿ񱻸��Ĺ�
    bool saveImage(const QString &fileName, const char *fileFormat); //����ͼƬ
    bool openImage(const QString &fileName);  //��ͼƬ

    QSize getImageSize();
    void doPrint();

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
    bool modified;   //��־�����Ƿ񱻸��Ĺ�
};
#endif // PAINTAREA_H
