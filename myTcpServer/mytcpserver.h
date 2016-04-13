#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include "myclientsocket.h"

class myTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myTcpServer(QObject *parent = 0);
    void SendData(int clientID,QString IP,int Port,QByteArray data);

private:
    QList<myClientSocket *> ClientSocketList;
    QList<int> ClientSocketID;

protected:
    void incomingConnection(int handle);
    
signals:
    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);
    
private slots:
    void ReadData(int clientID,QString IP,int Port,QByteArray data);
    void DisConnect(int clientID,QString IP,int Port);

public slots:
    
};

#endif // MYTCPSERVER_H
