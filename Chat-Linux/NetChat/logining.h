#ifndef LOGINING_H
#define LOGINING_H

#include <QWidget>
#include <QTimer>
#include <QTcpSocket>
namespace Ui {
class Logining;
}

class Logining : public QWidget
{
    Q_OBJECT

public:
    explicit Logining(QWidget *parent = 0);
    ~Logining();
    void paintEvent(QPaintEvent *);
    QTcpSocket *tcpClient;
protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void progressBar_init();
    void form_init();
    void socket_init();
private slots:
    void on_Close_pushButton_clicked();
    void ProgressValue();
    void on_login_button_clicked();
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
private:
    QTimer *timer;
    QPoint dragPosition;
    Ui::Logining *ui;
    int Progress_value;

};

#endif // LOGINING_H
