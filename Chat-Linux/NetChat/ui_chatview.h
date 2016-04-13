/********************************************************************************
** Form generated from reading UI file 'chatview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATVIEW_H
#define UI_CHATVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatView
{
public:
    QListWidget *listWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;

    void setupUi(QWidget *ChatView)
    {
        if (ChatView->objectName().isEmpty())
            ChatView->setObjectName(QStringLiteral("ChatView"));
        ChatView->resize(720, 480);
        listWidget = new QListWidget(ChatView);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 90, 480));
        listWidget->setStyleSheet(QStringLiteral("background-color: rgb(69, 171, 243);"));
        label = new QLabel(ChatView);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 10, 80, 30));
        label->setStyleSheet(QStringLiteral("color: rgb(169, 49, 229);"));
        label_2 = new QLabel(ChatView);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(200, 15, 50, 20));
        label_3 = new QLabel(ChatView);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 40, 200, 20));
        textEdit = new QTextEdit(ChatView);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(100, 380, 450, 90));
        textEdit->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 119);"));
        pushButton = new QPushButton(ChatView);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(600, 420, 100, 50));
        pushButton_2 = new QPushButton(ChatView);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(100, 340, 30, 30));
        pushButton_3 = new QPushButton(ChatView);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(200, 340, 30, 30));
        pushButton_4 = new QPushButton(ChatView);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(250, 340, 30, 30));
        verticalLayoutWidget = new QWidget(ChatView);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(100, 79, 511, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));

        verticalLayout->addWidget(groupBox);


        retranslateUi(ChatView);

        QMetaObject::connectSlotsByName(ChatView);
    } // setupUi

    void retranslateUi(QWidget *ChatView)
    {
        ChatView->setWindowTitle(QApplication::translate("ChatView", "Form", 0));
        label->setText(QApplication::translate("ChatView", "TextLabel", 0));
        label_2->setText(QApplication::translate("ChatView", "TextLabel", 0));
        label_3->setText(QApplication::translate("ChatView", "TextLabel", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        groupBox->setTitle(QApplication::translate("ChatView", "GroupBox", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatView: public Ui_ChatView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATVIEW_H
