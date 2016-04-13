#ifndef DEVICESEARCHAPI_H
#define DEVICESEARCHAPI_H

#include <QObject>

class QUdpSocket;

class DeviceSearchAPI : public QObject
{
    Q_OBJECT
public:
    explicit DeviceSearchAPI(QObject *parent = 0);

    bool Init();

private:
    QUdpSocket *udp;

private slots:
    void ReadData();    

signals:
    void receiveDevice(QString ip, QString mask, QString gateway, QString mac, QString defenceID);

public slots:
    void Search();

};

#endif // DEVICESEARCHAPI_H
