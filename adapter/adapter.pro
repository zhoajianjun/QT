TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    deque.cpp \
    sequence.cpp \
    stack.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    deque.h \
    sequence.h \
    stack.h

