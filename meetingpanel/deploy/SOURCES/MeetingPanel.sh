#!/bin/sh

basedir=/usr/bqvision
qt5dir=${basedir}/qt/qt5.5

export LD_LIBRARY_PATH=${qt5dir}/lib
export QML_IMPORT_PATH=${qt5dir}/qml
export QML2_IMPORT_PATH=${qt5dir}/qml
export QT_QPA_PLATFORM_PLUGIN_PATH=${qt5dir}/plugins/platforms

/usr/bqvision/MeetingPanel/MeetingPanel
