TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    os.cpp \
    windowos.cpp \
    linuxos.cpp \
    unixos.cpp \
    compute.cpp \
    dellcompute.cpp \
    applecompute.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    os.h \
    windowos.h \
    linuxos.h \
    unixos.h \
    compute.h \
    dellcompute.h \
    applecompute.h

