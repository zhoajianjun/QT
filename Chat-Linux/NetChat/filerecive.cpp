#include "filerecive.h"
#include "ui_filerecive.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
FileRecive::FileRecive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileRecive)
{
    ui->setupUi(this);
    form_init();
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    tClient = new QTcpSocket(this);
    tPort = 5555;

    connect(tClient, SIGNAL(readyRead()), this, SLOT(readMsg()));
    connect(tClient, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(displayErr(QAbstractSocket::SocketError)));
}

void FileRecive::Init(UserData::UserInfo *user)
{
    this->user = user;
    ui->FriendAvatar_label->setPixmap(QPixmap(UserData::AvatarPath+user->UserAvatar));
    ui->OwnAvatar_label->setPixmap(QPixmap(UserData::AvatarPath+UserData::OwnInfo.UserAvatar));
//    ui->transProgressBar->hide();
//    ui->Send_pushButton->setEnabled(false);

}
void FileRecive::readMsg()
{
    QDataStream in(tClient);
    in.setVersion(QDataStream::Qt_5_3);

    float useTime = time.elapsed();
    qDebug()<<"1";
    if (bytesReceived <= sizeof(qint64)*2) {
        qDebug()<<"2";
        if ((tClient->bytesAvailable() >= sizeof(qint64)*2) && (fileNameSize == 0))
        {
            in>>totalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        qDebug()<<"3";
        if((tClient->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)){
            in>>fileName;
            bytesReceived +=fileNameSize;

            if(!localFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n%2.").arg(fileName).arg(localFile->errorString()));
                return;
            }
        } else {
            return;
        }
    }
    qDebug()<<"4";
    if (bytesReceived < totalBytes) {
        bytesReceived += tClient->bytesAvailable();
        inBlock = tClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    qDebug()<<"5";
    ui->transProgressBar->setMaximum(totalBytes);
    ui->transProgressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    ui->Status_label->setText(tr("已接收 %1MB (%2MB/s) \n共%3MB 已用时：%4秒\n估计剩余时间：%5秒")
                                      .arg(bytesReceived / (1024*1024))
                                      .arg(speed*1000/(1024*1024),0,'f',2)
                                      .arg(totalBytes / (1024 * 1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(totalBytes/speed/1000 - useTime/1000,0,'f',0));

    qDebug()<<"6";
    if(bytesReceived == totalBytes)
    {
        localFile->close();
        tClient->close();
        ui->Status_label->setText(tr("接收文件 %1 完毕").arg(fileName));
        ui->Refuse_pushButton->setText("完成");
    }
}
void FileRecive::setFileName(QString name)
{
    localFile = new QFile(name);
}

void FileRecive::newConn()
{
    blockSize = 0;
    tClient->abort();
    tClient->connectToHost("127.0.0.1", tPort);
    time.start();
}


void FileRecive::displayErr(QAbstractSocket::SocketError sockErr)
{
    switch(sockErr)
    {
    case QAbstractSocket::RemoteHostClosedError : break;
    default : qDebug() << tClient->errorString();
    }
}

FileRecive::~FileRecive()
{
    delete ui;
}



void FileRecive::on_pushButton_clicked()
{
    tClient->abort();
    if (localFile->isOpen())
        localFile->close();
    close();
}
void FileRecive::on_Refuse_pushButton_clicked()
{
    if(ui->Refuse_pushButton->text() == "完成")
    {
        tClient->abort();
        if (localFile->isOpen())
            localFile->close();
        close();
    }
    else{
        tClient->abort();
        if (localFile->isOpen())
            localFile->close();
    }

}



void FileRecive::form_init()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}
void FileRecive::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(0,0,QPixmap(":/images/images/LoginBack1.png"));//绘制图片到窗口
}

void FileRecive::mousePressEvent(QMouseEvent *event)

{

    if(event->button()==Qt::LeftButton)

    {

        dragPosition=event->globalPos()-frameGeometry().topLeft();

        event->accept();

    }

    if(event->button()==Qt::RightButton)
    {
    }
}

void FileRecive::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口

        event->accept();
    }
}


