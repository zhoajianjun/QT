#ifndef LINK_H
#define LINK_H

#include <QWidget>

namespace Ui {
class Link;
}

class Link : public QWidget
{
    Q_OBJECT

public:
    explicit Link(QWidget *parent = 0);
    ~Link();
    void paintEvent(QPaintEvent *);
private:
    Ui::Link *ui;
};

#endif // LINK_H
