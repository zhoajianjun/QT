#include "devicesearchapi.h"
#include "api/myhelper.h"

DeviceSearchAPI::DeviceSearchAPI(QObject *parent) : QObject(parent)
{
    udp = new QUdpSocket(this);
    connect(udp, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

bool DeviceSearchAPI::Init()
{
    bool ok = udp->bind(QHostAddress::Any, App::SearchPort, QUdpSocket::ShareAddress);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,5))
    udp->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    udp->joinMulticastGroup(QHostAddress(App::SearchIP));
#endif
    return ok;
}

void DeviceSearchAPI::Search()
{
    QStringList data;
    data.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    data.append("<Server><SearchDevice /></Server>");

    QString buffer = data.join("");
    int len = buffer.length();
    buffer = QString("IALARM:%1").arg(len, 13, 10, QLatin1Char('0')) + buffer;
    udp->writeDatagram(buffer.toLatin1(), QHostAddress(App::SearchIP), App::SearchPort);
}

void DeviceSearchAPI::ReadData()
{
    do {
        QByteArray buffer;
        int bufferLen = udp->pendingDatagramSize();
        buffer.resize(bufferLen);
        udp->readDatagram(buffer.data(), bufferLen);

        if (bufferLen <= 37) {
            continue;
        }

        QByteArray data = buffer.mid(20, bufferLen);

        QDomDocument dom;
        if(!dom.setContent(data)) {
            App::WriteError("xml error in DeviceSearchAPI");
            continue;
        }

        QDomElement element = dom.documentElement();
        if(element.tagName() == "Device") {
            QString ip = element.attribute("DeviceIP");
            QString mask = element.attribute("Mask");
            QString gateway = element.attribute("Gateway");
            QString mac = element.attribute("MAC");
            if (!mac.contains("-")){
                QString temp;
                for (int i=0;i<mac.length();i=i+2){
                    temp+=QString("%1-").arg(mac.mid(i,2));
                }
                mac=temp.mid(0,temp.length()-1);
            }
            QString defenceID = element.attribute("DefenceID");
            emit receiveDevice(ip, mask, gateway, mac, defenceID);            
        }
    } while(udp->hasPendingDatagrams());
}
