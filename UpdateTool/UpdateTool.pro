#-------------------------------------------------
#
# Project created by QtCreator 2014-08-15T14:34:50
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UpdateTool
TEMPLATE = app

SOURCES += main.cpp\
        frmmain.cpp \
    api/iconhelper.cpp \
    api/app.cpp \
    api/appinit.cpp \
    api/applog.cpp \
    api/deviceupdateapi.cpp \
    api/devicesearchapi.cpp \
    usercontrol/frmmessagebox.cpp \
    usercontrol/frminputbox.cpp \
    usercontrol/combobox.cpp \
    usercontrol/qdelegate.cpp

HEADERS  += frmmain.h \
    api/iconhelper.h \
    api/myhelper.h \
    api/app.h \
    api/appinit.h \
    api/applog.h \
    api/deviceupdateapi.h \
    api/devicesearchapi.h \
    usercontrol/frmmessagebox.h \    
    usercontrol/frminputbox.h \
    usercontrol/combobox.h \
    usercontrol/qdelegate.h

FORMS    += frmmain.ui \
    usercontrol/frmmessagebox.ui \
    usercontrol/frminputbox.ui

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/usercontrol

MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = bin

win32:RC_FILE   = other/main.rc

RESOURCES += \
    other/rc.qrc
