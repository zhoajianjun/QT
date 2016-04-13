#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(m_pixmapBg.rect(), m_pixmapBg);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    this->move(e->globalPos() - m_pointStart);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_pointPress = e->globalPos();
    m_pointStart = m_pointPress - this->pos();

}

void MainWindow::setNomalStyle()
{
    QFile styleSheet(":/res/qss/style_360.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll());
}



void MainWindow::on_menuBtn_clicked()
{
    m_menu->exec(this->mapToGlobal(QPoint(700, 20)));
}

void MainWindow::initData()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_menu = new QMenu();
    m_menu->addAction(tr("AA"));
    m_menu->addAction(tr("BB"));
    m_menu->addAction(tr("CC"));
    m_menu->addSeparator();
    m_menu->addAction(tr("DD"));
    m_menu->addAction(tr("EE"));
    m_menu->addAction(tr("FF"));
    m_menu->addAction(tr("HH"));
    m_menu->addAction(tr("JJ"));
    m_AactionAboutQt = new QAction(tr("&About Qt"), this);
    connect(m_AactionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    m_menu->addAction(m_AactionAboutQt);

    ///背景加载;
    m_pixmapBg.load(":/res/image/frame.png");

    m_vecBtn.push_back(ui->pushButton);
    m_vecBtn.push_back(ui->pushButton_2);
    m_vecBtn.push_back(ui->pushButton_3);
    m_vecBtn.push_back(ui->pushButton_4);
    m_vecBtn.push_back(ui->pushButton_5);
    m_vecBtn.push_back(ui->pushButton_6);
    m_vecBtn.push_back(ui->pushButton_7);
    m_vecBtn.push_back(ui->pushButton_8);
    m_vecBtn.push_back(ui->pushButton_9);

    for (int i = 0; i != m_vecBtn.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn[i]->setCheckable(true);
        m_vecBtn[i]->setAutoExclusive(true);
    }

    ///状态栏加上链接QLabel;
    ui->label_checkUpdate->setText(
                tr("<a href=http://www.360.cn>"
                   "<font color=white>uu</font></a>"));
    ui->label_checkUpdate->setOpenExternalLinks(true);

     setNomalStyle();
}


void MainWindow::on_pushButton_clicked()
{
    setCurrentWidget();
}

void MainWindow::on_pushButton_2_clicked()
{
    setCurrentWidget();
}

void MainWindow::on_pushButton_3_clicked()
{
    setCurrentWidget();
}

void MainWindow::on_pushButton_4_clicked()
{
    setCurrentWidget();
}

void MainWindow::on_pushButton_5_clicked()
{
    setCurrentWidget();
}

void MainWindow::on_pushButton_6_clicked()
{
    setCurrentWidget();
}

void MainWindow::on_pushButton_7_clicked()
{
    setCurrentWidget();
}

void MainWindow::on_pushButton_8_clicked()
{
     setCurrentWidget();
}

void MainWindow::on_pushButton_9_clicked()
{
    setCurrentWidget();
}

void MainWindow::setCurrentWidget()
{
    for (int i = 0; i != m_vecBtn.size(); ++i)
    {
        if ( m_vecBtn[i]->isChecked() )
        {
            qDebug()<<"MM"<<endl;
            ui->stackedWidget->setCurrentIndex(i);
        }
    }
}

void MainWindow::on_closeBtn_clicked()
{
    this->close();
}

//void MainWindow::on_nomalBtn_clicked()
//{
//    qDebug()<<"["<<__FILE__<<__LINE__<<__FUNCTION__<<__DATE__<<__TIME__<<"]";
//    this->showMaximized();
//}

