#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QVector>
#include <QHBoxLayout>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QVector<QPushButton*> mbt;
private:
    QButtonGroup* m_btngroup;
    QPushButton* btn;
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;
    QPushButton* btn4;
    QHBoxLayout* m_hlayout;
};

#endif // WIDGET_H
