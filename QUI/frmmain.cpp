#include "frmmain.h"
#include "ui_frmmain.h"
#include "api/myhelper.h"

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
    this->max = false;
    this->location = this->geometry();
    this->setProperty("Form", true);
    this->setProperty("CanMove", true);
    this->setWindowTitle(ui->lab_Title->text());
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    //安装事件监听器,让标题栏识别鼠标双击
    ui->lab_Title->installEventFilter(this);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d));
    IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096));
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068));
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015));

    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnMenu_Min, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void frmMain::InitForm()
{
    QStringList qssName;
    qssName << "黑色" << "灰黑色" << "灰色" << "浅灰色" << "深灰色" << "银色" << "淡蓝色" << "蓝色";
    ui->cboxStyle->addItems(qssName);
    myHelper::Sleep(300);
    ui->cboxStyle->setCurrentIndex(4);
}

void frmMain::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096));
        ui->btnMenu_Max->setToolTip("最大化");
        this->setProperty("CanMove", true);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf079));
        ui->btnMenu_Max->setToolTip("还原");
        this->setProperty("CanMove", false);
    }
    max = !max;
}

void frmMain::on_pushButton_clicked()
{
    myHelper::ShowMessageBoxInfo("恭喜你获得我公司送出的1000万元大礼一份!");
}

void frmMain::on_pushButton_2_clicked()
{
    int result = myHelper::ShowMessageBoxQuesion("确定真的不要我了吗?");
    if (result == 1) {
        myHelper::ShowMessageBoxInfo("你好狠心啊!");
    } else {
        myHelper::ShowMessageBoxInfo("亲爱的,我就知道你不会离开我的!");
    }
}

void frmMain::on_pushButton_3_clicked()
{
    myHelper::ShowMessageBoxError("天空飘来五个字!");
}

void frmMain::on_pushButton_5_clicked()
{
    bool ok;
    QString value = myHelper::ShowInputBox("请输入姓名:", ok);
    if (ok) {
        myHelper::ShowMessageBoxInfo("您输入的是:" + value);
    }
}

void frmMain::on_cboxStyle_currentIndexChanged(const QString &arg1)
{
    QString qssName = ui->cboxStyle->currentText();
    QString qssFile = ":/qss/lightgray.css";
    if (qssName == "黑色") {
        qssFile = ":/qss/black.css";
    } else if (qssName == "灰黑色") {
        qssFile = ":/qss/brown.css";
    } else if (qssName == "灰色") {
        qssFile = ":/qss/gray.css";
    } else if (qssName == "浅灰色") {
        qssFile = ":/qss/lightgray.css";
    } else if (qssName == "深灰色") {
        qssFile = ":/qss/darkgray.css";
    } else if (qssName == "银色") {
        qssFile = ":/qss/silvery.css";
    } else if (qssName == "淡蓝色") {
        qssFile = ":/qss/blue.css";
    } else if (qssName == "蓝色") {
        qssFile = ":/qss/dev.css";
    }

    myHelper::SetStyle(qssFile);
}
