#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include "clientsocket.h"
class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = 0);
    ~ChatServer();
    QList<ClientSocket*>  ClientSocket_lists;
    bool Run();
//    bool Stop();
protected:
    void    incomingConnection(qintptr handle );

private slots:
    void clientDisconnected  ();
//    void newClient_connect();
signals:

public slots:

};

#endif // CHATSERVER_H
