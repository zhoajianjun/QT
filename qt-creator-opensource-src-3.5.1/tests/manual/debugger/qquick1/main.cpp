#include <QApplication>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDebug>

class Backend : public QObject {
    Q_OBJECT

public:
    Q_INVOKABLE void greet(const QString &toWhom);
signals:
    void greetBack(const QString &toWhom);
};


void Backend::greet(const QString &toWhom)
{
    // bp here should be hit on startup
    qDebug() << "hello" << toWhom;

    // let's call back through signal ...
    emit greetBack("QML");
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);


    QDeclarativeView view;
    Backend backend;
    view.rootContext()->setContextProperty("backend", &backend);

    view.setSource(QUrl::fromLocalFile(SRCDIR"/qml/main.qml"));
    view.show();

    app.exec();
}

#include "main.moc"
