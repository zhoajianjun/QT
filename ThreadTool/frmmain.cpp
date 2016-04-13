#include "frmmain.h"
#include "ui_frmmain.h"
#include "app.h"
#include "qdatetime.h"
#include "qdesktopwidget.h"

#define _TIME_ qPrintable (QTime::currentTime().toString("now : hh:mm:ss:zzz"))

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    this->showMaximized();

    timer=new QTimer(this);
    timer->setInterval(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(writeOne()));

    thread=new Thread;
    connect(thread,SIGNAL(readOne(QString)),this,SLOT(readOne(QString)));
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::writeOne()
{
    App::list.append(_TIME_);
}

void frmMain::readOne(QString txt)
{
    ui->txtOut->append(txt);
}

void frmMain::on_btnAppend_clicked()
{
    App::list.append(ui->txtIn->text());
}

void frmMain::on_btnThread_clicked()
{
    if (ui->btnThread->text()=="start thread"){
        thread->start();
        ui->btnThread->setText("stop thread");
        ui->txtOut->append("start thread ok");
    }else{
        thread->stop();
        ui->btnThread->setText("start thread");
        ui->txtOut->append("stop thread ok");
    }
}

void frmMain::on_btnTimer_clicked()
{
    if (ui->btnTimer->text()=="start timer"){
        timer->start();
        ui->btnTimer->setText("stop timer");
        ui->txtOut->append("start timer ok");
    }else{
        timer->stop();
        ui->btnTimer->setText("start timer");
        ui->txtOut->append("stop timer ok");
    }
}
