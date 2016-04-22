#!/bin/bash

set -e

print_help()
{
    echo "Usage: $0 <topdir> <destdir> <debug|release> "
}

TopDir=$1
DestDir=$2
buildmode=$3


ProjectName=MeetingPanel
binname=${ProjectName}

mkdir -p ${DestDir}/bin/
mv ${DestDir}/../bin/linux/$binname ${DestDir}/bin/MeetingPanel
#/bin/cp -v ${DestDir}/../deploy/MeetingPanel* ${DestDir}/bin/


