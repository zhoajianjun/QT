#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "slider.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    Slider *slider;
};

#endif // WIDGET_H
