TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    factory.cpp \
    product.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    factory.h \
    product.h

