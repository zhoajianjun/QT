#ifndef LISTWIDGET_H
#define LISTWIDGET_H
#include <QtGui>
#include <QLabel>
#include <QListWidget>

class ListWidget : public QWidget
{
public:
        ListWidget();

private:
        QLabel *label;
        QListWidget *list;
};

#endif // LISTWIDGET_H
