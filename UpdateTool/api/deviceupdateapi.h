#ifndef DEVICEUPDATEAPI_H
#define DEVICEUPDATEAPI_H

#include <QObject>
#include <QMutex>

class QTcpSocket;
class QProgressBar;

class DeviceUpdateAPI : public QObject
{
    Q_OBJECT
public:
    explicit DeviceUpdateAPI(QObject *parent = 0);

    static DeviceUpdateAPI *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new DeviceUpdateAPI;
            }
        }
        return _instance;
    }

    void Start(QString deviceIP, int devicePort, QString fileName, QProgressBar *bar);

private:
    static DeviceUpdateAPI *_instance;

    QTcpSocket *socket;
    QProgressBar *bar;

private slots:
    void Error();
    void Disconnected();

signals:

public slots:
};

#endif // DEVICEUPDATEAPI_H
