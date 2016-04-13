/********************************************************************************
** Form generated from reading UI file 'logining.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINING_H
#define UI_LOGINING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logining
{
public:
    QPushButton *Min_pushButton;
    QPushButton *Close_pushButton;
    QLabel *avatar_label;
    QPushButton *login_button;
    QProgressBar *progressBar;
    QLabel *CurrentStatus_label;

    void setupUi(QWidget *Logining)
    {
        if (Logining->objectName().isEmpty())
            Logining->setObjectName(QStringLiteral("Logining"));
        Logining->resize(430, 280);
        Min_pushButton = new QPushButton(Logining);
        Min_pushButton->setObjectName(QStringLiteral("Min_pushButton"));
        Min_pushButton->setGeometry(QRect(370, 0, 20, 20));
        Min_pushButton->setFocusPolicy(Qt::NoFocus);
        Min_pushButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/images/images/button-quit.svg); border:none;}\n"
"\n"
"                                      QPushButton:hover{border-image: url(:/images/images/button-quit.svg);}\n"
"                                      QPushButton:pressed{border-image: url(:/images/images/button-quit.svg);}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/button-minimize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Min_pushButton->setIcon(icon);
        Min_pushButton->setIconSize(QSize(25, 25));
        Close_pushButton = new QPushButton(Logining);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(400, 0, 20, 20));
        Close_pushButton->setFocusPolicy(Qt::NoFocus);
        Close_pushButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/images/images/button-quit.svg);border:none;}\n"
"                                      QPushButton:hover{border-image: url(:/images/images/button-quit.svg);}\n"
"                                      QPushButton:pressed{border-image: url(:/images/images/button-quit.svg);}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/button-quit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Close_pushButton->setIcon(icon1);
        Close_pushButton->setIconSize(QSize(25, 25));
        avatar_label = new QLabel(Logining);
        avatar_label->setObjectName(QStringLiteral("avatar_label"));
        avatar_label->setGeometry(QRect(190, 40, 100, 100));
        avatar_label->setStyleSheet(QStringLiteral(""));
        avatar_label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/avatar.png")));
        login_button = new QPushButton(Logining);
        login_button->setObjectName(QStringLiteral("login_button"));
        login_button->setGeometry(QRect(150, 220, 200, 40));
        login_button->setFocusPolicy(Qt::NoFocus);
        login_button->setStyleSheet(QLatin1String("QPushButton{\n"
"    color: white;\n"
"    font: bold 13pt;\n"
"    border:none;\n"
"    min-height: 24px;\n"
"    min-width: 60px;\n"
"	border-image: url(:/images/images/button-login.svg);\n"
"}\n"
"QPushButton:hover{\n"
"    color: lightgray;\n"
"    \n"
"	border-image: url(:/images/images/button-login-hover.svg);\n"
"}\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    \n"
"	border-image: url(:/images/images/button-login-press.svg);\n"
"    padding-top: -15px;\n"
"    padding-bottom: -17px;\n"
"} "));
        login_button->setIconSize(QSize(200, 40));
        progressBar = new QProgressBar(Logining);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(50, 170, 380, 5));
        progressBar->setContextMenuPolicy(Qt::DefaultContextMenu);
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setAutoFillBackground(false);
        progressBar->setStyleSheet(QLatin1String("QProgressBar {\n"
"	background-color: rgb(52, 187, 231);\n"
"    border: -1px solid;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"   \n"
"	background-color: rgb(255, 120, 31);\n"
"}"));
        progressBar->setValue(24);
        CurrentStatus_label = new QLabel(Logining);
        CurrentStatus_label->setObjectName(QStringLiteral("CurrentStatus_label"));
        CurrentStatus_label->setGeometry(QRect(160, 180, 181, 31));

        retranslateUi(Logining);

        QMetaObject::connectSlotsByName(Logining);
    } // setupUi

    void retranslateUi(QWidget *Logining)
    {
        Logining->setWindowTitle(QApplication::translate("Logining", "Form", 0));
        Min_pushButton->setText(QString());
        Close_pushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        avatar_label->setToolTip(QApplication::translate("Logining", "<html><head/><body><p align=\"center\"><span style=\" color:#ff781f;\">\345\244\264\345\203\217</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        avatar_label->setText(QString());
#ifndef QT_NO_TOOLTIP
        login_button->setToolTip(QApplication::translate("Logining", "<html><head/><body><p align=\"center\"><span style=\" color:#ff781f;\">\347\231\273\345\275\225</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        login_button->setText(QApplication::translate("Logining", "\345\217\226\346\266\210", 0));
#ifndef QT_NO_TOOLTIP
        progressBar->setToolTip(QApplication::translate("Logining", "\346\255\243\345\234\250\345\212\240\350\275\275", 0));
#endif // QT_NO_TOOLTIP
        CurrentStatus_label->setText(QApplication::translate("Logining", "<html><head/><body><p align=\"center\"><span style=\" color:#ff781f;\">\346\255\243\345\234\250\351\223\276\346\216\245\346\234\215\345\212\241\345\231\250.......</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Logining: public Ui_Logining {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINING_H
