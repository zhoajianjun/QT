/********************************************************************************
** Form generated from reading UI file 'filerecive.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILERECIVE_H
#define UI_FILERECIVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileRecive
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *FriendAvatar_label;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *Status_label;
    QProgressBar *transProgressBar;
    QLabel *OwnAvatar_label;
    QPushButton *Refuse_pushButton;
    QPushButton *pushButton;
    QLabel *Ask_label;

    void setupUi(QWidget *FileRecive)
    {
        if (FileRecive->objectName().isEmpty())
            FileRecive->setObjectName(QStringLiteral("FileRecive"));
        FileRecive->resize(450, 300);
        layoutWidget = new QWidget(FileRecive);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 431, 111));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        FriendAvatar_label = new QLabel(layoutWidget);
        FriendAvatar_label->setObjectName(QStringLiteral("FriendAvatar_label"));
        FriendAvatar_label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/avatar.png")));

        horizontalLayout->addWidget(FriendAvatar_label);

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

        OwnAvatar_label = new QLabel(layoutWidget);
        OwnAvatar_label->setObjectName(QStringLiteral("OwnAvatar_label"));
        OwnAvatar_label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/avatar.png")));

        horizontalLayout->addWidget(OwnAvatar_label);

        Refuse_pushButton = new QPushButton(FileRecive);
        Refuse_pushButton->setObjectName(QStringLiteral("Refuse_pushButton"));
        Refuse_pushButton->setGeometry(QRect(170, 230, 100, 40));
        Refuse_pushButton->setFocusPolicy(Qt::NoFocus);
        Refuse_pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
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
        pushButton = new QPushButton(FileRecive);
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
        Ask_label = new QLabel(FileRecive);
        Ask_label->setObjectName(QStringLiteral("Ask_label"));
        Ask_label->setGeometry(QRect(10, 169, 431, 61));

        retranslateUi(FileRecive);

        QMetaObject::connectSlotsByName(FileRecive);
    } // setupUi

    void retranslateUi(QWidget *FileRecive)
    {
        FileRecive->setWindowTitle(QApplication::translate("FileRecive", "Form", 0));
        FriendAvatar_label->setText(QString());
        Status_label->setText(QString());
        OwnAvatar_label->setText(QString());
        Refuse_pushButton->setText(QApplication::translate("FileRecive", "\345\217\226\346\266\210", 0));
        pushButton->setText(QString());
        Ask_label->setText(QApplication::translate("FileRecive", "<html><head/><body><p align=\"center\"><br/></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class FileRecive: public Ui_FileRecive {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILERECIVE_H
