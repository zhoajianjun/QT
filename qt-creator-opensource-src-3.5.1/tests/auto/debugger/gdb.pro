QTC_LIB_DEPENDS += utils
QT = core network
include(../qttest.pri)

DEBUGGERDIR = $$IDE_SOURCE_TREE/src/plugins/debugger

INCLUDEPATH += $$DEBUGGERDIR

SOURCES += \
    tst_gdb.cpp \
    $$DEBUGGERDIR/debuggerprotocol.cpp \

