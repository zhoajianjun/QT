QTC_LIB_DEPENDS += qmljs
include(../../qttest.pri)

DEFINES+=QTCREATORDIR=\\\"$$IDE_SOURCE_TREE\\\"
DEFINES+=TESTSRCDIR=\\\"$$_PRO_FILE_PWD_\\\"

TARGET = tst_reformatter

SOURCES += \
    tst_reformatter.cpp
