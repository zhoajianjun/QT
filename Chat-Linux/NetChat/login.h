#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "userdata.h"
#include <QSystemTrayIcon>
#include <QFile>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    //    UserData userdata;
    void paintEvent(QPaintEvent *);
protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
private slots:

    void on_login_button_clicked();
    void on_pushButton_clicked();
    void on_Min_pushButton_clicked();
    void on_AutoLogin_checkBox_clicked();
    void on_RemeberPwd_checkBox_clicked();
    void Status_Changed();
    void on_userid_comboBox_editTextChanged(const QString &arg1);

private:
    QAction *action[6];
    QString ImagesIcon[6];
    QPoint dragPosition;
    QSystemTrayIcon *systemTrayIcon;
    void Status_init();
    void init();
    Ui::Login *ui;
    QStringList Status;

    QFile userFile;


};

#endif // LOGIN_H
