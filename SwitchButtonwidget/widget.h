#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "switchbutton.h"

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
    SwitchButton *m_btn;
};

#endif // WIDGET_H
