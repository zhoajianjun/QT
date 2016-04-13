#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QUdpSocket>
class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
    QUdpSocket *Server_UdpSocket;

signals:

public slots:
    void    ReadData_Client();
};

#endif // CLIENTSOCKET_H
