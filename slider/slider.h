#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QPainter>
#include <QStyleOptionSlider>



class Slider : public QSlider
{
    Q_OBJECT
public:
    Slider(QWidget *parent=0);
    ~Slider() {}

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public:
    bool m_inBtnClicked;
    bool m_outBtnClicked;

private:
    int m_inPointX;
    int m_outPointX;
    QPoint m_point;

};

#endif // VIDEOWIDGETSLIDER_H
