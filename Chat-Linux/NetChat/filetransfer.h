#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QWidget>
#include <userdata.h>
#include <QTime>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class FileTransfer;
}

class FileTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit FileTransfer(QWidget *parent = 0);
    void Init(UserData::UserInfo *user);

    void refused();
    void initServer();


    ~FileTransfer();

private slots:
    void on_Open_pushButton_clicked();
    void on_Send_pushButton_clicked();
    void on_FileName_lineEdit_textChanged(const QString &arg1);
    void on_pushButton_clicked();
    void SendFile();
    void UpdateProgress(qint64 numBytes);

protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void form_init();
    void paintEvent(QPaintEvent *);
    void sendFileName(QString fileName);
signals:

private:

    qint16 tPort;
    QTcpServer *tServer;
    QString fileName;
    QString theFileName;
    QFile *localFile;
    QTcpSocket *clientConnection;
    QTime time;

    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesTobeWrite;
    qint64 payloadSize;

    QByteArray outBlock;
    Ui::FileTransfer *ui;
    QPoint dragPosition;

    UserData::UserInfo *user;


};

#endif // FILETRANSFER_H
