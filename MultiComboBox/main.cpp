#include "multicombobox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MultiComboBox w;
    w.show();

    return a.exec();
}
