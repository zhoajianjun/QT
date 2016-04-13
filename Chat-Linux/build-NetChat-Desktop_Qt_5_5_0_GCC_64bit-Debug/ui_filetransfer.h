/********************************************************************************
** Form generated from reading UI file 'filetransfer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILETRANSFER_H
#define UI_FILETRANSFER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileTransfer
{
public:
    QPushButton *Open_pushButton;
    QPushButton *Send_pushButton;
    QLineEdit *FileName_lineEdit;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *OwnAvatar_label;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *Status_label;
    QProgressBar *transProgressBar;
    QLabel *FriendAvatar_label;

    void setupUi(QWidget *FileTransfer)
    {
        if (FileTransfer->objectName().isEmpty())
            FileTransfer->setObjectName(QStringLiteral("FileTransfer"));
        FileTransfer->resize(450, 300);
        Open_pushButton = new QPushButton(FileTransfer);
        Open_pushButton->setObjectName(QStringLiteral("Open_pushButton"));
        Open_pushButton->setGeometry(QRect(10, 200, 100, 40));
        Open_pushButton->setFocusPolicy(Qt::NoFocus);
        Open_pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
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
        Send_pushButton = new QPushButton(FileTransfer);
        Send_pushButton->setObjectName(QStringLiteral("Send_pushButton"));
        Send_pushButton->setGeometry(QRect(340, 200, 100, 40));
        Send_pushButton->setFocusPolicy(Qt::NoFocus);
        Send_pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
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
        FileName_lineEdit = new QLineEdit(FileTransfer);
        FileName_lineEdit->setObjectName(QStringLiteral("FileName_lineEdit"));
        FileName_lineEdit->setGeometry(QRect(120, 210, 211, 27));
        pushButton = new QPushButton(FileTransfer);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(420, 10, 20, 20));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
"			border-image: url(:/images/images/button-quit.svg);\n"
"   			border:none;\n"
"}\n"
"QPushButton:hover{border:none;border-image: url(:/images/images/button-quit.svg);}\n"
"QPushButton:pressed{border:none;border-image: url(:/images/images/button-quit.svg);}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/button-quit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(25, 25));
        layoutWidget = new QWidget(FileTransfer);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 431, 111));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        OwnAvatar_label = new QLabel(layoutWidget);
        OwnAvatar_label->setObjectName(QStringLiteral("OwnAvatar_label"));
        OwnAvatar_label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/avatar.png")));

        horizontalLayout->addWidget(OwnAvatar_label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalSpacer = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        Status_label = new QLabel(layoutWidget);
        Status_label->setObjectName(QStringLiteral("Status_label"));

        verticalLayout->addWidget(Status_label);

        transProgressBar = new QProgressBar(layoutWidget);
        transProgressBar->setObjectName(QStringLiteral("transProgressBar"));
        transProgressBar->setStyleSheet(QLatin1String("QProgressBar {\n"
"    border: 5px;\n"
"	border-color: rgb(74, 181, 238);\n"
"    text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #05B8CC;\n"
"    width: 10px;\n"
"	margin: 0.5px;\n"
"}"));
        transProgressBar->setValue(24);

        verticalLayout->addWidget(transProgressBar);


        horizontalLayout->addLayout(verticalLayout);

        FriendAvatar_label = new QLabel(layoutWidget);
        FriendAvatar_label->setObjectName(QStringLiteral("FriendAvatar_label"));
        FriendAvatar_label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/avatar.png")));

        horizontalLayout->addWidget(FriendAvatar_label);

        layoutWidget->raise();
        Open_pushButton->raise();
        Send_pushButton->raise();
        FileName_lineEdit->raise();
        pushButton->raise();

        retranslateUi(FileTransfer);
        QObject::connect(pushButton, SIGNAL(clicked()), FileTransfer, SLOT(close()));

        QMetaObject::connectSlotsByName(FileTransfer);
    } // setupUi

    void retranslateUi(QWidget *FileTransfer)
    {
        FileTransfer->setWindowTitle(QApplication::translate("FileTransfer", "Form", 0));
        Open_pushButton->setText(QApplication::translate("FileTransfer", "\346\211\223\345\274\200......", 0));
        Send_pushButton->setText(QApplication::translate("FileTransfer", "\345\217\221\351\200\201", 0));
        pushButton->setText(QString());
        OwnAvatar_label->setText(QString());
        Status_label->setText(QString());
        FriendAvatar_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FileTransfer: public Ui_FileTransfer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILETRANSFER_H
