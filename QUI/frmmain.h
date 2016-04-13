#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>

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

private slots:
    void on_btnMenu_Max_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_cboxStyle_currentIndexChanged(const QString &arg1);

private:
    Ui::frmMain *ui;

    void InitStyle();   //初始化无边框窗体
    void InitForm();    //初始化窗体数据

    bool max;           //是否处于最大化状态
    QRect location;     //鼠标移动窗体后的坐标位置

};

#endif // FRMMAIN_H
