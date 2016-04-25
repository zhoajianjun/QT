#include "messagebox.h"
#include <QApplication>
#include <QFile>

void SetStyle(const QString &qssFile) {
        QFile file(qssFile);
        if (file.open(QFile::ReadOnly)) {
            QString qss = QLatin1String(file.readAll());
            qApp->setStyleSheet(qss);
            QString PaletteColor = qss.mid(20, 7);
            qApp->setPalette(QPalette(QColor(PaletteColor)));
            file.close();
        }
    }
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MessageBox w;
    w.show();

    return a.exec();
}
