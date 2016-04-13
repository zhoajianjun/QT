#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(700,500);   //主窗口大小设为700*500
    area = new PaintArea;
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);   //scrollArea对象的背景色设为Dark
    scrollArea->setWidget(area);     //将画布添加到scrollArea中
    scrollArea->widget()->setMinimumSize(800,600);  //scrollArea初始化大小设为800*600

    setCentralWidget(scrollArea);    //将scrollArea加入到主窗口的中心区
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
