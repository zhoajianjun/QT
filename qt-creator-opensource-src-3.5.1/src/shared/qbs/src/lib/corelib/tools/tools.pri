include(../../../install_prefix.pri)

INCLUDEPATH += $$PWD/../.. # for plugins

HEADERS += \
    $$PWD/architectures.h \
    $$PWD/buildgraphlocker.h \
    $$PWD/codelocation.h \
    $$PWD/commandechomode.h \
    $$PWD/error.h \
    $$PWD/executablefinder.h \
    $$PWD/fileinfo.h \
    $$PWD/filetime.h \
    $$PWD/generateoptions.h \
    $$PWD/id.h \
    $$PWD/persistence.h \
    $$PWD/scannerpluginmanager.h \
    $$PWD/scripttools.h \
    $$PWD/settings.h \
    $$PWD/settingsmodel.h \
    $$PWD/preferences.h \
    $$PWD/profile.h \
    $$PWD/processresult.h \
    $$PWD/processresult_p.h \
    $$PWD/processutils.h \
    $$PWD/progressobserver.h \
    $$PWD/projectgeneratormanager.h \
    $$PWD/propertyfinder.h \
    $$PWD/shellutils.h \
    $$PWD/hostosinfo.h \
    $$PWD/buildoptions.h \
    $$PWD/installoptions.h \
    $$PWD/cleanoptions.h \
    $$PWD/setupprojectparameters.h \
    $$PWD/persistentobject.h \
    $$PWD/weakpointer.h \
    $$PWD/qbs_export.h \
    $$PWD/qbsassert.h \
    $$PWD/qttools.h \
    $$PWD/version.h

SOURCES += \
    $$PWD/architectures.cpp \
    $$PWD/buildgraphlocker.cpp \
    $$PWD/codelocation.cpp \
    $$PWD/commandechomode.cpp \
    $$PWD/error.cpp \
    $$PWD/executablefinder.cpp \
    $$PWD/fileinfo.cpp \
    $$PWD/generateoptions.cpp \
    $$PWD/id.cpp \
    $$PWD/persistence.cpp \
    $$PWD/scannerpluginmanager.cpp \
    $$PWD/scripttools.cpp \
    $$PWD/settings.cpp \
    $$PWD/settingsmodel.cpp \
    $$PWD/preferences.cpp \
    $$PWD/processresult.cpp \
    $$PWD/processutils.cpp \
    $$PWD/profile.cpp \
    $$PWD/progressobserver.cpp \
    $$PWD/projectgeneratormanager.cpp \
    $$PWD/propertyfinder.cpp \
    $$PWD/shellutils.cpp \
    $$PWD/buildoptions.cpp \
    $$PWD/installoptions.cpp \
    $$PWD/cleanoptions.cpp \
    $$PWD/setupprojectparameters.cpp \
    $$PWD/qbsassert.cpp \
    $$PWD/qttools.cpp \
    $$PWD/version.cpp

win32 {
    SOURCES += $$PWD/filetime_win.cpp
}

unix {
    SOURCES += $$PWD/filetime_unix.cpp
}

qbs_enable_unit_tests {
    HEADERS += $$PWD/tst_tools.h
    SOURCES += $$PWD/tst_tools.cpp
}

!qbs_no_dev_install {
    tools_headers.files = \
        $$PWD/architectures.h \
        $$PWD/cleanoptions.h \
        $$PWD/codelocation.h \
        $$PWD/commandechomode.h \
        $$PWD/error.h \
        $$PWD/settings.h \
        $$PWD/settingsmodel.h \
        $$PWD/preferences.h \
        $$PWD/profile.h \
        $$PWD/processresult.h \
        $$PWD/qbs_export.h \
        $$PWD/buildoptions.h \
        $$PWD/generateoptions.h \
        $$PWD/generatorpluginmanager.h \
        $$PWD/installoptions.h \
        $$PWD/setupprojectparameters.h
    tools_headers.path = $${QBS_INSTALL_PREFIX}/include/qbs/tools
    INSTALLS += tools_headers
}
