#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "donewdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>

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

    creatColorComboBox(ui->penColorComboBox);   //������ɫ��Ͽ�
    creatColorComboBox(ui->brushColorComboBox);   //�����ɫ��Ͽ�
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

void MainWindow::on_action_4_triggered()    //�Ŵ�˵�
{
    area->zoomIn();
}

void MainWindow::on_action_5_triggered()    //��С�˵�
{
    area->zoomOut();
}

void MainWindow::on_action_6_triggered()    //��ԭ�˵�
{
    area->zoom_1();
}

void MainWindow::on_action_7_triggered()    //��ת�˵�
{
    area->doRotate();
}

void MainWindow::on_action_8_triggered()    //����˵�
{
    area->doShear();
}

void MainWindow::on_action_10_triggered()    //��ղ˵�
{
    area->doClear();
}

void MainWindow::on_action_11_triggered()   //��ͼ�������˵�
{
    ui->dockWidget->show();
}

void MainWindow::creatColorComboBox(QComboBox *comboBox)
{
    QPixmap pix(16,16);
    QPainter painter(&pix);

    painter.fillRect(0,0,16,16,Qt::black);   //�Ȼ���һ��16*16��СͼƬ��Ȼ�����Ϳɫ
    comboBox->addItem(QIcon(pix),tr("��ɫ"),Qt::black);   //���ø�ͼƬ��Ϊ��Ͽ���Ŀ��ͼ��
    painter.fillRect(0,0,16,16,Qt::white);
    comboBox->addItem(QIcon(pix),tr("��ɫ"),Qt::white);
    painter.fillRect(0,0,16,16,Qt::red);
    comboBox->addItem(QIcon(pix),tr("��ɫ"),Qt::red);
    painter.fillRect(0,0,16,16,Qt::green);
    comboBox->addItem(QIcon(pix),tr("��ɫ"),Qt::green);
    painter.fillRect(0,0,16,16,Qt::blue);
    comboBox->addItem(QIcon(pix),tr("��ɫ"),Qt::blue);
    painter.fillRect(0,0,16,16,Qt::yellow);
    comboBox->addItem(QIcon(pix),tr("��ɫ"),Qt::yellow);

    comboBox->addItem(tr("����ɫ"),Qt::transparent);  //��͸��
}

void MainWindow::on_shapeComboBox_currentIndexChanged(QString shape) //ѡ��ͼ����Ͽ�
{
    if(shape == tr("��"))
        area->setShape(PaintArea::None);   //����PaintArea���е�ö�ٱ���
    else if(shape == tr("����"))
        area->setShape(PaintArea::Rectangle);
    else if(shape == tr("ֱ��"))
        area->setShape(PaintArea::Line);
    else if(shape == tr("��Բ"))
        area->setShape(PaintArea::Ellipse);
}

void MainWindow::on_penStyleComboBox_currentIndexChanged(QString style)   //���ʷ����Ͽ�
{
    if(style == tr("ʵ��"))
    {
        area->setPenStyle(Qt::SolidLine);
    }
    else if(style == tr("����"))
    {
        area->setPenStyle(Qt::DotLine);
    }
}

void MainWindow::on_penWidthSpinBox_valueChanged(int width)   //�����߿���Ͽ�
{
    area->setPenWidth(width);
}

void MainWindow::on_penColorComboBox_currentIndexChanged(int index)   //������ɫ��Ͽ�
{
    QColor color = ui->penColorComboBox->itemData(index,Qt::UserRole).value<QColor>();

    area->setPenColor(color);
}

void MainWindow::on_brushColorComboBox_currentIndexChanged(int index)   //�����ɫ��Ͽ�
{
    QColor color = ui->brushColorComboBox->itemData(index,Qt::UserRole).value<QColor>();

    area->setBrushColor(color);
}
