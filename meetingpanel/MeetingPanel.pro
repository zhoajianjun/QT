TEMPLATE = app

DESTDIR = $${PWD}/bin/linux

QT += qml quick

SOURCES += main.cpp \
    fileio.cpp \
    sortfilterproxymodel.cpp \
    XmlToJsonConvertor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    fileio.h \
    sortfilterproxymodel.h \
    XmlToJsonConvertor.h \
    xml2json/include/rapidjson/error/en.h \
    xml2json/include/rapidjson/error/error.h \
    xml2json/include/rapidjson/internal/biginteger.h \
    xml2json/include/rapidjson/internal/diyfp.h \
    xml2json/include/rapidjson/internal/dtoa.h \
    xml2json/include/rapidjson/internal/ieee754.h \
    xml2json/include/rapidjson/internal/itoa.h \
    xml2json/include/rapidjson/internal/meta.h \
    xml2json/include/rapidjson/internal/pow10.h \
    xml2json/include/rapidjson/internal/stack.h \
    xml2json/include/rapidjson/internal/strfunc.h \
    xml2json/include/rapidjson/internal/strtod.h \
    xml2json/include/rapidjson/internal/swap.h \
    xml2json/include/rapidjson/msinttypes/inttypes.h \
    xml2json/include/rapidjson/msinttypes/stdint.h \
    xml2json/include/rapidjson/allocators.h \
    xml2json/include/rapidjson/document.h \
    xml2json/include/rapidjson/encodedstream.h \
    xml2json/include/rapidjson/encodings.h \
    xml2json/include/rapidjson/filereadstream.h \
    xml2json/include/rapidjson/filewritestream.h \
    xml2json/include/rapidjson/memorybuffer.h \
    xml2json/include/rapidjson/memorystream.h \
    xml2json/include/rapidjson/pointer.h \
    xml2json/include/rapidjson/prettywriter.h \
    xml2json/include/rapidjson/rapidjson.h \
    xml2json/include/rapidjson/reader.h \
    xml2json/include/rapidjson/stringbuffer.h \
    xml2json/include/rapidjson/writer.h \
    xml2json/include/rapidxml/rapidxml.hpp \
    xml2json/include/rapidxml/rapidxml_iterators.hpp \
    xml2json/include/rapidxml/rapidxml_print.hpp \
    xml2json/include/rapidxml/rapidxml_utils.hpp \
    xml2json/include/xml2json.hpp













