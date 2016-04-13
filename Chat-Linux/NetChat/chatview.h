#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <frienditem.h>
#include <chatitem.h>
namespace Ui {
class ChatView;
}
class FriendItem;
class ChatItem;
class ChatView : public QWidget
{
    Q_OBJECT

public:

    static ChatView* getInstance()
    {
        if(w == NULL)  //判断是否第一次调用
                    w = new ChatView();
                return w;
    }
    static ChatView *w;
    QVector<QString> Chating_UserId;
    QVector<ChatItem *> Chating_Widget;
    ~ChatView();

//    void addChat(FriendItem *parent);

    void addChat(UserData::UserInfo *it);
    void addMsg(int row ,QString newMsg);
protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void form_init();
    void paintEvent(QPaintEvent *);
public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void CloseChat();
private:
    Ui::ChatView *ui;
    QPoint dragPosition;
    ChatView();
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;


};

#endif // CHATVIEW_H
