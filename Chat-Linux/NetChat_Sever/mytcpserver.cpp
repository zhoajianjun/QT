#include "mytcpserver.h"
#include "myclientsocket.h"
#include "clientinfo.h"
myTcpServer::myTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    connect(this,SIGNAL(newConnection()),this,SLOT(newConnect()));
}

//void myTcpServer::newConnect()
//{
//    myClientSocket *newClientSocket = ne;
//    newClientSocket =this->nextPendingConnection();
//    ClientSocketList.append(newClientSocket);
//}

void myTcpServer::incomingConnection( int handle )
{
    printf( "incomingConnection(): %d !\n", handle );
    MySocket *mysocket = new MySocket( this );
    mysocket->setSocketDescriptor( handle );
    connect( mysocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()) );
    _mysockets.append( mysocket );
}

void myTcpServer::newConnect()
{
        ClientInfo *newClient = new ClientInfo();

//        myClientSocket *newClientSocket = new myClientSocket(this);
        newClient->ClientSocket =this->nextPendingConnection();
        ClientInfoList.append(newClient);

}
