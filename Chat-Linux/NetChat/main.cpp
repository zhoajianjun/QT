#include "login.h"
#include <QApplication>
#include <QStandardItemModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    a.setWindowIcon(QIcon("app.ico"));
    return a.exec();
}
