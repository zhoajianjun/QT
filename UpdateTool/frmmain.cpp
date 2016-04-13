#include "frmmain.h"
#include "ui_frmmain.h"
#include "api/myhelper.h"
#include "api/devicesearchapi.h"
#include "api/deviceupdateapi.h"

frmMain::frmMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->InitStyle();
    this->InitForm();
    myHelper::FormInCenter(this);    
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::InitStyle()
{
    if (App::UseStyle) {
        this->max = false;
        this->location = this->geometry();
        this->setProperty("Form", true);
        this->setProperty("CanMove", true);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

        IconHelper::Instance()->SetIcoClose(ui->btnMenu_Close);
        IconHelper::Instance()->SetIcoNormal(ui->btnMenu_Max);
        IconHelper::Instance()->SetIcoMin(ui->btnMenu_Min);
        IconHelper::Instance()->SetIcoMain(ui->lab_Ico, App::FontSize + 2);
        IconHelper::Instance()->SetIcoMenu(ui->btnMenu);

        connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
        if (App::UseTray) {
            connect(ui->btnMenu_Min, SIGNAL(clicked()), this, SLOT(hide()));
        } else {
            connect(ui->btnMenu_Min, SIGNAL(clicked()), this, SLOT(showMinimized()));
        }

#ifdef __arm__
        ui->btnMenu_Max->click();
        ui->widget_menu->setVisible(false);
#else
        ui->widget_title->installEventFilter(this);
#endif
    } else {
        this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
        this->resize(size().width(), size().height() - ui->widget_title->size().height());
        ui->widget_title->setVisible(false);
    }

    this->setWindowTitle(ui->lab_Title->text());
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->widget_title) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            this->on_btnMenu_Max_clicked();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void frmMain::InitForm()
{
    if (App::UseTray) {
        trayIcon = new QSystemTrayIcon(this);
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
        trayIcon->setIcon(QIcon(":/main.ico"));
        trayIcon->setToolTip(ui->lab_Title->text());

        QMenu *menu = new QMenu(QApplication::desktop());
        menu->addAction("主界面", this, SLOT(showNormal()));
        menu->addAction("退出", ui->btnMenu_Close, SLOT(click()));
        trayIcon->setContextMenu(menu);
        trayIcon->show();
    }

    QAction *act1 = new QAction("淡蓝色", this);
    QAction *act2 = new QAction("蓝色", this);
    QAction *act3 = new QAction("浅灰色", this);
    QAction *act4 = new QAction("深灰色", this);
    QAction *act5 = new QAction("灰色", this);
    QAction *act6 = new QAction("灰黑色", this);
    QAction *act7 = new QAction("黑色", this);
    QAction *act8 = new QAction("银色", this);
    QAction *act9 = new QAction("系统", this);

    ui->btnMenu->addAction(act1);
    ui->btnMenu->addAction(act2);
    ui->btnMenu->addAction(act3);
    ui->btnMenu->addAction(act4);
    ui->btnMenu->addAction(act5);
    ui->btnMenu->addAction(act6);
    ui->btnMenu->addAction(act7);
    ui->btnMenu->addAction(act8);
    ui->btnMenu->addAction(act9);

    connect(act1, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act2, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act3, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act4, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act5, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act6, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act7, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act8, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act9, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));

    //设置列数和列宽
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 180);
    ui->tableWidget->setColumnWidth(4, 100);

    //设置行高
    ui->tableWidget->setRowCount(100);
    for (int i = 0; i < 100; i++) {
        ui->tableWidget->setRowHeight(i, 25);
    }

    QStringList headText;
    headText << "IP地址" << "网关" << "子网掩码" << "MAC地址" << "防区号";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    deviceCount = 0;
    deviceSearch = new DeviceSearchAPI(this);
    if (!deviceSearch->Init()) {
        ui->btnSearch->setEnabled(false);
        myHelper::ShowMessageBoxErrorX("组播监听端口绑定失败!");
    } else {
        connect(deviceSearch, SIGNAL(receiveDevice(QString, QString, QString, QString, QString)),
                this, SLOT(ReceiveDevice(QString, QString, QString, QString, QString)));
    }
}

void frmMain::ChangeStyle()
{
    QAction *act = (QAction *)sender();
    QString name = act->text();

    QString style = ":/qss/blue.css";
    if (name == "淡蓝色") {
        style = ":/qss/blue.css";
    } else if (name == "蓝色") {
        style = ":/qss/dev.css";
    } else if (name == "浅灰色") {
        style = ":/qss/lightgray.css";
    } else if (name == "深灰色") {
        style = ":/qss/darkgray.css";
    } else if (name == "灰色") {
        style = ":/qss/gray.css";
    } else if (name == "灰黑色") {
        style = ":/qss/brown.css";
    } else if (name == "黑色") {
        style = ":/qss/black.css";
    } else if (name == "银色") {
        style = ":/qss/silvery.css";
    } else if (name == "系统") {
        App::UseStyle = false;
        App::WriteConfig();
        qApp->exit();
        myHelper::Sleep(10);
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }

    if (style != App::StyleName) {
        App::StyleName = style;
        myHelper::SetStyle(App::StyleName);
        App::WriteConfig();
    }
}

void frmMain::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcoNormal(ui->btnMenu_Max);
        ui->btnMenu_Max->setToolTip("最大化");
        this->setProperty("CanMove", true);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcoMax(ui->btnMenu_Max);
        ui->btnMenu_Max->setToolTip("还原");
        this->setProperty("CanMove", false);
    }
    max = !max;
}

void frmMain::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick: {
        showNormal();
        break;
    }
    default:
        break;
    }
}

void frmMain::on_btnSelect_clicked()
{
    ui->txtFile->setText(myHelper::GetFileName("所有文件(*)"));
}

void frmMain::on_btnSearch_clicked()
{
    deviceCount = 0;
    ui->tableWidget->clearContents();
    deviceSearch->Search();
}

void frmMain::on_btnUpdate_clicked()
{
    QString fileName = ui->txtFile->text();
    if (fileName.length() == 0) {
        myHelper::ShowMessageBoxError("请选择要发送的文件!");
        return;
    }

    int row = ui->tableWidget->currentRow();
    QString deviceIP = ui->tableWidget->item(row, 0)->data(0).toString();
    if (!myHelper::IsIP(deviceIP)) {
        myHelper::ShowMessageBoxError("设备IP地址为空或者非法!");
        return;
    }

    DeviceUpdateAPI::Instance()->Start(deviceIP, App::UpdatePort, fileName, ui->progressBar);
}

void frmMain::ReceiveDevice(QString ip, QString mask, QString gateway, QString mac, QString defenceID)
{
    QTableWidgetItem *itemIP = new QTableWidgetItem(ip);
    QTableWidgetItem *itemMask = new QTableWidgetItem(mask);
    QTableWidgetItem *itemGateway = new QTableWidgetItem(gateway);
    QTableWidgetItem *itemMac = new QTableWidgetItem(mac);
    QTableWidgetItem *itemDefenceID = new QTableWidgetItem(defenceID);

    ui->tableWidget->setItem(deviceCount, 0, itemIP);
    ui->tableWidget->setItem(deviceCount, 1, itemMask);
    ui->tableWidget->setItem(deviceCount, 2, itemGateway);
    ui->tableWidget->setItem(deviceCount, 3, itemMac);
    ui->tableWidget->setItem(deviceCount, 4, itemDefenceID);

    deviceCount++;
}

