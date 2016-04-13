#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T06:56:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ../src/framelesshelper.cpp \
    ../src/framelesshelperprivate.cpp

HEADERS  += widget.h \
    ../src/framelesshelper.h \
    ../src/framelesshelperprivate.h

FORMS    += widget.ui
