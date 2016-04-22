#!/usr/bin/env bash
#
set -ex

topdir=$(dirname $(readlink -e $0))

pkg=MeetingPanel

[ ! -e ${topdir}/SOURCES/${pkg}.tar.gz ] \
    || rm -f ${topdir}/SOURCES/${pkg}.tar.gz

curl ftp://192.168.0.250/release/cv5.0/linux_x86_64/MeetingPanel-linux_x86_64-release.tar.gz -o ${topdir}/SOURCES/${pkg}.tar.gz

rpmbuild -bb ${topdir}/SPECS/meetingpanel.spec --define "%_topdir $topdir"
