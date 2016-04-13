/********************************************************************************
** Form generated from reading UI file 'friendslist.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDSLIST_H
#define UI_FRIENDSLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendsList
{
public:
    QTabWidget *FriendList_tabWidget;
    QWidget *Near_tab;
    QTreeView *treeView;
    QWidget *Friends_tab;
    QWidget *Groups_tab;
    QLabel *UserAvatar_label;
    QLabel *UserPS_label;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPushButton *Close_pushButton;
    QLabel *UserName_label;

    void setupUi(QWidget *FriendsList)
    {
        if (FriendsList->objectName().isEmpty())
            FriendsList->setObjectName(QStringLiteral("FriendsList"));
        FriendsList->resize(300, 650);
        FriendList_tabWidget = new QTabWidget(FriendsList);
        FriendList_tabWidget->setObjectName(QStringLiteral("FriendList_tabWidget"));
        FriendList_tabWidget->setGeometry(QRect(9, 160, 280, 421));
        FriendList_tabWidget->setFocusPolicy(Qt::NoFocus);
        FriendList_tabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        FriendList_tabWidget->setStyleSheet(QLatin1String("QTabWidget::pane { /* The tab widget frame */\n"
"    border-top: none;\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    left: 0px; /* move to the right by 5px */\n"
"	\n"
"}\n"
"\n"
"/* Style the tab using the tab sub-control. Note that\n"
"    it reads QTabBar _not_ QTabWidget */\n"
"QTabBar::tab {\n"
"\n"
" 	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #EDEDED, stop: 0.4 #D0D0D0,\n"
"                                stop: 0.5 #C8C8C8, stop: 1.0 #C3C3C3);\n"
"text-align:center;\n"
"	width:93px;\n"
"	height:30px;\n"
"   border: none;\n"
"    border-top-left-radius: 2px;\n"
"    border-top-right-radius: 2px;\n"
"    min-width: 8ex;\n"
"    padding: 0px;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"	 	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #DDDDDD, stop: 0.4 #DDDDDD,\n"
"                                stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"    \n"
"}\n"
"\n"
""
                        "QTabBar::tab:selected {\n"
"	background-color: rgb(255, 255, 255);\n"
"   \n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 0px; /* make non-selected tabs look smaller */\n"
"}\n"
"\n"
"                            "));
        FriendList_tabWidget->setTabPosition(QTabWidget::North);
        FriendList_tabWidget->setTabShape(QTabWidget::Rounded);
        FriendList_tabWidget->setIconSize(QSize(50, 30));
        FriendList_tabWidget->setElideMode(Qt::ElideNone);
        FriendList_tabWidget->setDocumentMode(false);
        FriendList_tabWidget->setTabsClosable(false);
        FriendList_tabWidget->setMovable(false);
        Near_tab = new QWidget();
        Near_tab->setObjectName(QStringLiteral("Near_tab"));
        treeView = new QTreeView(Near_tab);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(0, 0, 280, 391));
        treeView->setStyleSheet(QLatin1String("QTreeView {\n"
"    show-decoration-selected: 1;\n"
"	border:none;\n"
"}\n"
"\n"
"QTreeView::item {\n"
"     border: 1px solid #d9d9d9;\n"
"    border-top-color: transparent;\n"
"    border-bottom-color: transparent;\n"
"}\n"
"\n"
"QTreeView::item:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);\n"
"    border: 1px solid #bfcde4;\n"
"}\n"
"\n"
"QTreeView::item:selected {\n"
"    border: 1px solid #567dbc;\n"
"}\n"
"\n"
"QTreeView::item:selected:active{\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);\n"
"}\n"
"\n"
"QTreeView::item:selected:!active {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);\n"
"}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/recentList_unselect.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/images/recentList_select.svg"), QSize(), QIcon::Normal, QIcon::On);
        FriendList_tabWidget->addTab(Near_tab, icon, QString());
        Friends_tab = new QWidget();
        Friends_tab->setObjectName(QStringLiteral("Friends_tab"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/friendList_unselect.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/images/images/friendList_select.svg"), QSize(), QIcon::Normal, QIcon::On);
        FriendList_tabWidget->addTab(Friends_tab, icon1, QString());
        Groups_tab = new QWidget();
        Groups_tab->setObjectName(QStringLiteral("Groups_tab"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/images/groupList_unselect.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":/images/images/groupList_select.svg"), QSize(), QIcon::Normal, QIcon::On);
        FriendList_tabWidget->addTab(Groups_tab, icon2, QString());
        UserAvatar_label = new QLabel(FriendsList);
        UserAvatar_label->setObjectName(QStringLiteral("UserAvatar_label"));
        UserAvatar_label->setGeometry(QRect(20, 10, 100, 100));
        UserAvatar_label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/avatar.png")));
        UserPS_label = new QLabel(FriendsList);
        UserPS_label->setObjectName(QStringLiteral("UserPS_label"));
        UserPS_label->setGeometry(QRect(20, 120, 271, 31));
        UserPS_label->setFrameShape(QFrame::StyledPanel);
        pushButton = new QPushButton(FriendsList);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 610, 30, 30));
        QIcon icon3;
        icon3.addFile(QStringLiteral("images/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);
        lineEdit = new QLineEdit(FriendsList);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 610, 161, 27));
        Close_pushButton = new QPushButton(FriendsList);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(270, 10, 20, 20));
        Close_pushButton->setFocusPolicy(Qt::NoFocus);
        Close_pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
"			border-image: url(:/images/images/button-quit.svg);\n"
"   			border:none;\n"
"}\n"
"QPushButton:hover{border:none;border-image: url(:/images/images/button-quit.svg);}\n"
"QPushButton:pressed{border:none;border-image: url(:/images/images/button-quit.svg);}"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/images/button-quit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Close_pushButton->setIcon(icon4);
        Close_pushButton->setIconSize(QSize(25, 25));
        UserName_label = new QLabel(FriendsList);
        UserName_label->setObjectName(QStringLiteral("UserName_label"));
        UserName_label->setGeometry(QRect(140, 40, 111, 31));

        retranslateUi(FriendsList);

        FriendList_tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(FriendsList);
    } // setupUi

    void retranslateUi(QWidget *FriendsList)
    {
        FriendsList->setWindowTitle(QApplication::translate("FriendsList", "Form", 0));
        FriendList_tabWidget->setTabText(FriendList_tabWidget->indexOf(Near_tab), QApplication::translate("FriendsList", "\346\234\200\350\277\221", 0));
        FriendList_tabWidget->setTabText(FriendList_tabWidget->indexOf(Friends_tab), QApplication::translate("FriendsList", "\345\245\275\345\217\213", 0));
        FriendList_tabWidget->setTabText(FriendList_tabWidget->indexOf(Groups_tab), QApplication::translate("FriendsList", "\347\276\244\347\273\204", 0));
        UserAvatar_label->setText(QString());
        UserPS_label->setText(QString());
        pushButton->setText(QString());
        Close_pushButton->setText(QString());
        UserName_label->setText(QApplication::translate("FriendsList", "<html><head/><body><p align=\"center\"><span style=\" color:#ffffff;\"><br/></span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class FriendsList: public Ui_FriendsList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDSLIST_H
