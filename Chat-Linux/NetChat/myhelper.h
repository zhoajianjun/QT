#ifndef MYHELPER_H
#define MYHELPER_H

#include <QObject>
#include <QDesktopWidget>
class MyHelper : public QObject
{
    Q_OBJECT
public:
    explicit MyHelper(QObject *parent = 0);

    static void FormInCenter(QWidget *frm)
    {
        QDesktopWidget desktop;
        int screenX=desktop.availableGeometry().width();
        int screenY=desktop.availableGeometry().height();
        int wndX=frm->width();
        int wndY=frm->height();
        QPoint movePoint(screenX/2-wndX/2,screenY/2-wndY/2);
        frm->move(movePoint);
    }
    static void FormNotResize(QWidget *frm)
    {
        frm->setFixedSize(frm->width(),frm->height());
    }

signals:

public slots:

};

#endif // MYHELPER_H
