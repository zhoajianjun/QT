/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QLabel *warn_label;
    QLabel *title_label;
    QLineEdit *userid_text;
    QLineEdit *password_text;
    QLabel *logo_label;
    QLabel *label_2;
    QLabel *avatar_label;
    QLabel *label_3;
    QLabel *register_label;
    QPushButton *pushButton;
    QPushButton *login_button;

    void setupUi(QWidget *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName(QStringLiteral("LoginForm"));
        LoginForm->resize(430, 280);
        warn_label = new QLabel(LoginForm);
        warn_label->setObjectName(QStringLiteral("warn_label"));
        warn_label->setGeometry(QRect(250, 150, 181, 21));
        title_label = new QLabel(LoginForm);
        title_label->setObjectName(QStringLiteral("title_label"));
        title_label->setGeometry(QRect(90, 10, 241, 41));
        title_label->setPixmap(QPixmap(QString::fromUtf8("images/title.png")));
        userid_text = new QLineEdit(LoginForm);
        userid_text->setObjectName(QStringLiteral("userid_text"));
        userid_text->setGeometry(QRect(190, 80, 141, 27));
        userid_text->setMaxLength(15);
        userid_text->setReadOnly(false);
        password_text = new QLineEdit(LoginForm);
        password_text->setObjectName(QStringLiteral("password_text"));
        password_text->setGeometry(QRect(190, 120, 141, 27));
        password_text->setMaxLength(15);
        password_text->setFrame(true);
        password_text->setEchoMode(QLineEdit::Password);
        logo_label = new QLabel(LoginForm);
        logo_label->setObjectName(QStringLiteral("logo_label"));
        logo_label->setGeometry(QRect(340, 10, 50, 50));
        logo_label->setPixmap(QPixmap(QString::fromUtf8("images/logo.png")));
        label_2 = new QLabel(LoginForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 80, 61, 31));
        avatar_label = new QLabel(LoginForm);
        avatar_label->setObjectName(QStringLiteral("avatar_label"));
        avatar_label->setGeometry(QRect(0, 90, 100, 100));
        avatar_label->setStyleSheet(QStringLiteral(""));
        avatar_label->setPixmap(QPixmap(QString::fromUtf8("images/avatar.png")));
        label_3 = new QLabel(LoginForm);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 120, 61, 31));
        register_label = new QLabel(LoginForm);
        register_label->setObjectName(QStringLiteral("register_label"));
        register_label->setGeometry(QRect(340, 90, 81, 21));
        pushButton = new QPushButton(LoginForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 10, 20, 20));
        QIcon icon;
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Disabled, QIcon::Off);
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Disabled, QIcon::On);
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Active, QIcon::On);
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Selected, QIcon::Off);
        icon.addFile(QStringLiteral("images/button-quit.svg"), QSize(), QIcon::Selected, QIcon::On);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(25, 25));
        login_button = new QPushButton(LoginForm);
        login_button->setObjectName(QStringLiteral("login_button"));
        login_button->setGeometry(QRect(140, 230, 201, 40));

        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QWidget *LoginForm)
    {
        LoginForm->setWindowTitle(QApplication::translate("LoginForm", "Form", 0));
        warn_label->setText(QString());
        title_label->setText(QString());
        userid_text->setText(QString());
        logo_label->setText(QString());
        label_2->setText(QApplication::translate("LoginForm", "<html><head/><body><p align=\"right\"><span style=\" font-size:14pt; color:#FF781F;\">\345\270\220\345\217\267\357\274\232</span></p></body></html>", 0));
        avatar_label->setText(QString());
        label_3->setText(QApplication::translate("LoginForm", "<html><head/><body><p align=\"right\"><span style=\" font-size:14pt; color:#FF781F;\">\345\257\206\347\240\201\357\274\232</span></p></body></html>", 0));
        register_label->setText(QApplication::translate("LoginForm", "<html><head/><body><p><span style=\" color:#FF781F;\">\346\263\250\345\206\214\345\270\220\345\217\267&gt;&gt;</span></p></body></html>", 0));
        pushButton->setText(QString());
        login_button->setText(QApplication::translate("LoginForm", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
