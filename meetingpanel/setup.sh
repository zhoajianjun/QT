#!/bin/bash

set -x

export SHK_QMAKE_PATH=/opt/Qt5.5.0/5.5/gcc_64/bin/qmake

shk_qmake_build.sh  -s ./MeetingPanel.pro -p linux_x86_64 -R
