#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintarea.h"
#include <QScrollArea>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void doNew();    //�½��ļ�����
    void doOpen();   //���ļ�����
    bool doFileSave();   //�����ļ�����
    bool doFileSaveAs();   //�ļ����Ϊ����

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    PaintArea *area;
    QScrollArea *scrollArea;

    bool isSaved;   //��־�ļ��Ƿ񱣴��
    QString curFile;  //���浱ǰ�ļ���·��
    bool maybeSave();   //�Ƿ񱣴��ļ�

    bool saveFile(QString fileName);   //ʵ���ļ��Ĵ洢


private slots:
    void on_action_P_triggered();
    void on_action_X_triggered();
    void on_action_A_triggered();
    void on_action_S_triggered();
    void on_action_O_triggered();
    void on_action_N_triggered();
};

#endif // MAINWINDOW_H
