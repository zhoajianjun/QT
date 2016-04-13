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

    bool isModified() const { return modified; }  //判断画布内容是否被更改过
    bool saveImage(const QString &fileName, const char *fileFormat); //保存图片
    bool openImage(const QString &fileName);  //打开图片

    QSize getImageSize();
    void doPrint();

protected:
    void paintEvent(QPaintEvent *);   //重绘事件
    void mousePressEvent(QMouseEvent *);  //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *);   //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *);   //鼠标释放事件

    void paint(QImage& theImage);   //进行绘制
private:
    QImage image;    //QImage类对象，用于在其上绘图
    QRgb backColor;  //QRgb颜色对象，存储image的背景色

    QPoint lastPoint,endPoint; //定义两个坐标对象存放鼠标指针的前后两个坐标
    bool modified;   //标志画布是否被更改过
};
#endif // PAINTAREA_H
