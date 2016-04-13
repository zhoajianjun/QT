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
    resize(700,500);   //主窗口大小设为700*500
    area = new PaintArea;
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);   //scrollArea对象的背景色设为Dark
    scrollArea->setWidget(area);     //将画布添加到scrollArea中
    scrollArea->widget()->setMinimumSize(800,600);  //scrollArea初始化大小设为800*600

    setCentralWidget(scrollArea);    //将scrollArea加入到主窗口的中心区
    isSaved = false;
    curFile = tr("未命名.png");
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
                                    tr("打开文件"), QDir::currentPath());
         if (!fileName.isEmpty())
         {
             area->openImage(fileName);
             scrollArea->widget()->resize(area->getImageSize());
             //获得图片的大小，然后更改scrollArea的大小
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
        box = QMessageBox::warning(this,tr("保存文件"),tr("图片已经改变，是否保存？"),
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
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    if(fileName.isEmpty())
    {
        return false;
    }
    else return saveFile(fileName);
}

void MainWindow::on_action_N_triggered()  //新建菜单
{
   doNew();
}

void MainWindow::on_action_O_triggered()  //打开菜单
{
    doOpen();
}

void MainWindow::on_action_S_triggered()  //保存菜单
{
    doFileSave();
}

void MainWindow::on_action_A_triggered()  //另存为菜单
{
    doFileSaveAs();
}

void MainWindow::on_action_X_triggered()   //退出菜单
{
    if(maybeSave())
        qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent *event)   //关闭事件
{
    if(maybeSave())
        qApp->quit();
    else event->ignore();
}

void MainWindow::on_action_P_triggered()  //打印菜单
{
    area->doPrint();
}
