#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
signals:

public slots:
private:
    QPoint dragPosition;

};

#endif // MYWIDGET_H
