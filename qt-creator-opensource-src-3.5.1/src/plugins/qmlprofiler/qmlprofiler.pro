DEFINES += QMLPROFILER_LIBRARY

QT += network qml quick quickwidgets

include(../../qtcreatorplugin.pri)

SOURCES += \
    localqmlprofilerrunner.cpp \
    qmlprofileranimationsmodel.cpp \
    qmlprofilerattachdialog.cpp \
    qmlprofilerbasemodel.cpp \
    qmlprofilerbindingloopsrenderpass.cpp \
    qmlprofilerclientmanager.cpp \
    qmlprofilerdatamodel.cpp \
    qmlprofilerdetailsrewriter.cpp \
    qmlprofilerengine.cpp \
    qmlprofilereventsmodelproxy.cpp \
    qmlprofilereventview.cpp \
    qmlprofilermodelmanager.cpp \
    qmlprofilernotesmodel.cpp \
    qmlprofilerplugin.cpp \
    qmlprofilerrangemodel.cpp \
    qmlprofilerruncontrolfactory.cpp \
    qmlprofilerstatemanager.cpp \
    qmlprofilerstatewidget.cpp \
    qmlprofilertimelinemodel.cpp \
    qmlprofilertimelinemodelfactory.cpp \
    qmlprofilertool.cpp \
    qmlprofilertracefile.cpp \
    qmlprofilertraceview.cpp \
    qmlprofilertreeview.cpp \
    qmlprofilerviewmanager.cpp

HEADERS += \
    localqmlprofilerrunner.h \
    qmlprofiler_global.h \
    qmlprofileranimationsmodel.h \
    qmlprofilerattachdialog.h \
    qmlprofilerbasemodel.h \
    qmlprofilerbasemodel_p.h \
    qmlprofilerbindingloopsrenderpass.h \
    qmlprofilerclientmanager.h \
    qmlprofilerconstants.h \
    qmlprofilerdatamodel.h \
    qmlprofilerdetailsrewriter.h \
    qmlprofilerengine.h \
    qmlprofilereventsmodelproxy.h \
    qmlprofilereventview.h \
    qmlprofilermodelmanager.h \
    qmlprofilernotesmodel.h \
    qmlprofilerplugin.h \
    qmlprofilerrangemodel.h \
    qmlprofilerruncontrolfactory.h \
    qmlprofilerstatemanager.h \
    qmlprofilerstatewidget.h \
    qmlprofilertimelinemodel.h \
    qmlprofilertimelinemodelfactory.h \
    qmlprofilertool.h \
    qmlprofilertracefile.h \
    qmlprofilertraceview.h \
    qmlprofilertreeview.h \
    qmlprofilerviewmanager.h

RESOURCES += \
    qml/qmlprofiler.qrc

DISTFILES += \
    qml/bindingloops.frag \
    qml/bindingloops.vert
