
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    resume.cpp \
    resumea.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    resume.h \
    resumea.h

