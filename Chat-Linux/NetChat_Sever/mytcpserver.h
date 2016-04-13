#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <myclientsocket.h>
#include "clientinfo.h"
class myTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myTcpServer(QObject *parent = 0);
    QList<ClientInfo *> ClientInfoList;
signals:
protected:
//    void incomingConnection();
public slots:
    void newConnect();
};

#endif // MYTCPSERVER_H
