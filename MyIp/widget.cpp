#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    QHostInfo info =QHostInfo::fromName("zhaojianjun");
//    qDebug()<<info.addresses()<<endl;
//    qDebug()<<info.hostName()<<endl;
    QString localHostName = QHostInfo::localHostName();
    qDebug() <<"localHostName: "<<localHostName;
    QList<QNetworkInterface> list =QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, list) {
        qDebug()<<"Device:"<<interface.name();
        qDebug()<<"HardwareAddress:"<<interface.hardwareAddress();
        if(interface.name()=="eth0")
        {
            QList<QNetworkAddressEntry>entryList = interface.addressEntries();
            foreach (QNetworkAddressEntry entry,entryList) {
                qDebug()<<"IP Address: "<<entry.ip().toString();
                qDebug()<<"NetMask: "<<entry.netmask().toString();
                qDebug()<<"brodcast:"<<entry.broadcast().toString();
                }
        }
    }
    qDebug()<<"KK"<<getIP()<<endl;
}
Widget::~Widget()
{
    delete ui;
}

QString Widget::getIP()
{
    QList<QHostAddress>list=QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if(address.protocol()==QAbstractSocket::IPv4Protocol)
        {
            return address.toString();
        }

    }
    return 0;
}
