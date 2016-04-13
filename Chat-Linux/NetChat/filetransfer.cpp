#include "filetransfer.h"
#include "ui_filetransfer.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
//#include <userdata.h>
FileTransfer::FileTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileTransfer)
{
    ui->setupUi(this);
    form_init();
    tPort = 5555;
    tServer = new QTcpServer(this);
    connect(tServer,SIGNAL(newConnection()),this,SLOT(SendFile()));
    initServer();

}

void FileTransfer::initServer()
{
    payloadSize = 64*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesTobeWrite = 0;
    ui->transProgressBar->reset();
    tServer->close();
}

void FileTransfer::Init(UserData::UserInfo *user)
{

    this->user = user;
    ui->FriendAvatar_label->setPixmap(QPixmap(UserData::AvatarPath+user->UserAvatar));
    ui->OwnAvatar_label->setPixmap(QPixmap(UserData::AvatarPath+UserData::OwnInfo.UserAvatar));
    ui->transProgressBar->hide();
    ui->Send_pushButton->setEnabled(false);

}

FileTransfer::~FileTransfer()
{
    delete ui;
}


void FileTransfer::SendFile()
{
    ui->transProgressBar->show();
    ui->transProgressBar->reset();
    ui->Send_pushButton->setEnabled(false);
    clientConnection = tServer->nextPendingConnection();
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(UpdateProgress(qint64)));
    ui->Status_label->setText("开始传送.......");


    localFile = new QFile(fileName);
    if(!localFile->open((QFile::ReadOnly))){
        QMessageBox::warning(this, tr("应用程序"), tr("无法读取文件 %1:\n%2").arg(fileName).arg(localFile->errorString()));
        return;
    }
    totalBytes = localFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_3);
    time.start();  // 开始计时
    QString curFile = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << curFile;
    totalBytes += outBlock.size();
    sendOut.device()->seek(0);
    sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64)*2));
    bytesTobeWrite = totalBytes - clientConnection->write(outBlock);
    outBlock.resize(0);

}

void FileTransfer::UpdateProgress(qint64 numBytes)
{
    qApp->processEvents();
    bytesWritten += (int)numBytes;
    if (bytesTobeWrite > 0) {
        outBlock = localFile->read(qMin(bytesTobeWrite, payloadSize));
        bytesTobeWrite -= (int)clientConnection->write(outBlock);
        outBlock.resize(0);
    } else {
        localFile->close();
    }
    ui->transProgressBar->setMaximum(totalBytes);
    ui->transProgressBar->setValue(bytesWritten);

    float useTime = time.elapsed();
    double speed = bytesWritten / useTime;
    ui->Status_label->setText(tr("已发送 %1MB (%2MB/s) \n共%3MB 已用时:%4秒\n估计剩余时间：%5秒")
                   .arg(bytesWritten / (1024*1024))
                   .arg(speed*1000 / (1024*1024), 0, 'f', 2)
                   .arg(totalBytes / (1024 * 1024))
                   .arg(useTime/1000, 0, 'f', 0)
                   .arg(totalBytes/speed/1000 - useTime/1000, 0, 'f', 0));

    if(bytesWritten == totalBytes) {
        localFile->close();
        tServer->close();
        ui->Status_label->setText(tr("传送文件 %1 成功").arg(theFileName));

        ui->FileName_lineEdit->clear();
        ui->Open_pushButton->setEnabled(true);
        ui->Send_pushButton->setEnabled(false);

    }
}
void FileTransfer::on_Open_pushButton_clicked()
{
    ui->Send_pushButton->setEnabled(true);
    fileName = QFileDialog::getOpenFileName(this,tr("打开文件"),
                                                    "/home/rcl",
                                                    tr("所有文件*.*(*.*)"));
    //! 获得要打开的文件的名字
    if(fileName.isEmpty())//! 如果文件名为空
    {
        QMessageBox::information( this, "Information", "FileName is wrong!" );
        return;
    }
    ui->FileName_lineEdit->setText(fileName);
    theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') -1);

}

void FileTransfer::on_Send_pushButton_clicked()
{

    if(!tServer->listen(QHostAddress::Any,tPort))
    {
        qDebug()<<tServer->errorString();
        close();
        return;
    }
    ui->Status_label->setText("等待对方接收.....");
    sendFileName(theFileName);
    ui->Open_pushButton->setEnabled(false);

}

void FileTransfer::sendFileName(QString fileName)
{
    QUdpSocket *Send_UdpSocket = new QUdpSocket(this);
    if(user->UserStatus == "0")
    {
        QMessageBox::warning(this,tr("警告"),tr("该用户不在线！！！"));
        return;
    }
    QByteArray ask = QString("#FILE#"+UserData::OwnInfo.UserID+"|"+user->UserID+"|"+fileName).toLatin1();
    Send_UdpSocket->writeDatagram(ask,ask.size(),QHostAddress(user->UserIP),user->UserPort.toInt());


}


void FileTransfer::on_FileName_lineEdit_textChanged(const QString &arg1)
{

}

void FileTransfer::on_pushButton_clicked()
{
    if(tServer->isListening())
    {
        tServer->close();
        if(localFile->isOpen())
        {
            localFile->close();
        }
        clientConnection->abort();
    }
    close();
}



void FileTransfer::form_init()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}
void FileTransfer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(0,0,QPixmap(":/images/images/LoginBack1.png"));//绘制图片到窗口
}

void FileTransfer::mousePressEvent(QMouseEvent *event)

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

void FileTransfer::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口

        event->accept();
    }
}



