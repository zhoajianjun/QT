/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLabel *label;
    QPushButton *Besure_Button;
    QPushButton *Back_Button;
    QGroupBox *PersonInfo_GroupBox;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *UserName_lineEdit;
    QTextEdit *UserPS_textEdit;
    QLabel *UserAvatar_label;
    QComboBox *UserSex_comboBox;
    QLineEdit *UserAge_lineEdit;
    QLineEdit *UserAddress_lineEdit;
    QGroupBox *AccountInfo_GroupBox;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *UserID_lineEdit;
    QLineEdit *Password_lineEdit;
    QLineEdit *Password2_lineEdit;
    QLabel *Warn_label;
    QLabel *Warn2_label;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QStringLiteral("Register"));
        Register->resize(401, 591);
        label = new QLabel(Register);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 20, 261, 61));
        Besure_Button = new QPushButton(Register);
        Besure_Button->setObjectName(QStringLiteral("Besure_Button"));
        Besure_Button->setGeometry(QRect(40, 530, 99, 41));
        Besure_Button->setAutoFillBackground(false);
        Besure_Button->setCheckable(false);
        Besure_Button->setChecked(false);
        Back_Button = new QPushButton(Register);
        Back_Button->setObjectName(QStringLiteral("Back_Button"));
        Back_Button->setGeometry(QRect(240, 530, 99, 41));
        PersonInfo_GroupBox = new QGroupBox(Register);
        PersonInfo_GroupBox->setObjectName(QStringLiteral("PersonInfo_GroupBox"));
        PersonInfo_GroupBox->setGeometry(QRect(19, 269, 361, 241));
        PersonInfo_GroupBox->setCursor(QCursor(Qt::ArrowCursor));
        PersonInfo_GroupBox->setFocusPolicy(Qt::NoFocus);
        PersonInfo_GroupBox->setContextMenuPolicy(Qt::DefaultContextMenu);
        PersonInfo_GroupBox->setLayoutDirection(Qt::LeftToRight);
        PersonInfo_GroupBox->setStyleSheet(QLatin1String("\n"
"background-color: rgb(167, 208, 215);\n"
""));
        PersonInfo_GroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        PersonInfo_GroupBox->setFlat(false);
        label_5 = new QLabel(PersonInfo_GroupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 60, 61, 31));
        label_6 = new QLabel(PersonInfo_GroupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 90, 61, 31));
        label_7 = new QLabel(PersonInfo_GroupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 120, 61, 31));
        label_8 = new QLabel(PersonInfo_GroupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(0, 150, 91, 31));
        label_9 = new QLabel(PersonInfo_GroupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 30, 61, 31));
        UserName_lineEdit = new QLineEdit(PersonInfo_GroupBox);
        UserName_lineEdit->setObjectName(QStringLiteral("UserName_lineEdit"));
        UserName_lineEdit->setGeometry(QRect(80, 30, 91, 27));
        UserPS_textEdit = new QTextEdit(PersonInfo_GroupBox);
        UserPS_textEdit->setObjectName(QStringLiteral("UserPS_textEdit"));
        UserPS_textEdit->setGeometry(QRect(23, 187, 321, 51));
        UserAvatar_label = new QLabel(PersonInfo_GroupBox);
        UserAvatar_label->setObjectName(QStringLiteral("UserAvatar_label"));
        UserAvatar_label->setGeometry(QRect(230, 20, 80, 110));
        UserAvatar_label->setPixmap(QPixmap(QString::fromUtf8("images/wenhao.png")));
        UserSex_comboBox = new QComboBox(PersonInfo_GroupBox);
        UserSex_comboBox->setObjectName(QStringLiteral("UserSex_comboBox"));
        UserSex_comboBox->setGeometry(QRect(90, 60, 81, 27));
        UserSex_comboBox->setLayoutDirection(Qt::LeftToRight);
        UserSex_comboBox->setAutoFillBackground(false);
        UserSex_comboBox->setStyleSheet(QLatin1String("QComboBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 3px;\n"
"    padding: 1px 18px 1px 3px;\n"
"    \n"
"}"));
        UserSex_comboBox->setEditable(false);
        UserSex_comboBox->setMinimumContentsLength(0);
        UserAge_lineEdit = new QLineEdit(PersonInfo_GroupBox);
        UserAge_lineEdit->setObjectName(QStringLiteral("UserAge_lineEdit"));
        UserAge_lineEdit->setGeometry(QRect(80, 90, 91, 27));
        UserAddress_lineEdit = new QLineEdit(PersonInfo_GroupBox);
        UserAddress_lineEdit->setObjectName(QStringLiteral("UserAddress_lineEdit"));
        UserAddress_lineEdit->setGeometry(QRect(80, 120, 91, 27));
        UserSex_comboBox->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        label_8->raise();
        label_9->raise();
        UserName_lineEdit->raise();
        UserPS_textEdit->raise();
        UserAvatar_label->raise();
        UserAge_lineEdit->raise();
        UserAddress_lineEdit->raise();
        AccountInfo_GroupBox = new QGroupBox(Register);
        AccountInfo_GroupBox->setObjectName(QStringLiteral("AccountInfo_GroupBox"));
        AccountInfo_GroupBox->setGeometry(QRect(20, 110, 361, 141));
        AccountInfo_GroupBox->setLayoutDirection(Qt::LeftToRight);
        AccountInfo_GroupBox->setAutoFillBackground(false);
        AccountInfo_GroupBox->setStyleSheet(QLatin1String("\n"
"background-color: rgb(167, 208, 215);\n"
""));
        label_2 = new QLabel(AccountInfo_GroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 40, 61, 31));
        label_4 = new QLabel(AccountInfo_GroupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 70, 61, 31));
        label_3 = new QLabel(AccountInfo_GroupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 100, 61, 31));
        UserID_lineEdit = new QLineEdit(AccountInfo_GroupBox);
        UserID_lineEdit->setObjectName(QStringLiteral("UserID_lineEdit"));
        UserID_lineEdit->setGeometry(QRect(110, 40, 141, 27));
        Password_lineEdit = new QLineEdit(AccountInfo_GroupBox);
        Password_lineEdit->setObjectName(QStringLiteral("Password_lineEdit"));
        Password_lineEdit->setGeometry(QRect(110, 70, 141, 27));
        Password_lineEdit->setEchoMode(QLineEdit::Password);
        Password2_lineEdit = new QLineEdit(AccountInfo_GroupBox);
        Password2_lineEdit->setObjectName(QStringLiteral("Password2_lineEdit"));
        Password2_lineEdit->setGeometry(QRect(110, 100, 141, 27));
        Password2_lineEdit->setFrame(true);
        Password2_lineEdit->setEchoMode(QLineEdit::Password);
        Password2_lineEdit->setClearButtonEnabled(false);
        Warn_label = new QLabel(AccountInfo_GroupBox);
        Warn_label->setObjectName(QStringLiteral("Warn_label"));
        Warn_label->setGeometry(QRect(260, 40, 91, 21));
        Warn2_label = new QLabel(AccountInfo_GroupBox);
        Warn2_label->setObjectName(QStringLiteral("Warn2_label"));
        Warn2_label->setGeometry(QRect(260, 110, 91, 21));

        retranslateUi(Register);

        UserSex_comboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QApplication::translate("Register", "Form", 0));
        label->setText(QApplication::translate("Register", "<html><head/><body><p align=\"center\"><span style=\" font-size:28pt; color:#19b4ee;\">Welcome</span></p></body></html>", 0));
        Besure_Button->setText(QApplication::translate("Register", "\347\241\256\345\256\232", 0));
        Back_Button->setText(QApplication::translate("Register", "\350\277\224\345\233\236", 0));
        PersonInfo_GroupBox->setTitle(QApplication::translate("Register", "\344\270\252\344\272\272\344\277\241\346\201\257", 0));
        label_5->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\346\200\247\345\210\253\357\274\232</span></p></body></html>", 0));
        label_6->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\345\271\264\351\276\204\357\274\232</span></p></body></html>", 0));
        label_7->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\345\234\260\345\235\200\357\274\232</span></p></body></html>", 0));
        label_8->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\344\270\252\346\200\247\347\255\276\345\220\215\357\274\232</span></p></body></html>", 0));
        label_9->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\346\230\265\347\247\260\357\274\232</span></p></body></html>", 0));
        UserAvatar_label->setText(QString());
        UserSex_comboBox->setCurrentText(QString());
        AccountInfo_GroupBox->setTitle(QApplication::translate("Register", "\345\270\220\345\217\267\344\277\241\346\201\257", 0));
        label_2->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\345\270\220\345\217\267\357\274\232</span></p></body></html>", 0));
        label_4->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\345\257\206\347\240\201\357\274\232</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("Register", "<html><head/><body><p align=\"right\"><span style=\" color:#2341c6;\">\347\241\256\350\256\244\357\274\232</span></p></body></html>", 0));
        Warn_label->setText(QString());
        Warn2_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
