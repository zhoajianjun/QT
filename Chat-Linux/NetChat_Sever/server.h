#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include "chatserver.h"
#include <QUdpSocket>
namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
    ChatServer *MyServer;
    QUdpSocket *Server_UdpSocket;
    QTimer *timer;
private slots:

    void on_Listen_pushButton_clicked();
    void UpdateInfo();
    void ReadMessage();

private:
    Ui::Server *ui;

};

#endif // SERVER_H
