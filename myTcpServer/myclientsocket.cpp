#include "myclientsocket.h"
#include <QHostAddress>

myClientSocket::myClientSocket(QObject *parent,int clientID) :
    QTcpSocket(parent)
{    
    this->clientID=clientID;
    connect(this,SIGNAL(readyRead()),this,SLOT(ReadData()));//挂接读取数据信号
    connect(this,SIGNAL(disconnected()),this,SLOT(DisConnect()));//关闭连接时，发送断开连接信号
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));//关闭连接时，对象自动删除
}

void myClientSocket::ReadData()
{
    //读取完整一条数据并发送信号
    QByteArray data=this->readAll();
    emit ClientReadData(this->clientID,this->peerAddress().toString(),this->peerPort(),data);
}

void myClientSocket::DisConnect()
{
    //断开连接时，发送断开信号
    emit ClientDisConnect(this->clientID,this->peerAddress().toString(),this->peerPort());
}
