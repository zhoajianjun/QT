TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    MyString.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    MyString.h

