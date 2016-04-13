#ifndef MSGGROUPBOX_H
#define MSGGROUPBOX_H

#include <QGroupBox>
#include <QLabel>
class MsgGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    MsgGroupBox(int type,QString Avatar,QString Msg);
    MsgGroupBox(QString Record);

signals:

public slots:
private:
    QLabel *AvatarLabel;
    QLabel *MsgLabel;
    QLabel *TimeLabel;
    int type;
    void init();

};

#endif // MSGGROUPBOX_H
