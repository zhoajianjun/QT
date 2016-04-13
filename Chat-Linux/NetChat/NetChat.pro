#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T18:58:13
#
#-------------------------------------------------
QT       += network
QT       += core gui
QT       += multimedia
QT +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_FILE = icon.rc
TARGET = NetChat
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    userdata.cpp \
    friendslist.cpp \
    register.cpp \
    myhelper.cpp \
    logining.cpp \
    qmenubutton.cpp \
    mywidget.cpp \
    frienditem.cpp \
    chatview.cpp \
    chatitem.cpp \
    msggroupbox.cpp \
    filetransfer.cpp \
    filerecive.cpp \
    groupitem.cpp

HEADERS  += login.h \
    userdata.h \
    friendslist.h \
    register.h \
    myhelper.h \
    logining.h \
    qmenubutton.h \
    mywidget.h \
    frienditem.h \
    chatview.h \
    chatitem.h \
    msggroupbox.h \
    filetransfer.h \
    filerecive.h \
    groupitem.h

FORMS    += login.ui \
    friendslist.ui \
    register.ui \
    logining.ui \
    filetransfer.ui \
    filerecive.ui

RESOURCES += \
    images.qrc

OTHER_FILES +=
