/********************************************************************************
** Form generated from reading UI file 'link.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINK_H
#define UI_LINK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Link
{
public:

    void setupUi(QWidget *Link)
    {
        if (Link->objectName().isEmpty())
            Link->setObjectName(QStringLiteral("Link"));
        Link->resize(400, 300);

        retranslateUi(Link);

        QMetaObject::connectSlotsByName(Link);
    } // setupUi

    void retranslateUi(QWidget *Link)
    {
        Link->setWindowTitle(QApplication::translate("Link", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Link: public Ui_Link {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINK_H
