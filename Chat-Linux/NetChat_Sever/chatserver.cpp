#include "chatserver.h"
#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QVector>
#include <userdata.h>
ChatServer::ChatServer(QObject *parent) :
    QTcpServer(parent)
{
    ClientSocket_lists.empty();
}
ChatServer::~ChatServer()
{
    qDeleteAll(ClientSocket_lists );
       ClientSocket_lists.clear();
}
bool ChatServer::Run()
{

     return this->listen(QHostAddress::Any,12345);
}

void ChatServer::incomingConnection(qintptr handle )
{

    ClientSocket *mysocket = new ClientSocket( this );
    mysocket->setSocketDescriptor( handle );
    connect( mysocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()) );
    ClientSocket_lists.append( mysocket );
}

void ChatServer::clientDisconnected()
{

}
