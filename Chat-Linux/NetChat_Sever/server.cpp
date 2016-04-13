#include "server.h"
#include "ui_server.h"
#include <QtGui>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>
#include "userdata.h"
Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    UserData::Link();
    Server_UdpSocket = new QUdpSocket(this);
    Server_UdpSocket->bind(UserData::port.toInt());
    this->timer = new QTimer();
    timer->setInterval(10000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateInfo()));
    connect(Server_UdpSocket,SIGNAL(readyRead()),this,SLOT(ReadMessage()));
}

Server::~Server()
{
    delete ui;
}
void Server::ReadMessage()
{
    QByteArray Buffer;
    Server_UdpSocket->hasPendingDatagrams();
    Buffer.resize(Server_UdpSocket->pendingDatagramSize());
    Server_UdpSocket->readDatagram(Buffer.data(), Buffer.size());
    QString msg = QVariant(Buffer).toString();
    qDebug()<<"&&&&&&&&&&&"<<msg;
    if(msg.startsWith("#IsOnline#"))
    {
        QString userID = msg.remove(0,10);
        QVector<UserData::Client>::iterator it = UserData::Client_List.begin();
        for(;it != UserData::Client_List.end();++it)
        {
            if(it->ClientID == userID)
            {
                it->online = true;
            }
        }
    }


}
void Server::UpdateInfo()
{

    QVector<UserData::Client>::iterator it = UserData::Client_List.begin();
    for(int i=0;i < UserData::Client_List.count();++i,++it)
    {
        if(UserData::Client_List.at(i).online == false)
        {


            QVector<UserData::Client>::iterator iter = UserData::Client_List.begin();
            for(;iter != UserData::Client_List.end();++iter)
            {
                if(UserData::IsFriend(it->ClientID,iter->ClientID))
                {

                    QString update = it->ClientID+"|"+UserData::ip+"|"+UserData::port+"|";
                    update.append("0");
                    QByteArray information = QString("#Update#"+update).toLatin1();
                    qDebug()<<QString("#Update#"+update);
                    Server_UdpSocket->writeDatagram(information,information.size(),QHostAddress(iter->IP),iter->Port.toInt());
                }

            }
            UserData::Client_List.removeAt(i);

            continue;
        }
        else
            it->online = false;
        QByteArray ask =QString("#IsOnline#").toLatin1();
        Server_UdpSocket->writeDatagram(ask,ask.size(),QHostAddress(UserData::Client_List.at(i).IP),UserData::Client_List.at(i).Port.toInt());
    }

}
void Server::on_Listen_pushButton_clicked()
{
    if (ui->Listen_pushButton->text()=="开启监听")
    {
        MyServer = new ChatServer(this);
        if (MyServer->Run())
        {
            ui->Listen_pushButton->setText("停止监听");
            ui->Message_textEdit->append("监听成功");
        }
    }
    else
    {
        MyServer->close();
        ui->Listen_pushButton->setText("开启监听");
        ui->Message_textEdit->append("停止监听成功");

    }
    //    connect(MyTcpServer,SIGNAL(newConnection()),this,SLOT(newConnect()));
    //新连接信号触发，调用newConnect()槽函数，这个跟信号函数一样，其实你可以随便取。

}

