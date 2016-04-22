#include "XmlToJsonConvertor.h"

#include "xml2json/include/xml2json.hpp"

XmlToJsonConvertor::XmlToJsonConvertor(QObject *parent) : QObject(parent)
{

}

QString XmlToJsonConvertor::convert(const QString &data)
{
    std::string json = xml2json(data.toUtf8().constData());
    return QString::fromUtf8(json.c_str());
}

