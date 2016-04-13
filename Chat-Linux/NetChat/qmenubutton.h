#ifndef QMENUBUTTON_H
#define QMENUBUTTON_H

#include <QPushButton>
class QMenu;
class QMenuButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QMenuButton(QWidget *parent = 0);
    QMenu * getmenu();

signals:

protected:
//    void setIcon(QIcon icon);
public slots:
    void popupmenu();
private:
 QMenu * menu;
};

#endif // QMENUBUTTON_H
