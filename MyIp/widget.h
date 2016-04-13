#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QHostInfo>
#include <QDebug>
#include <QNetworkInterface>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public:
    QString getIP();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
