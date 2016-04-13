#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "donewdialog.h"
#include <QMessageBox>
#include <QFileDialog>

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
    isSaved = false;
    curFile = tr("δ����.png");
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


void MainWindow::doOpen()
{
    if (maybeSave())
    {
         QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("���ļ�"), QDir::currentPath());
         if (!fileName.isEmpty())
         {
             area->openImage(fileName);
             scrollArea->widget()->resize(area->getImageSize());
             //���ͼƬ�Ĵ�С��Ȼ�����scrollArea�Ĵ�С
             isSaved = true;
             curFile = fileName;
         }
    }
}
void MainWindow::doNew()
{
    if(maybeSave())
    {
        DoNewDialog dlg;
        if(dlg.exec() == QDialog::Accepted)
        {
            int width = dlg.getWidth();
            int height = dlg.getHeight();
            area->setImageSize(width,height);
            scrollArea->widget()->resize(width,height);
            area->setImageColor(dlg.getBackColor());
            isSaved = false;
        }
    }
}

bool MainWindow::maybeSave()
{
    if(area->isModified())
    {
        QMessageBox::StandardButton box;
        box = QMessageBox::warning(this,tr("�����ļ�"),tr("ͼƬ�Ѿ��ı䣬�Ƿ񱣴棿"),
                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(box == QMessageBox::Yes)
        {
            return doFileSave();
        }
        else if(box == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

bool MainWindow::doFileSave()
{
    if(isSaved)
    {
        return saveFile(curFile);
    }
    else  return doFileSaveAs();
}

bool MainWindow::saveFile(QString fileName)
{
    if(area->saveImage(fileName,"png"))
    {
        isSaved = true;
        return true;
    }
    else return false;
}

bool MainWindow::doFileSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("���Ϊ"),curFile);
    if(fileName.isEmpty())
    {
        return false;
    }
    else return saveFile(fileName);
}

void MainWindow::on_action_N_triggered()  //�½��˵�
{
   doNew();
}

void MainWindow::on_action_O_triggered()  //�򿪲˵�
{
    doOpen();
}

void MainWindow::on_action_S_triggered()  //����˵�
{
    doFileSave();
}

void MainWindow::on_action_A_triggered()  //���Ϊ�˵�
{
    doFileSaveAs();
}

void MainWindow::on_action_X_triggered()   //�˳��˵�
{
    if(maybeSave())
        qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent *event)   //�ر��¼�
{
    if(maybeSave())
        qApp->quit();
    else event->ignore();
}

void MainWindow::on_action_P_triggered()  //��ӡ�˵�
{
    area->doPrint();
}
