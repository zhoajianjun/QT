TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    singlecore.cpp \
    singlecorea.cpp \
    singlecoreb.cpp \
    multicore.cpp \
    multicorea.cpp \
    multicoreb.cpp \
    corefactory.cpp \
    factorya.cpp \
    factoryb.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    singlecore.h \
    singlecorea.h \
    singlecoreb.h \
    multicore.h \
    multicorea.h \
    multicoreb.h \
    corefactory.h \
    factorya.h \
    factoryb.h

