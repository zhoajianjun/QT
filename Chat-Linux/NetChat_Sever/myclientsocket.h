#ifndef MYCLIENTSOCKET_H
#define MYCLIENTSOCKET_H

#include <QTcpSocket>

class myClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit myClientSocket(QObject *parent = 0);
    QString ClientID;
    QString IP;
    QString Port;
    QString Password;

signals:

public slots:
    void ReadData_Client();
//    void WriteData_Client();


};

#endif // MYCLIENTSOCKET_H
