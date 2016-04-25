#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class MessageBox : public QDialog
{
    Q_OBJECT

public:
    MessageBox(QWidget *parent = 0);
    ~MessageBox();
public:
    void InitStyle();
    void SetMessage(QString msg, int type);
private:
    QLabel* m_lab;
    QLabel* m_labIcoMain;
    QLabel* m_labTitle;
    QLabel* m_labInfo;
    QWidget* m_titleWidget;
    QWidget* m_mainWidget;
    QPushButton* m_closeBtn;

};

#endif // MESSAGEBOX_H
