#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "thread.h"
#include "qtimer.h"

namespace Ui {
class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

private slots:
    void writeOne();
    void readOne(QString txt);
    void on_btnAppend_clicked();
    void on_btnThread_clicked();
    void on_btnTimer_clicked();

private:
    Ui::frmMain *ui;

    QTimer *timer;
    Thread *thread;

};

#endif // WIDGET_H
