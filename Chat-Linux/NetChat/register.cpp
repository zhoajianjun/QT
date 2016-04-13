#include "register.h"
#include "ui_register.h"
#include <QFileDialog>
#include <QDebug>
#include <login.h>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    QStringList test = QStringList()

            <<"男"<<"女"<<"保密";
    Register::ui->UserSex_comboBox->addItems(test);
    Register::ui->UserAvatar_label->installEventFilter(this);
}

Register::~Register()
{
    delete ui;
}
bool Register::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == Register::ui->UserAvatar_label) {
        if (event->type() == QEvent::MouseButtonRelease) { //随便判断什么事件都可以了
            imagePath ="./images/wenhao.png";
            imagePath.replace("\\","/");
            imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"/home/rcl",tr("Images (*.jpg *.png)"));
            if(!imagePath.isEmpty())
            {
                QImage *image= new QImage(imagePath);
                Register::ui->UserAvatar_label->setPixmap(QPixmap::fromImage(*image));
            }
            //            UPDATE `Chat`.`UserInfo` SET `UserPS`='我的未来我做主！！' WHERE `UserID`='123456789';

            return true;
        } else {
            return false;
        }
    } else {
        return Register::eventFilter(obj, event);
    }
}



void Register::on_Besure_Button_clicked()
{
    UserData::newUser.UserID = Register::ui->UserID_lineEdit->text();
    UserData::newUserInfo.UserID = Register::ui->UserID_lineEdit->text();
    UserData::newUser.Password = Register::ui->Password_lineEdit->text();
    UserData::newUserInfo.UserName = Register::ui->UserName_lineEdit->text();
    UserData::newUserInfo.UserSex =Register::ui->UserSex_comboBox->currentText();
    UserData::newUserInfo.UserAge = Register::ui->UserAge_lineEdit->text();
    UserData::newUserInfo.UserAddress = Register::ui->UserAddress_lineEdit->text();
    UserData::newUserInfo.UserPS = Register::ui->UserPS_textEdit->document()->toPlainText();
    UserData::newUserInfo.UserAvatar = imagePath;
//    UserData::CreateNewUser();

}

void Register::on_Back_Button_clicked()
{
    this->close();
    Login *login = new Login();
    login->show();
}

void Register::on_UserID_lineEdit_editingFinished()
{
    for(int i =0;i<UserData::User_List.size();i++)
    {
        if(Register::ui->UserID_lineEdit->text() ==UserData::User_List[i].UserID )
        {
            Register::ui->Warn_label->setText("此帐号已注册!!!");
            Register::ui->Besure_Button->setEnabled(false);
            break;

        }
        else
        {
            Register::ui->Warn_label->setText("");

            Register::ui->Besure_Button->setEnabled(true);
        }

    }
}

void Register::on_Password2_lineEdit_editingFinished()
{

    if(Register::ui->Password2_lineEdit->text() != Register::ui->Password_lineEdit->text())
    {
        Register::ui->Warn2_label->setText("密码不一致");
        Register::ui->Besure_Button->setEnabled(false);
    }
    else{
        Register::ui->Warn2_label->setText("");
        Register::ui->Besure_Button->setEnabled(true);
    }
}
