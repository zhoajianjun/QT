TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    replacealgorithm.cpp \
    lrureplacealgorithm.cpp \
    fiforeplacealgorithm.cpp \
    cache.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    replacealgorithm.h \
    lrureplacealgorithm.h \
    fiforeplacealgorithm.h \
    cache.h

