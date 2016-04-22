#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include  "fileio.h"
#include "sortfilterproxymodel.h"
#include "XmlToJsonConvertor.h"

#include<QtQml>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<FileIo>("readfile", 1, 0, "FileIo");
    qmlRegisterType<SortFilterProxyModel>("SortFilterProxyModel", 0, 1, "SortFilterProxyModel");
    qmlRegisterType<XmlToJsonConvertor>("XmlToJsonConvertor", 1, 0, "XmlToJsonConvertor");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
