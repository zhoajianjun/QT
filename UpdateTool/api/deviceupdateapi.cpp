#include "deviceupdateapi.h"
#include "api/myhelper.h"

DeviceUpdateAPI *DeviceUpdateAPI::_instance = 0;
DeviceUpdateAPI::DeviceUpdateAPI(QObject *parent) : QObject(parent)
{
    bar = 0;
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Error()));
}

void DeviceUpdateAPI::Start(QString deviceIP, int devicePort, QString fileName, QProgressBar *bar)
{
    socket->connectToHost(deviceIP, devicePort);
    if (socket->waitForConnected(1000)) {
        this->bar = bar;

        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)) {
            socket->disconnectFromHost();
            return;
        }

        int fileSize = file.size();
        bar->setRange(0, fileSize);

        qint64 size;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        QString name = myHelper::GetFileNameWithExtension(fileName);

        //写入开始符及文件名称
        block.clear();
        out.device()->seek(0);
        out << 0x01 << name.toUtf8();
        size = block.size();
        socket->write((char *)&size, sizeof(qint64));
        socket->write(block.data(), size);

        if(!socket->waitForBytesWritten(-1)) {
            socket->disconnectFromHost();
            return;
        }

        //写入文件大小
        block.clear();
        out.device()->seek(0);
        out << 0x02 << QString::number(file.size()).toUtf8();
        size = block.size();
        socket->write((char *)&size, sizeof(qint64));
        socket->write(block.data(), size);

        if(!socket->waitForBytesWritten(-1)) {
            socket->disconnectFromHost();
            return;
        }

        //循环写入文件数据
        do {
            block.clear();
            out.device()->seek(0);
            out << 0x03 << file.read(0xFFFF);
            size = block.size();
            socket->write((char *)&size, sizeof(qint64));
            socket->write(block.data(), size);

            if(!socket->waitForBytesWritten(-1)) {
                socket->disconnectFromHost();
                return;
            }

            bar->setValue(bar->value() + size - 12);
            qApp->processEvents();
        } while(!file.atEnd());

        //写入结束符及文件名称
        block.clear();
        out.device()->seek(0);
        out << 0x04 << name.toUtf8();
        size = block.size();
        socket->write((char *)&size, sizeof(qint64));
        socket->write(block.data(), size);

        if(!socket->waitForBytesWritten(-1)) {
            socket->disconnectFromHost();
            return;
        }

        if(socket->waitForDisconnected()) {
            bar->setValue(fileSize);
            myHelper::ShowMessageBoxInfoX("升级成功,设备稍后自动重启!");
            bar->setValue(0);
        } else {
            myHelper::ShowMessageBoxErrorX("连接设备失败!");
        }
    } else {
        myHelper::ShowMessageBoxErrorX("连接设备失败!");
    }
}

void DeviceUpdateAPI::Error()
{
    socket->disconnectFromHost();
}

void DeviceUpdateAPI::Disconnected()
{
    bar->setValue(0);
}
