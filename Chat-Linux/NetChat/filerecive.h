#ifndef FILERECIVE_H
#define FILERECIVE_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <QTime>
#include <QHostAddress>
#include <userdata.h>
namespace Ui {
class FileRecive;
}

class FileRecive : public QWidget
{
    Q_OBJECT

public:
    explicit FileRecive(QWidget *parent = 0);
    ~FileRecive();
    void newConn();
    void setFileName(QString name);
    void Init(UserData::UserInfo *user);
private slots:

    void on_Refuse_pushButton_clicked();

    void readMsg();
    void displayErr(QAbstractSocket::SocketError);
    void on_pushButton_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void form_init();
    void paintEvent(QPaintEvent *);

private:
    Ui::FileRecive *ui;
    QTcpSocket *tClient;
    quint16 blockSize;
    QHostAddress hostAddr;
    qint16 tPort;

    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 fileNameSize;
    QString fileName;
    QFile *localFile;
    QByteArray inBlock;
    QTime time;
    QPoint dragPosition;

    UserData::UserInfo *user;
};

#endif // FILERECIVE_H
