/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of the Qt Build Suite.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms and
** conditions see http://www.qt.io/terms-conditions. For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "probe.h"
#include "xcodeprobe.h"

#include "../shared/logging/consolelogger.h"

#include <logging/translator.h>
#include <tools/architectures.h>
#include <tools/profile.h>
#include <tools/settings.h>

#include <QStringList>
#include <QProcess>
#include <QByteArray>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QRegExp>

using namespace qbs;
using Internal::Tr;

namespace {
static QString qsystem(const QString &exe, const QStringList &args = QStringList())
{
    QProcess p;
    p.setProcessChannelMode(QProcess::MergedChannels);
    p.start(exe, args);
    p.waitForFinished();
    return QString::fromLocal8Bit(p.readAll());
}

class XcodeProbe
{
public:
    XcodeProbe(qbs::Settings *settings, QList<qbs::Profile> &profiles)
        : settings(settings), profiles(profiles)
    { }

    static int compareVersions(const QString &v1, const QString &v2);
    bool addDeveloperPath(const QString &path);
    void detectDeveloperPaths();
    void setArch(Profile *profile, const QString &pathToGcc, const QStringList &extraFlags);
    void setupDefaultToolchains(const QString &devPath, const QString &xCodeName);
    void detectAll();
private:
    qbs::Settings *settings;
    QList<qbs::Profile> &profiles;
    QStringList developerPaths;
};

int XcodeProbe::compareVersions(const QString &v1, const QString &v2)
{
    QStringList v1L = v1.split(QLatin1Char('.'), QString::SkipEmptyParts);
    QStringList v2L = v2.split(QLatin1Char('.'), QString::SkipEmptyParts);
    int i = 0;
    while (v1L.length() > i && v2L.length() > i) {
        bool n1Ok, n2Ok;
        int n1 = v1L.value(i).toInt(&n1Ok);
        int n2 = v2L.value(i).toInt(&n2Ok);
        if (!(n1Ok && n2Ok)) {
            qbsInfo() << Tr::tr("Failed to compare version %1 and %2").arg(v1,v2);
            return 0;
        }
        if (n1 > n2)
            return -1;
        else if (n1 < n2)
            return 1;
        ++i;
    }
    if (v1L.length() > v2L.length())
        return -1;
    if (v1L.length() < v2L.length())
        return 1;
    return 0;
}

bool XcodeProbe::addDeveloperPath(const QString &path)
{
    if (path.isEmpty())
        return false;
    QFileInfo pInfo(path);
    if (!pInfo.exists() || !pInfo.isDir())
        return false;
    if (developerPaths.contains(path))
        return false;
    developerPaths.append(path);
    qbsInfo() << Tr::tr("Added developer path %1").arg(path);
    return true;
}

void XcodeProbe::detectDeveloperPaths()
{
    QProcess selectedXcode;
    QString program = QLatin1String("/usr/bin/xcode-select");
    QStringList arguments(QLatin1String("--print-path"));
    selectedXcode.start(program, arguments, QProcess::ReadOnly);
    if (!selectedXcode.waitForFinished() || selectedXcode.exitCode()) {
        qbsInfo() << Tr::tr("Could not detect selected xcode with /usr/bin/xcode-select");
    } else {
        QString path = QString::fromLocal8Bit(selectedXcode.readAllStandardOutput());
        addDeveloperPath(path);
    }
    addDeveloperPath(QLatin1String("/Applications/Xcode.app/Contents/Developer"));
}

void XcodeProbe::setArch(Profile *profile, const QString &pathToGcc, const QStringList &extraFlags)
{
    if (!extraFlags.isEmpty()) {
        profile->setValue(QLatin1String("cpp.platformCommonCompilerFlags"), extraFlags);
        profile->setValue(QLatin1String("cpp.platformLinkerFlags"), extraFlags);
    }
    // setting architecture only here, bercause the same compiler
    // can support several ones
    QStringList flags(extraFlags);
    flags << QLatin1String("-dumpmachine");
    QString compilerTriplet = qsystem(pathToGcc, flags).simplified();
    QStringList compilerTripletl = compilerTriplet.split(QLatin1Char('-'));
    if (compilerTripletl.count() < 2) {
        qbsError() << QString::fromLocal8Bit("Detected '%1', but I do not understand "
                                             "its architecture '%2'.")
                      .arg(pathToGcc, compilerTriplet);
        return;
    }

    const QString architecture = compilerTripletl.at(0);

    qbsInfo() << Tr::tr("    Toolchain %1 detected:\n"
                        "        binary: %2\n"
                        "        triplet: %3\n"
                        "        arch: %4").arg(profile->name(), pathToGcc, compilerTriplet,
                                            architecture);

    profile->setValue(QLatin1String("qbs.architecture"), canonicalArchitecture(architecture));
}

void XcodeProbe::setupDefaultToolchains(const QString &devPath, const QString &xCodeName)
{
    qbsInfo() << Tr::tr("Setting up profile '%1'.").arg(xCodeName);
    QString indent = QLatin1String("  ");

    // detect clang (default toolchain)
    QFileInfo clangFileInfo(devPath
                            + QLatin1String("/Toolchains/XcodeDefault.xctoolchain/usr/bin")
                            + QLatin1String("/clang++"));
    bool hasClang = clangFileInfo.exists();
    if (!hasClang)
        qbsInfo() << indent << Tr::tr("Default toolchain %1 not found.")
                     .arg(clangFileInfo.canonicalFilePath());

    // Platforms
    QDir platformsDir(devPath + QLatin1String("/Platforms"));
    QFileInfoList platforms = platformsDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (const QFileInfo &fInfo, platforms) {
        if (fInfo.isDir() && fInfo.suffix() == QLatin1String("platform")) {
            qbsInfo() << indent << Tr::tr("Setting up %1").arg(fInfo.fileName());
            QSettings infoSettings(fInfo.absoluteFilePath() + QLatin1String("/Info.plist")
                                   , QSettings::NativeFormat);
            if (!infoSettings.contains(QLatin1String("Name"))) {
                qbsInfo() << indent << Tr::tr("Missing platform name in Info.plist of %1")
                             .arg(fInfo.absoluteFilePath());
                continue;
            }
            QStringList targetOS;
            targetOS << QLatin1String("darwin") << QLatin1String("bsd") << QLatin1String("unix");
            QString name = infoSettings.value(QLatin1String("Name")).toString();
            if (name == QLatin1String("macosx")) {
                targetOS << QLatin1String("osx");
            } else if (name == QLatin1String("iphoneos")) {
                targetOS << QLatin1String("ios");
            } else if (name == QLatin1String("iphonesimulator")) {
                targetOS << QLatin1String("ios") << QLatin1String("ios-simulator");
            } else {
                qbsInfo() << indent << Tr::tr("Skipping unknown platform %1").arg(name);
                continue;
            }

            // prepare default platform properties
            QVariantMap defaultProp = infoSettings.value(QLatin1String("DefaultProperties"))
                    .toMap();
            QVariantMap overrideProp = infoSettings.value(QLatin1String("OverrideProperties"))
                    .toMap();
            QMapIterator<QString, QVariant> i(overrideProp);
            while (i.hasNext()) {
                i.next();
                // use unite? might lead to double insertions...
                defaultProp[i.key()] = i.value();
            }

            QString clangFullName = xCodeName + QLatin1Char('-') + name + QLatin1String("-clang");
            // detect gcc
            QFileInfo gccFileInfo(fInfo.absoluteFilePath() + QLatin1String("/Developer/usr/bin/g++"));
            QString gccFullName = xCodeName + QLatin1Char('-') + name + QLatin1String("-gcc");
            if (!gccFileInfo.exists())
                gccFileInfo = QFileInfo(devPath + QLatin1String("/usr/bin/g++"));
            bool hasGcc = gccFileInfo.exists();

            // set SDKs/sysroot
            QString sysRoot;
            {
                QString sdkName;
                if (defaultProp.contains(QLatin1String("SDKROOT")))
                    sdkName = defaultProp.value(QLatin1String("SDKROOT")).toString();
                QString sdkPath;
                QDir sdks(fInfo.absoluteFilePath() + QLatin1String("/Developer/SDKs"));
                QString maxVersion;
                foreach (const QFileInfo &sdkDirInfo, sdks.entryInfoList(QDir::Dirs
                                                                         | QDir::NoDotAndDotDot)) {
                    indent = QLatin1String("    ");
                    QSettings sdkInfo(sdkDirInfo.absoluteFilePath()
                                      + QLatin1String("/SDKSettings.plist")
                                      , QSettings::NativeFormat);
                    QString versionStr = sdkInfo.value(QLatin1String("Version")).toString();
                    QVariant currentSdkName = sdkInfo.value(QLatin1String("CanonicalName"));
                    bool isBaseSdk = sdkInfo.value((QLatin1String("isBaseSDK"))).toString()
                            .toLower() != QLatin1String("no");
                    if (!isBaseSdk) {
                        qbsInfo() << indent << Tr::tr("Skipping non base Sdk %1").arg(currentSdkName.toString());
                        continue;
                    }
                    QString safeName = currentSdkName.toString()
                            .replace(QRegExp(QLatin1String("[^-a-zA-Z0-9]")),QLatin1String("-"));
                    if (sdkName.isEmpty()) {
                        if (compareVersions(maxVersion,versionStr) > 0) {
                            maxVersion = versionStr;
                            sdkPath = sdkDirInfo.canonicalFilePath();
                        }
                    } else if (currentSdkName == sdkName) {
                        sdkPath = sdkDirInfo.canonicalFilePath();
                    }
                    if (hasClang){
                        Profile pSdk(xCodeName + QLatin1Char('-') + safeName
                                     + QLatin1String("-clang"), settings);
                        pSdk.removeProfile();
                        pSdk.setBaseProfile(clangFullName);
                        pSdk.setValue(QLatin1String("qbs.sysroot"), sdkDirInfo.canonicalFilePath());
                        pSdk.setValue(QLatin1String("cpp.xcodeSdkName"), currentSdkName.toString());
                        pSdk.setValue(QLatin1String("cpp.xcodeSdkVersion"), versionStr);
                        qbsInfo() << indent << Tr::tr("* adding profile %1").arg(pSdk.name());
                        profiles << pSdk;
                    }
                    if (hasGcc) {
                        Profile pSdk(xCodeName + QLatin1Char('-') + safeName
                                     + QLatin1String("-gcc"), settings);
                        pSdk.removeProfile();
                        pSdk.setBaseProfile(gccFullName);
                        pSdk.setValue(QLatin1String("qbs.sysroot"), sdkDirInfo.canonicalFilePath());
                        pSdk.setValue(QLatin1String("cpp.xcodeSdkName"), currentSdkName.toString());
                        pSdk.setValue(QLatin1String("cpp.xcodeSdkVersion"), versionStr);
                        qbsInfo() << indent << Tr::tr("* adding profile %1").arg(pSdk.name());
                        profiles << pSdk;
                    }
                }
                if (!sdkPath.isEmpty())
                    sysRoot = sdkPath;
                else if (!sdkName.isEmpty())
                    qbsInfo() << indent << Tr::tr("Failed to find sysroot %1").arg(sdkName);
            }
            if (hasClang) {
                Profile clangProfile(clangFullName, settings);
                clangProfile.removeProfile();
                clangProfile.setValue(QLatin1String("qbs.targetOS"), targetOS);
                clangProfile.setValue(QLatin1String("qbs.toolchain"),
                                      QStringList() << QLatin1String("clang")
                                                    << QLatin1String("llvm")
                                                    << QLatin1String("gcc"));
                QStringList extraFlags;
                if (defaultProp.contains(QLatin1String("ARCHS"))) {
                    QString arch = defaultProp.value(QLatin1String("ARCHS")).toString();
                    if (arch == QLatin1String("$(NATIVE_ARCH_32_BIT)"))
                        extraFlags << QLatin1String("-arch") << QLatin1String("i386");
                }
                if (defaultProp.contains(QLatin1String("NATIVE_ARCH"))) {
                    QString arch = defaultProp.value(QLatin1String("NATIVE_ARCH")).toString();
                    if (!arch.startsWith(QLatin1String("arm")))
                        qbsInfo() << indent << Tr::tr("Expected arm architecture, not %1").arg(arch);
                    extraFlags << QLatin1String("-arch") << arch;
                }
                if (!sysRoot.isEmpty())
                    clangProfile.setValue(QLatin1String("qbs.sysroot"), sysRoot);
                clangProfile.setValue(QLatin1String("cpp.platformPath"), fInfo.canonicalFilePath());
                clangProfile.setValue(QLatin1String("cpp.compilerName"), clangFileInfo.fileName());
                clangProfile.setValue(QLatin1String("cpp.linkerName"), QLatin1String("clang++"));
                clangProfile.setValue(QLatin1String("cpp.toolchainInstallPath"),
                                      clangFileInfo.canonicalPath());
                setArch(&clangProfile, clangFileInfo.canonicalFilePath(), extraFlags);
                qbsInfo() << indent << Tr::tr("* adding profile %1").arg(clangProfile.name());
                profiles << clangProfile;
            }
            if (hasGcc) {
                Profile gccProfile(gccFullName, settings);
                gccProfile.removeProfile();
                // use the arm-apple-darwin10-llvm-* variant if available???
                gccProfile.setValue(QLatin1String("qbs.targetOS"), targetOS);
                QStringList toolchainTypes;
                toolchainTypes << QLatin1String("gcc");
                if (gccFullName.contains(QLatin1String("llvm")))
                    toolchainTypes << QLatin1String("llvm");
                gccProfile.setValue(QLatin1String("qbs.toolchain"), toolchainTypes);
                if (!sysRoot.isEmpty())
                    gccProfile.setValue(QLatin1String("qbs.sysroot"), sysRoot);
                gccProfile.setValue(QLatin1String("cpp.platformPath"),fInfo.canonicalFilePath());
                gccProfile.setValue(QLatin1String("cpp.compilerName"), gccFileInfo.fileName());
                gccProfile.setValue(QLatin1String("cpp.linkerName"), QLatin1String("g++"));
                gccProfile.setValue(QLatin1String("cpp.toolchainInstallPath"),
                                    gccFileInfo.canonicalPath());
                setArch(&gccProfile, gccFileInfo.canonicalFilePath(), QStringList());
                qbsInfo() << indent << Tr::tr("* adding profile %1").arg(gccProfile.name());
                profiles << gccProfile;
            }
        }
        indent = QLatin1String("  ");
    }
}

void XcodeProbe::detectAll()
{
    detectDeveloperPaths();
    QString xcodeName = QLatin1String("xcode");
    for (int iXcode = 0; iXcode < developerPaths.count(); ++iXcode) {
        setupDefaultToolchains(developerPaths.value(iXcode), xcodeName);
        xcodeName = QString::fromLatin1("xcode%1").arg(iXcode + 2);
    }
}
} // end anonymous namespace

void xcodeProbe(qbs::Settings *settings, QList<qbs::Profile> &profiles)
{
    XcodeProbe probe(settings, profiles);
    probe.detectAll();
}

