#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QWidget>
#include <QLabel>
#include <userdata.h>
#include <QGroupBox>
#include <chatview.h>

class ChatView;
class GroupItem : public QWidget
{
    Q_OBJECT
public:
    explicit GroupItem(QWidget *parent = 0);
    GroupItem(QWidget *parent =0,int x =0,int y=0,UserData::UserInfo *user =NULL);
    QLabel *Avatar;
    QLabel *Status;
    QLabel *Name;
    QLabel *PS;
    QGroupBox *groupbox;
    QPixmap avatar_images;
    UserData::UserInfo *user;
signals:

public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:

    void init(UserData::UserInfo *user);

    bool IsChatOpen;
    ChatView *w;




};


#endif // GROUPITEM_H
