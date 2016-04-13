#ifndef FRIENDSLIST_H
#define FRIENDSLIST_H

#include <QWidget>
#include <QToolBox>
#include <frienditem.h>
namespace Ui {
class FriendsList;
}
class ChatView;
class FriendsList : public QWidget
{
    Q_OBJECT

public:
    explicit FriendsList(QWidget *parent = 0);
    ~FriendsList();
//    QString UserID;


    void Update(QString msg);
    void ReciveFile(QString msg);
    void ReciveMsg(QString msg);
    void IsOnline(QHostAddress IP,qint16 Port);

    void Init();
    void FriendsInit();
    void GroupsInit();
    void NearInit();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
//    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_Close_pushButton_clicked();
    void BoxChanged();
    void AnalyseMessage();
private:
    Ui::FriendsList *ui;
    QPoint dragPosition;
    QToolBox *friends_box;
    QGroupBox *Groups_box;

    FriendItem *frienditem;

    ChatView *chatWindow;

    QVector <FriendItem*> FriendItemList;

};

#endif // FRIENDSLIST_H
