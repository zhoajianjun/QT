#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include <QSystemTrayIcon>

class DeviceSearchAPI;

namespace Ui
{
    class frmMain;
}

class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::frmMain *ui;
    bool max;                   //是否处于最大化状态
    QRect location;             //鼠标移动窗体后的坐标位置
    QSystemTrayIcon *trayIcon;  //托盘图标

    int deviceCount;
    DeviceSearchAPI *deviceSearch;

private slots:
    void InitStyle();           //初始化无边框窗体
    void ChangeStyle();         //改变样式
    void InitForm();            //初始化窗体数据

private slots:
    void ReceiveDevice(QString ip, QString mask, QString gateway, QString mac, QString defenceID);

private slots:
    void on_btnMenu_Max_clicked();    
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);

    void on_btnSelect_clicked();    
    void on_btnSearch_clicked();
    void on_btnUpdate_clicked();
};

#endif // FRMMAIN_H
