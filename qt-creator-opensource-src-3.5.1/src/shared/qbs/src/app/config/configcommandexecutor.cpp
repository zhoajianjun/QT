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
#include "configcommandexecutor.h"

#include "configcommand.h"
#include "../shared/logging/consolelogger.h"

#include <tools/settingsmodel.h>
#include <tools/error.h>

#include <QDir>
#include <QFile>
#include <QTextStream>

#include <cstdio>

using namespace qbs;

ConfigCommandExecutor::ConfigCommandExecutor(Settings *settings) : m_settings(settings)
{
}

void ConfigCommandExecutor::execute(const ConfigCommand &command)
{
    switch (command.command) {
    case ConfigCommand::CfgList:
        printSettings(command);
        break;
    case ConfigCommand::CfgSet:
        setValue(command.varNames.first(), command.varValue);
        break;
    case ConfigCommand::CfgUnset:
        foreach (const QString &varName, command.varNames)
            m_settings->remove(varName);
        break;
    case ConfigCommand::CfgExport:
        exportSettings(command.fileName);
        break;
    case ConfigCommand::CfgImport:
        // Display old and new settings, in case import fails or user accidentally nukes everything
        printf("old "); // Will end up as "old settings:"
        printSettings(command);
        importSettings(command.fileName);
        printf("\nnew ");
        printSettings(command);
        break;
    case ConfigCommand::CfgNone:
        qFatal("%s: Impossible command value.", Q_FUNC_INFO);
        break;
    }
}

void ConfigCommandExecutor::setValue(const QString &key, const QString &rawInput)
{
    m_settings->setValue(key, representationToSettingsValue(rawInput));
}

void ConfigCommandExecutor::printSettings(const ConfigCommand &command)
{
    if (command.varNames.isEmpty()) {
        foreach (const QString &key, m_settings->allKeys())
            printOneSetting(key);
    } else {
        foreach (const QString &parentKey, command.varNames) {
            if (m_settings->value(parentKey).isValid()) { // Key is a leaf.
                printOneSetting(parentKey);
            } else {                                     // Key is a node.
                foreach (const QString &key, m_settings->allKeysWithPrefix(parentKey))
                    printOneSetting(parentKey + QLatin1Char('.') + key);
            }
        }
    }
}

void ConfigCommandExecutor::printOneSetting(const QString &key)
{
    printf("%s: %s\n", qPrintable(key),
           qPrintable(qbs::settingsValueToRepresentation(m_settings->value(key))));
 }

void ConfigCommandExecutor::exportSettings(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::Truncate | QFile::WriteOnly | QFile::Text)) {
        throw ErrorInfo(tr("Could not open file '%1' for writing: %2")
                .arg(QDir::toNativeSeparators(filename), file.errorString()));
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    foreach (const QString &key, m_settings->allKeys())
        stream << key << ": " << qbs::settingsValueToRepresentation(m_settings->value(key)) << endl;
}

void ConfigCommandExecutor::importSettings(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw ErrorInfo(tr("Could not open file '%1' for reading: %2")
                .arg(QDir::toNativeSeparators(filename), file.errorString()));
    }
    // Remove all current settings
    foreach (const QString &key, m_settings->allKeys())
        m_settings->remove(key);

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        int colon = line.indexOf(QLatin1Char(':'));
        if (colon >= 0 && !line.startsWith(QLatin1Char('#'))) {
            const QString key = line.left(colon).trimmed();
            const QString value = line.mid(colon + 1).trimmed();
            m_settings->setValue(key, representationToSettingsValue(value));
        }
    }
}
