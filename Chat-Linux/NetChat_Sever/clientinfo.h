#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <QTcpSocket>

class ClientInfo
{
    Q_OBJECT
public:
    ClientInfo();
    QString ClientID;
    QString IP;
    QString Port;
    QString Password;
    QTcpSocket *ClientSocket;
public slots:
    void ReadData_Client();
private:
    void ClientSocket_init();
};

#endif // CLIENTINFO_H
