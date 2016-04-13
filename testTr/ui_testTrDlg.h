/********************************************************************************
** Form generated from reading ui file 'testTrDlg.ui'
**
** Created: Tue Jan 20 14:08:40 2009
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TESTTRDLG_H
#define UI_TESTTRDLG_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *engBtn;
    QPushButton *chsBtn;
    QPushButton *loveBtn;
    QPushButton *testBtn;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    Dialog->resize(268, 166);
    engBtn = new QPushButton(Dialog);
    engBtn->setObjectName(QString::fromUtf8("engBtn"));
    engBtn->setGeometry(QRect(14, 30, 121, 23));
    chsBtn = new QPushButton(Dialog);
    chsBtn->setObjectName(QString::fromUtf8("chsBtn"));
    chsBtn->setGeometry(QRect(160, 30, 91, 23));
    loveBtn = new QPushButton(Dialog);
    loveBtn->setObjectName(QString::fromUtf8("loveBtn"));
    loveBtn->setGeometry(QRect(20, 100, 121, 23));
    testBtn = new QPushButton(Dialog);
    testBtn->setObjectName(QString::fromUtf8("testBtn"));
    testBtn->setGeometry(QRect(160, 100, 91, 23));

    retranslateUi(Dialog);

    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
    engBtn->setText(QApplication::translate("Dialog", "English", 0));
    chsBtn->setText(QApplication::translate("Dialog", "Chinese", 0));
    loveBtn->setText(QApplication::translate("Dialog", "I Love My Family", 0));
    testBtn->setText(QApplication::translate("Dialog", "test tr", 0));
    Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTTRDLG_H
