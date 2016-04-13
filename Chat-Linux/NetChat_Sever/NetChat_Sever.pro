#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T10:01:40
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetChat_Sever
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp \
    userdata.cpp \
    clientsocket.cpp \
    chatserver.cpp

HEADERS  += server.h \
    userdata.h \
    clientsocket.h \
    chatserver.h

FORMS    += server.ui
