/********************************************************************************
** Form generated from reading UI file 'testwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIDGET_H
#define UI_TESTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QRoundProgressBar.h"

QT_BEGIN_NAMESPACE

class Ui_TestWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label;
    QRoundProgressBar *RoundBar1;
    QRoundProgressBar *RoundBar2;
    QRoundProgressBar *RoundBar3;
    QLabel *label_3;
    QSlider *Slider;
    QRoundProgressBar *RoundBar4;
    QRoundProgressBar *RoundBar5;
    QRoundProgressBar *RoundBar6;
    QGridLayout *gridLayout;
    QRoundProgressBar *RoundBar7;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;

    void setupUi(QWidget *TestWidget)
    {
        if (TestWidget->objectName().isEmpty())
            TestWidget->setObjectName(QStringLiteral("TestWidget"));
        TestWidget->resize(703, 350);
        horizontalLayout = new QHBoxLayout(TestWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(TestWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 0, 3, 1, 1);

        label = new QLabel(TestWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        RoundBar1 = new QRoundProgressBar(TestWidget);
        RoundBar1->setObjectName(QStringLiteral("RoundBar1"));

        gridLayout_2->addWidget(RoundBar1, 2, 0, 1, 1);

        RoundBar2 = new QRoundProgressBar(TestWidget);
        RoundBar2->setObjectName(QStringLiteral("RoundBar2"));
        QPalette palette;
        QBrush brush(QColor(118, 118, 118, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(170, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush2);
        QBrush brush3(QColor(122, 122, 122, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        QBrush brush4(QColor(244, 244, 244, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        QBrush brush5(QColor(50, 100, 150, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        RoundBar2->setPalette(palette);
        QFont font1;
        font1.setFamily(QStringLiteral("Courier New"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        RoundBar2->setFont(font1);

        gridLayout_2->addWidget(RoundBar2, 2, 1, 1, 1);

        RoundBar3 = new QRoundProgressBar(TestWidget);
        RoundBar3->setObjectName(QStringLiteral("RoundBar3"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush6(QColor(170, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        RoundBar3->setPalette(palette1);

        gridLayout_2->addWidget(RoundBar3, 2, 3, 1, 1);

        label_3 = new QLabel(TestWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 3);

        Slider = new QSlider(TestWidget);
        Slider->setObjectName(QStringLiteral("Slider"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Slider->sizePolicy().hasHeightForWidth());
        Slider->setSizePolicy(sizePolicy1);
        Slider->setMaximum(999);
        Slider->setValue(150);
        Slider->setOrientation(Qt::Horizontal);
        Slider->setTickPosition(QSlider::TicksBothSides);
        Slider->setTickInterval(25);

        gridLayout_3->addWidget(Slider, 1, 0, 1, 3);

        RoundBar4 = new QRoundProgressBar(TestWidget);
        RoundBar4->setObjectName(QStringLiteral("RoundBar4"));
        QPalette palette2;
        QBrush brush7(QColor(170, 170, 255, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush7);
        QBrush brush8(QColor(0, 0, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush8);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        RoundBar4->setPalette(palette2);

        gridLayout_3->addWidget(RoundBar4, 2, 0, 1, 1);

        RoundBar5 = new QRoundProgressBar(TestWidget);
        RoundBar5->setObjectName(QStringLiteral("RoundBar5"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette3.setBrush(QPalette::Active, QPalette::Highlight, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::Highlight, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        RoundBar5->setPalette(palette3);

        gridLayout_3->addWidget(RoundBar5, 2, 1, 1, 1);

        RoundBar6 = new QRoundProgressBar(TestWidget);
        RoundBar6->setObjectName(QStringLiteral("RoundBar6"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette4.setBrush(QPalette::Active, QPalette::Highlight, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::Highlight, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        RoundBar6->setPalette(palette4);

        gridLayout_3->addWidget(RoundBar6, 2, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_3);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        RoundBar7 = new QRoundProgressBar(TestWidget);
        RoundBar7->setObjectName(QStringLiteral("RoundBar7"));
        QPalette palette5;
        QBrush brush9(QColor(255, 255, 255, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush9);
        QBrush brush10(QColor(57, 57, 57, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush10);
        QBrush brush11(QColor(85, 85, 85, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush11);
        QBrush brush12(QColor(71, 71, 71, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Midlight, brush12);
        QBrush brush13(QColor(28, 28, 28, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Dark, brush13);
        QBrush brush14(QColor(38, 38, 38, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Mid, brush14);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush9);
        palette5.setBrush(QPalette::Active, QPalette::BrightText, brush9);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush9);
        QBrush brush15(QColor(0, 0, 0, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush15);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush10);
        palette5.setBrush(QPalette::Active, QPalette::Shadow, brush15);
        QBrush brush16(QColor(255, 170, 0, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Highlight, brush16);
        QBrush brush17(QColor(115, 115, 115, 255));
        brush17.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::AlternateBase, brush17);
        QBrush brush18(QColor(255, 255, 220, 255));
        brush18.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush18);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipText, brush15);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush10);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::Midlight, brush12);
        palette5.setBrush(QPalette::Inactive, QPalette::Dark, brush13);
        palette5.setBrush(QPalette::Inactive, QPalette::Mid, brush14);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::BrightText, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush15);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush10);
        palette5.setBrush(QPalette::Inactive, QPalette::Shadow, brush15);
        palette5.setBrush(QPalette::Inactive, QPalette::Highlight, brush16);
        palette5.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush17);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush18);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush15);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush13);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush10);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::Midlight, brush12);
        palette5.setBrush(QPalette::Disabled, QPalette::Dark, brush13);
        palette5.setBrush(QPalette::Disabled, QPalette::Mid, brush14);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush13);
        palette5.setBrush(QPalette::Disabled, QPalette::BrightText, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush13);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush10);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush10);
        palette5.setBrush(QPalette::Disabled, QPalette::Shadow, brush15);
        palette5.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        palette5.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush17);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush18);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush15);
        RoundBar7->setPalette(palette5);
        verticalLayout = new QVBoxLayout(RoundBar7);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout->addWidget(RoundBar7, 1, 0, 1, 2);

        label_4 = new QLabel(TestWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setWeight(75);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 0, 0, 1, 2);

        gridLayout->setRowStretch(0, 3);

        horizontalLayout->addLayout(gridLayout);


        retranslateUi(TestWidget);

        QMetaObject::connectSlotsByName(TestWidget);
    } // setupUi

    void retranslateUi(QWidget *TestWidget)
    {
        TestWidget->setWindowTitle(QApplication::translate("TestWidget", "TestWidget", 0));
        label_2->setText(QApplication::translate("TestWidget", "Line Style", 0));
        label->setText(QApplication::translate("TestWidget", "Donut Style", 0));
        label_3->setText(QApplication::translate("TestWidget", "Pie Style", 0));
        label_4->setText(QApplication::translate("TestWidget", "Donut Style (dark styled)", 0));
    } // retranslateUi

};

namespace Ui {
    class TestWidget: public Ui_TestWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIDGET_H
