#-------------------------------------------------
#
# Project created by QtCreator 2013-09-03T16:59:03
#
#-------------------------------------------------

QT       += core gui network
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myTcpServer
TEMPLATE = app


SOURCES += main.cpp\
        frmmain.cpp \
    myclientsocket.cpp \
    mytcpserver.cpp

HEADERS  += frmmain.h \
    myhelper.h \
    myclientsocket.h \
    mytcpserver.h

FORMS    += frmmain.ui

MOC_DIR=temp/moc
RCC_DIR=temp/rcc
UI_DIR=temp/ui
OBJECTS_DIR=temp/obj
DESTDIR=bin
