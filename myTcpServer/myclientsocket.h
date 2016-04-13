#ifndef MYCLIENTSOCKET_H
#define MYCLIENTSOCKET_H

#include <QTcpSocket>

class myClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit myClientSocket(QObject *parent = 0,int clientID=0);

private:
    int clientID;
    
signals:
    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientDisConnect(int clientID,QString IP,int Port);
    
private slots:
    void ReadData();
    void DisConnect();

public slots:

};

#endif // MYCLIENTSOCKET_H
