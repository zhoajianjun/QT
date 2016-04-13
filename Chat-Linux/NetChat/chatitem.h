#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <frienditem.h>
#include <QScrollArea>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <QFile>
#include <QScrollBar>
#include <QToolButton>
#include <filetransfer.h>
class ChatItem : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItem(QWidget *parent = 0);
    ChatItem(UserData::UserInfo *it);

    void ReciveMessage(QString msg);
signals:
    void CloseCurrentWidget();
public slots:
    void SendMessage();
    void Close();
    void FileTransferWindow();
    void ClearMsg();
private:
    void init();
    void ChatNoteInit();

    UserData::UserInfo *user;
    QLabel *Status;
    QLabel *Name;
    QLabel *PS;
    QScrollArea *Chat_ScrollArea;
    QTextEdit *Chat_TextEdit;

    QPushButton *Send_PushButton;

    QPushButton *Expression_PushButton;
    QPushButton *File_PushButton;
    QPushButton *Camera_PushButton;
    QPushButton *Clear_PushButton;


    QPushButton *Close_PushButton;

    QVBoxLayout *Chat_Layout;
    QWidget *Chat_Widget;
    QScrollBar * ScrollBar;

    QUdpSocket *Send_UdpSocket;
    QHostAddress IP;
    int Port;
    int Num;


    FileTransfer *fileTransfer;
    QFile ChatNote;

};

#endif // CHATITEM_H
