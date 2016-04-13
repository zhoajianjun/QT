#include "frmmain.h"
#include <QApplication>
#include "api/appinit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppInit *init = new AppInit;
    init->Load();

    frmMain w;
    w.show();

    return a.exec();
}
