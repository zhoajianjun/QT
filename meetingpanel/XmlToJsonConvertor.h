#ifndef XMLTOJSONCONVERTOR_H
#define XMLTOJSONCONVERTOR_H

#include <QObject>

class XmlToJsonConvertor : public QObject
{
    Q_OBJECT
public:
    explicit XmlToJsonConvertor(QObject *parent = 0);

    Q_INVOKABLE QString convert(const QString& data);

signals:

public slots:
};

#endif // XMLTOJSONCONVERTOR_H
