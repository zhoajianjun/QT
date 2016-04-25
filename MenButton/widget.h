#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QPushButton;
class QMenu;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void on_menuBtn_clicked();

private:
    Ui::Widget *ui;
private:
    QPushButton *m_menuBtn;
    QMenu *m_menu;
    QAction *m_AactionAboutQt;
};

#endif // WIDGET_H
