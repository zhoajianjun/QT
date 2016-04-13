#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(700,500);   //�����ڴ�С��Ϊ700*500
    area = new PaintArea;
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);   //scrollArea����ı���ɫ��ΪDark
    scrollArea->setWidget(area);     //��������ӵ�scrollArea��
    scrollArea->widget()->setMinimumSize(800,600);  //scrollArea��ʼ����С��Ϊ800*600

    setCentralWidget(scrollArea);    //��scrollArea���뵽�����ڵ�������
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
