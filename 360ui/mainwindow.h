#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

namespace Ui {
class MainWindow;
}
class QPushButton;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void on_menuBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();



    void on_closeBtn_clicked();

    void on_nomalBtn_clicked();

    void on_minBtn_clicked();

private:
    Ui::MainWindow *ui;
    QAction *m_AactionAboutQt;
    QPixmap m_pixmapBg;

    QMenu *m_menu;

    QPoint m_pointStart;
    QPoint m_pointPress;

    QVector <QPushButton* > m_vecBtn;

    ///成员变量初始化;
    void initData();

    ///自定义窗口样式;
    void setNomalStyle();

    ///功能选择函数;
    void setCurrentWidget();
};

#endif // MAINWINDOW_H
