#include "Xmltest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Xmltest w;
    w.show();

    return a.exec();
}
