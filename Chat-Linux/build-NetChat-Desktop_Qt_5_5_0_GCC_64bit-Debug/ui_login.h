/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <qmenubutton.h>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *warn_label;
    QLabel *avatar_label;
    QPushButton *login_button;
    QLabel *register_label;
    QPushButton *pushButton;
    QPushButton *Min_pushButton;
    QMenuButton *Status_pushButton;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    QComboBox *userid_comboBox;
    QLabel *label_3;
    QLineEdit *password_text;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QCheckBox *RemeberPwd_checkBox;
    QCheckBox *AutoLogin_checkBox;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *title_label;
    QLabel *logo_label;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(430, 280);
        Login->setStyleSheet(QStringLiteral(""));
        warn_label = new QLabel(Login);
        warn_label->setObjectName(QStringLiteral("warn_label"));
        warn_label->setGeometry(QRect(340, 150, 91, 21));
        avatar_label = new QLabel(Login);
        avatar_label->setObjectName(QStringLiteral("avatar_label"));
        avatar_label->setGeometry(QRect(0, 90, 100, 100));
        avatar_label->setStyleSheet(QLatin1String("border-color: rgb(255, 120, 31);\n"
"border-image: url(:/images/images/avatar-border.svg);"));
        avatar_label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/avatar.png")));
        login_button = new QPushButton(Login);
        login_button->setObjectName(QStringLiteral("login_button"));
        login_button->setGeometry(QRect(150, 230, 200, 40));
        login_button->setFocusPolicy(Qt::NoFocus);
        login_button->setStyleSheet(QLatin1String("QPushButton{\n"
"    color: white;\n"
"    font: bold 13pt;\n"
"    border:none;\n"
"    min-height: 24px;\n"
"    min-width: 60px;\n"
"	border-image: url(:/images/images/button-login.svg);\n"
"	\n"
"}\n"
"QPushButton:hover{\n"
"    color: lightgray;\n"
"    border:none;\n"
"	border-image: url(:/images/images/button-login-hover.svg);\n"
"}\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border:none;\n"
"	border-image: url(:/images/images/button-login-press.svg);\n"
"    padding-top: -15px;\n"
"    padding-bottom: -17px;\n"
"} "));
        login_button->setIconSize(QSize(200, 40));
        register_label = new QLabel(Login);
        register_label->setObjectName(QStringLiteral("register_label"));
        register_label->setGeometry(QRect(340, 110, 81, 21));
        pushButton = new QPushButton(Login);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 10, 20, 20));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
"			border-image: url(./images/button-quit.svg);\n"
"   			border:none;\n"
"}\n"
"QPushButton:hover{border:none;border-image: url(./images/button-quit.svg);}\n"
"QPushButton:pressed{border:none;border-image: url(./images/button-quit.svg);}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/button-quit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(25, 25));
        Min_pushButton = new QPushButton(Login);
        Min_pushButton->setObjectName(QStringLiteral("Min_pushButton"));
        Min_pushButton->setGeometry(QRect(370, 10, 20, 20));
        Min_pushButton->setFocusPolicy(Qt::NoFocus);
        Min_pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
"	border-image: url(./images/button-quit.svg);\n"
"   border:none;\n"
"}\n"
"QPushButton:hover{border:none;border-image: url(./images/button-quit.svg);}\n"
"QPushButton:pressed{border:none;border-image: url(./images/button-quit.svg);}\n"
"   "));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/button-minimize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Min_pushButton->setIcon(icon1);
        Min_pushButton->setIconSize(QSize(25, 25));
        Status_pushButton = new QMenuButton(Login);
        Status_pushButton->setObjectName(QStringLiteral("Status_pushButton"));
        Status_pushButton->setGeometry(QRect(75, 165, 25, 25));
        Status_pushButton->setFocusPolicy(Qt::NoFocus);
        Status_pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
"    border:none;\n"
"}\n"
"QPushButton:hover{\n"
"    border:none;\n"
"}\n"
"QPushButton:pressed {\n"
"\n"
"    border:none;\n"
"} "));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/images/status-online-1.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Status_pushButton->setIcon(icon2);
        Status_pushButton->setIconSize(QSize(25, 25));
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 110, 211, 61));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        userid_comboBox = new QComboBox(layoutWidget);
        userid_comboBox->setObjectName(QStringLiteral("userid_comboBox"));
        userid_comboBox->setStyleSheet(QLatin1String("QComboBox {\n"
"    \n"
"    border: 1px solid gray;\n"
"    border-radius: 3px;\n"
"    padding: 1px 18px 1px 3px;\n"
"    min-width: 6em;\n"
"}\n"
"\n"
"QComboBox:editable {\n"
"    background: white;\n"
"}\n"
"\n"
"QComboBox:!editable, QComboBox::drop-down:editable {\n"
"		border:none;\n"
"     background: white;\n"
"}\n"
"\n"
"/* QComboBox gets the \"on\" state when the popup is open */\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n"
"    background: white;\n"
"	border:none;\n"
"}\n"
"\n"
"QComboBox:on { /* shift the text when the popup opens */\n"
"    padding-top: 3px;\n"
"    padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 15px;\n"
"\n"
"    border-left-width: 1px;\n"
"    border-left-color: darkgray;\n"
"    border-left-style: solid; /* just a single line */\n"
"    border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"    border-bottom-right-radius: 3px;\n"
"}\n"
"\n"
"Q"
                        "ComboBox::down-arrow {\n"
"\n"
"	image: url(:/images/images/unfold_icon.png);\n"
"}\n"
"\n"
"QComboBox::down-arrow:on { /* shift the arrow when popup is open */\n"
"    top: 1px;\n"
"    left: 10px;\n"
"}"));
        userid_comboBox->setEditable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, userid_comboBox);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        password_text = new QLineEdit(layoutWidget);
        password_text->setObjectName(QStringLiteral("password_text"));
        password_text->setStyleSheet(QStringLiteral(""));
        password_text->setMaxLength(15);
        password_text->setFrame(true);
        password_text->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, password_text);

        layoutWidget1 = new QWidget(Login);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(150, 190, 188, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        RemeberPwd_checkBox = new QCheckBox(layoutWidget1);
        RemeberPwd_checkBox->setObjectName(QStringLiteral("RemeberPwd_checkBox"));
        RemeberPwd_checkBox->setStyleSheet(QLatin1String("QCheckBox {\n"
"    spacing: 10px;\n"
"	color: rgb(255, 120, 31);\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"   \n"
"	image: url(:/images/images/checkBox-unselect.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked:hover {\n"
" \n"
"	image: url(:/images/images/checkBox-unselect.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked:pressed {\n"
"    \n"
"	image: url(:/images/images/checkBox-unselect.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"   \n"
"	image: url(:/images/images/checkBox-select.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked:hover {\n"
"    \n"
"	image: url(:/images/images/checkBox-hover.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked:pressed {\n"
"    \n"
"	image: url(:/images/images/checkBox-hover.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate:hover {\n"
"    \n"
"	image: url(:/images/images/checkBox-hover.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate:pressed {\n"
"  image"
                        ": url(:/images/images/checkBox-hover.svg);\n"
"}"));

        horizontalLayout->addWidget(RemeberPwd_checkBox);

        AutoLogin_checkBox = new QCheckBox(layoutWidget1);
        AutoLogin_checkBox->setObjectName(QStringLiteral("AutoLogin_checkBox"));
        AutoLogin_checkBox->setStyleSheet(QLatin1String("QCheckBox {\n"
"    spacing: 10px;\n"
"	color: rgb(255, 120, 31);\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"   \n"
"	image: url(:/images/images/checkBox-unselect.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked:hover {\n"
" \n"
"	image: url(:/images/images/checkBox-unselect.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked:pressed {\n"
"    \n"
"	image: url(:/images/images/checkBox-unselect.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"   \n"
"	image: url(:/images/images/checkBox-select.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked:hover {\n"
"    \n"
"	image: url(:/images/images/checkBox-hover.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked:pressed {\n"
"    \n"
"	image: url(:/images/images/checkBox-hover.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate:hover {\n"
"    \n"
"	image: url(:/images/images/checkBox-hover.svg);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate:pressed {\n"
"  image"
                        ": url(:/images/images/checkBox-hover.svg);\n"
"}"));

        horizontalLayout->addWidget(AutoLogin_checkBox);

        layoutWidget2 = new QWidget(Login);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(90, 40, 297, 52));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        title_label = new QLabel(layoutWidget2);
        title_label->setObjectName(QStringLiteral("title_label"));
        title_label->setPixmap(QPixmap(QString::fromUtf8("images/title.png")));

        horizontalLayout_2->addWidget(title_label);

        logo_label = new QLabel(layoutWidget2);
        logo_label->setObjectName(QStringLiteral("logo_label"));
        logo_label->setPixmap(QPixmap(QString::fromUtf8("images/logo.png")));

        horizontalLayout_2->addWidget(logo_label);

        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        warn_label->raise();
        avatar_label->raise();
        login_button->raise();
        register_label->raise();
        pushButton->raise();
        Min_pushButton->raise();
        Status_pushButton->raise();
#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(userid_comboBox);
        label_3->setBuddy(password_text);
#endif // QT_NO_SHORTCUT

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", 0));
        warn_label->setText(QString());
#ifndef QT_NO_TOOLTIP
        avatar_label->setToolTip(QApplication::translate("Login", "<html><head/><body><p align=\"center\"><span style=\" color:#ff781f;\">\345\244\264\345\203\217</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        avatar_label->setText(QString());
#ifndef QT_NO_TOOLTIP
        login_button->setToolTip(QApplication::translate("Login", "<html><head/><body><p align=\"center\"><span style=\" color:#ff781f;\">\347\231\273\345\275\225</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        login_button->setText(QApplication::translate("Login", "\347\231\273\345\275\225", 0));
#ifndef QT_NO_TOOLTIP
        register_label->setToolTip(QApplication::translate("Login", "<html><head/><body><p align=\"center\"><span style=\" color:#ff781f;\">\347\202\271\345\207\273\346\263\250\345\206\214</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        register_label->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" color:#FF781F;\">\346\263\250\345\206\214\345\270\220\345\217\267&gt;&gt;</span></p></body></html>", 0));
        pushButton->setText(QString());
        Min_pushButton->setText(QString());
        Status_pushButton->setText(QString());
        label_2->setText(QApplication::translate("Login", "<html><head/><body><p align=\"right\"><span style=\" font-size:14pt; color:#ff781f;\">\345\270\220\345\217\267\357\274\232</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("Login", "<html><head/><body><p align=\"right\"><span style=\" font-size:14pt; color:#FF781F;\">\345\257\206\347\240\201\357\274\232</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        password_text->setToolTip(QApplication::translate("Login", "<html><head/><body><p align=\"center\"><span style=\" color:#ff781f;\">\345\257\206\347\240\201</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        RemeberPwd_checkBox->setText(QApplication::translate("Login", "\350\256\260\344\275\217\345\257\206\347\240\201", 0));
        AutoLogin_checkBox->setText(QApplication::translate("Login", "\350\207\252\345\212\250\347\231\273\345\275\225", 0));
        title_label->setText(QString());
        logo_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
