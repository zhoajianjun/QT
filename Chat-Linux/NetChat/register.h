#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <userdata.h>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    QString imagePath;

//    UserData::User newUser;
//    UserData::UserInfo newUserInfo;
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_Besure_Button_clicked();

    void on_Back_Button_clicked();

    void on_UserID_lineEdit_editingFinished();

    void on_Password2_lineEdit_editingFinished();

    
private:
    Ui::Register *ui;

};


#endif // REGISTER_H
