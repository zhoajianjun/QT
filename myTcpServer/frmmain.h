#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "mytcpserver.h"

namespace Ui {
class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT
    
public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();
    
private slots:

    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);
    void on_btnListen_clicked();

    void on_btnSend_clicked();

    void on_btnClear_clicked();

private:
    Ui::frmMain *ui;

    myTcpServer *server;

    void Init();

};

#endif // FRMMAIN_H
