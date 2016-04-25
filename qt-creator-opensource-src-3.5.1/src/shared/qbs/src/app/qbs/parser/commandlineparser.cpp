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

#include "commandlineparser.h"

#include "command.h"
#include "commandlineoption.h"
#include "commandlineoptionpool.h"
#include "commandpool.h"
#include "../qbstool.h"
#include "../../shared/logging/consolelogger.h"

#include <logging/translator.h>
#include <tools/buildoptions.h>
#include <tools/cleanoptions.h>
#include <tools/error.h>
#include <tools/generateoptions.h>
#include <tools/hostosinfo.h>
#include <tools/installoptions.h>
#include <tools/preferences.h>
#include <tools/settings.h>

#include <QCoreApplication>
#include <QDir>
#include <QMap>
#include <QPair>
#include <QTextStream>

#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

namespace qbs {
using Internal::Tr;

class CommandLineParser::CommandLineParserPrivate
{
public:
    CommandLineParserPrivate();

    void doParse();
    Command *commandFromString(const QString &commandString) const;
    QList<Command *> allCommands() const;
    QString generalHelp() const;

    void setupProjectFile();
    void setupBuildDirectory();
    void setupProgress();
    void setupLogLevel();
    void setupBuildOptions();
    bool checkForExistingBuildConfiguration(const QList<QVariantMap> &buildConfigs,
                                            const QString &buildVariant, const QString &profile);
    bool isSameProfile(const QString &profile1, const QString &profile2) const;
    bool withNonDefaultProducts() const;
    bool dryRun() const;
    QString settingsDir() const { return  optionPool.settingsDirOption()->settingsDir(); }

    CommandEchoMode echoMode() const;

    QString propertyName(const QString &aCommandLineName) const;

    QStringList commandLine;
    Command *command;
    QString projectFilePath;
    QString projectBuildDirectory;
    BuildOptions buildOptions;
    CommandLineOptionPool optionPool;
    CommandPool commandPool;
    bool showProgress;
    bool logTime;
};

CommandLineParser::CommandLineParser() : d(0)
{
}

CommandLineParser::~CommandLineParser()
{
    delete d;
}

void CommandLineParser::printHelp() const
{
    QTextStream stream(stdout);

    Q_ASSERT(d->command == d->commandPool.getCommand(HelpCommandType));
    const HelpCommand * const helpCommand = static_cast<HelpCommand *>(d->command);
    if (helpCommand->commandToDescribe().isEmpty()) {
        stream << "qbs " QBS_VERSION "\n";
        stream << d->generalHelp();
    } else {
        const Command * const commandToDescribe
                = d->commandFromString(helpCommand->commandToDescribe());
        if (commandToDescribe) {
            stream << commandToDescribe->longDescription();
        } else if (!QbsTool::tryToRunTool(helpCommand->commandToDescribe(),
                                          QStringList(QLatin1String("--help")))) {
            throw ErrorInfo(Tr::tr("No such command '%1'.\n%2")
                        .arg(helpCommand->commandToDescribe(), d->generalHelp()));
        }
    }
}

CommandType CommandLineParser::command() const
{
    return d->command->type();
}

QString CommandLineParser::projectFilePath() const
{
    return d->projectFilePath;
}

QString CommandLineParser::projectBuildDirectory() const
{
    return d->projectBuildDirectory;
}

BuildOptions CommandLineParser::buildOptions(const QString &profile) const
{
    Settings settings(settingsDir());
    Preferences preferences(&settings, profile);

    if (d->buildOptions.maxJobCount() <= 0) {
        d->buildOptions.setMaxJobCount(preferences.jobs());
    }

    if (d->buildOptions.echoMode() < 0) {
        d->buildOptions.setEchoMode(preferences.defaultEchoMode());
    }

    return d->buildOptions;
}

CleanOptions CommandLineParser::cleanOptions(const QString &profile) const
{
    Q_ASSERT(command() == CleanCommandType);
    CleanOptions options;
    options.setCleanType(d->optionPool.allArtifactsOption()->enabled()
                         ? CleanOptions::CleanupAll : CleanOptions::CleanupTemporaries);
    options.setDryRun(buildOptions(profile).dryRun());
    options.setKeepGoing(buildOptions(profile).keepGoing());
    options.setLogElapsedTime(logTime());
    return options;
}

GenerateOptions CommandLineParser::generateOptions() const
{
    Q_ASSERT(command() == GenerateCommandType);
    GenerateOptions options;
    options.setGeneratorName(d->optionPool.generatorOption()->generatorName());
    return options;
}

InstallOptions CommandLineParser::installOptions(const QString &profile) const
{
    Q_ASSERT(command() == InstallCommandType || command() == RunCommandType
             || command() == GenerateCommandType);
    InstallOptions options;
    options.setRemoveExistingInstallation(d->optionPool.removeFirstoption()->enabled());
    options.setInstallRoot(d->optionPool.installRootOption()->installRoot());
    options.setInstallIntoSysroot(d->optionPool.installRootOption()->useSysroot());
    if (!options.installRoot().isEmpty()) {
        QFileInfo fi(options.installRoot());
        if (!fi.isAbsolute())
            options.setInstallRoot(fi.absoluteFilePath());
    }
    options.setDryRun(buildOptions(profile).dryRun());
    options.setKeepGoing(buildOptions(profile).keepGoing());
    options.setLogElapsedTime(logTime());
    return options;
}

bool CommandLineParser::force() const
{
    return d->optionPool.forceOption()->enabled();
}

bool CommandLineParser::forceTimestampCheck() const
{
    return d->optionPool.forceTimestampCheckOption()->enabled();
}

bool CommandLineParser::dryRun() const
{
    return d->dryRun();
}

bool CommandLineParser::logTime() const
{
    return d->logTime;
}

bool CommandLineParser::withNonDefaultProducts() const
{
    return d->withNonDefaultProducts();
}

bool CommandLineParser::buildBeforeInstalling() const
{
    return !d->optionPool.noBuildOption()->enabled();
}

QStringList CommandLineParser::runArgs() const
{
    Q_ASSERT(d->command->type() == RunCommandType);
    return static_cast<RunCommand *>(d->command)->targetParameters();
}

QStringList CommandLineParser::products() const
{
    return d->optionPool.productsOption()->arguments();
}

bool CommandLineParser::showProgress() const
{
    return d->showProgress;
}

bool CommandLineParser::showVersion() const
{
    return d->optionPool.versionOption()->enabled();
}

QString CommandLineParser::settingsDir() const
{
    return d->settingsDir();
}

QString CommandLineParser::commandName() const
{
    return d->command->representation();
}

QString CommandLineParser::commandDescription() const
{
    return d->command->longDescription();
}

static QString getBuildVariant(const QVariantMap &buildConfig)
{
    return buildConfig.value(QLatin1String("qbs.buildVariant")).toString();
}

static QString getProfile(const QVariantMap &buildConfig)
{
    return buildConfig.value(QLatin1String("qbs.profile")).toString();
}

QList<QVariantMap> CommandLineParser::buildConfigurations() const
{
    // first: build variant, second: properties. Empty variant name used for global properties.
    typedef QPair<QString, QVariantMap> PropertyListItem;
    QList<PropertyListItem> propertiesPerBuildVariant;

    const QString buildVariantKey = QLatin1String("qbs.buildVariant");
    QString currentBuildVariant;
    QVariantMap currentProperties;
    foreach (const QString &arg, d->command->additionalArguments()) {
        const int sepPos = arg.indexOf(QLatin1Char(':'));
        if (sepPos == -1) { // New build variant found.
            propertiesPerBuildVariant << qMakePair(currentBuildVariant, currentProperties);
            currentBuildVariant = arg;
            currentProperties.clear();
            continue;
        }
        const QString property = d->propertyName(arg.left(sepPos));
        if (property.isEmpty())
            qbsWarning() << Tr::tr("Ignoring empty property.");
        else if (property == buildVariantKey)
            qbsWarning() << Tr::tr("Refusing to overwrite special property '%1'.").arg(buildVariantKey);
        else
            currentProperties.insert(property, arg.mid(sepPos + 1));
    }
    propertiesPerBuildVariant << qMakePair(currentBuildVariant, currentProperties);

    if (propertiesPerBuildVariant.count() == 1) // No build variant specified on command line.
        propertiesPerBuildVariant << PropertyListItem(QLatin1String("debug"), QVariantMap());

    const QVariantMap globalProperties = propertiesPerBuildVariant.takeFirst().second;
    QList<QVariantMap> buildConfigs;
    foreach (const PropertyListItem &item, propertiesPerBuildVariant) {
        QVariantMap properties = item.second;
        for (QVariantMap::ConstIterator globalPropIt = globalProperties.constBegin();
                 globalPropIt != globalProperties.constEnd(); ++globalPropIt) {
            if (!properties.contains(globalPropIt.key()))
                properties.insert(globalPropIt.key(), globalPropIt.value());
        }

        const QString buildVariant = item.first;
        const QString profile = getProfile(properties);
        if (d->checkForExistingBuildConfiguration(buildConfigs, buildVariant, profile)) {
            qbsWarning() << Tr::tr("Ignoring redundant request to build for variant '%1' and "
                                   "profile '%2'.").arg(buildVariant, profile);
            continue;
        }

        properties.insert(buildVariantKey, buildVariant);
        buildConfigs << properties;
    }

    return buildConfigs;
}

bool CommandLineParser::parseCommandLine(const QStringList &args)
{
    delete d;
    d = new CommandLineParserPrivate;
    d->commandLine = args;
    try {
        d->doParse();
        return true;
    } catch (const ErrorInfo &error) {
        qbsError() << error.toString();
        return false;
    }
}


CommandLineParser::CommandLineParserPrivate::CommandLineParserPrivate()
    : command(0), commandPool(optionPool), showProgress(false), logTime(false)
{
}

void CommandLineParser::CommandLineParserPrivate::doParse()
{
    if (commandLine.isEmpty()) { // No command given, use default.
        command = commandPool.getCommand(BuildCommandType);
    } else {
        command = commandFromString(commandLine.first());
        if (command) {
            commandLine.removeFirst();
        } else { // No command given.
            // As an exception to the command-based syntax, we allow -h or --help as the
            // sole contents of the command line, because people are used to this working.
            if (commandLine.count() == 1 && (commandLine.first() == QLatin1String("-h")
                                             || commandLine.first() == QLatin1String("--help"))) {
                command = commandPool.getCommand(HelpCommandType);
                commandLine.clear();
            } else {
                command = commandPool.getCommand(BuildCommandType);
            }
        }
    }
    command->parse(commandLine);

    if (command->type() == HelpCommandType)
        return;

    if (command->type() == BuildCommandType && optionPool.versionOption()->enabled())
        return;

    setupProjectFile();
    setupBuildDirectory();
    setupProgress();
    setupLogLevel();
    setupBuildOptions();
}

Command *CommandLineParser::CommandLineParserPrivate::commandFromString(const QString &commandString) const
{
    foreach (Command * const command, allCommands()) {
        if (command->representation() == commandString)
            return command;
    }
    return 0;
}

QList<Command *> CommandLineParser::CommandLineParserPrivate::allCommands() const
{
    return QList<Command *>()
            << commandPool.getCommand(GenerateCommandType)
            << commandPool.getCommand(ResolveCommandType)
            << commandPool.getCommand(BuildCommandType)
            << commandPool.getCommand(CleanCommandType)
            << commandPool.getCommand(RunCommandType)
            << commandPool.getCommand(ShellCommandType)
            << commandPool.getCommand(StatusCommandType)
            << commandPool.getCommand(UpdateTimestampsCommandType)
            << commandPool.getCommand(InstallCommandType)
            << commandPool.getCommand(DumpNodesTreeCommandType)
            << commandPool.getCommand(HelpCommandType);
}

QString CommandLineParser::CommandLineParserPrivate::generalHelp() const
{
    QString help = Tr::tr("Usage: qbs [command] [command parameters]\n");
    help += Tr::tr("Internal commands:\n");
    const int rhsIndentation = 30;

    // Sorting the commands by name is nicer for the user.
    QMap<QString, const Command *> commandMap;
    foreach (const Command * command, allCommands())
        commandMap.insert(command->representation(), command);

    foreach (const Command * command, commandMap) {
        help.append(QLatin1String("  ")).append(command->representation());
        const QString whitespace
                = QString(rhsIndentation - 2 - command->representation().count(), QLatin1Char(' '));
        help.append(whitespace).append(command->shortDescription()).append(QLatin1Char('\n'));
    }

    QStringList toolNames = QbsTool::allToolNames();
    toolNames.sort();
    if (!toolNames.isEmpty()) {
        help.append(QLatin1Char('\n')).append(Tr::tr("Auxiliary commands:\n"));
        foreach (const QString &toolName, toolNames) {
            help.append(QLatin1String("  ")).append(toolName);
            const QString whitespace = QString(rhsIndentation - 2 - toolName.count(),
                                               QLatin1Char(' '));
            QbsTool tool;
            tool.runTool(toolName, QStringList(QLatin1String("--help")));
            if (tool.exitCode() != 0)
                continue;
            const QString shortDescription
                    = tool.stdOut().left(tool.stdOut().indexOf(QLatin1Char('\n')));
            help.append(whitespace).append(shortDescription).append(QLatin1Char('\n'));
        }
    }

    return help;
}

void CommandLineParser::CommandLineParserPrivate::setupProjectFile()
{
    projectFilePath = optionPool.fileOption()->projectFilePath();
    if (projectFilePath.isEmpty()) {
        qbsDebug() << "No project file given; looking in current directory.";
        projectFilePath = QDir::currentPath();
    }

    const QFileInfo projectFileInfo(projectFilePath);
    if (!projectFileInfo.exists())
        throw ErrorInfo(Tr::tr("Project file '%1' cannot be found.").arg(projectFilePath));
    if (projectFileInfo.isRelative())
        projectFilePath = projectFileInfo.absoluteFilePath();
    if (projectFileInfo.isFile())
        return;
    if (!projectFileInfo.isDir())
        throw ErrorInfo(Tr::tr("Project file '%1' has invalid type.").arg(projectFilePath));

    const QStringList namePatterns = QStringList()
            << QLatin1String("*.qbs");

    const QStringList &actualFileNames
            = QDir(projectFilePath).entryList(namePatterns, QDir::Files);
    if (actualFileNames.isEmpty()) {
        QString error;
        if (optionPool.fileOption()->projectFilePath().isEmpty())
            error = Tr::tr("No project file given and none found in current directory.\n");
        else
            error = Tr::tr("No project file found in directory '%1'.").arg(projectFilePath);
        throw ErrorInfo(error);
    }
    if (actualFileNames.count() > 1) {
        throw ErrorInfo(Tr::tr("More than one project file found in directory '%1'.")
                .arg(projectFilePath));
    }
    projectFilePath.append(QLatin1Char('/')).append(actualFileNames.first());

    projectFilePath = QDir::current().filePath(projectFilePath);
    projectFilePath = QDir::cleanPath(projectFilePath);

    qbsDebug() << "Using project file '" << QDir::toNativeSeparators(projectFilePath) << "'.";
}

void CommandLineParser::CommandLineParserPrivate::setupBuildDirectory()
{
    projectBuildDirectory = optionPool.buildDirectoryOption()->projectBuildDirectory();
}

void CommandLineParser::CommandLineParserPrivate::setupBuildOptions()
{
    buildOptions.setDryRun(dryRun());
    QStringList changedFiles = optionPool.changedFilesOption()->arguments();
    QDir currentDir;
    for (int i = 0; i < changedFiles.count(); ++i) {
        QString &file = changedFiles[i];
        file = QDir::fromNativeSeparators(currentDir.absoluteFilePath(file));
    }
    buildOptions.setChangedFiles(changedFiles);
    buildOptions.setKeepGoing(optionPool.keepGoingOption()->enabled());
    buildOptions.setForceTimestampCheck(optionPool.forceTimestampCheckOption()->enabled());
    const JobsOption * jobsOption = optionPool.jobsOption();
    buildOptions.setMaxJobCount(jobsOption->jobCount());
    buildOptions.setLogElapsedTime(logTime);
    buildOptions.setEchoMode(echoMode());
    buildOptions.setInstall(!optionPool.noInstallOption()->enabled());
    buildOptions.setRemoveExistingInstallation(optionPool.removeFirstoption()->enabled());
}

void CommandLineParser::CommandLineParserPrivate::setupProgress()
{
    const ShowProgressOption * const option = optionPool.showProgressOption();
    showProgress = option->enabled();
#ifdef Q_OS_UNIX
    if (showProgress && !isatty(STDOUT_FILENO)) {
        showProgress = false;
        qbsWarning() << Tr::tr("Ignoring option '%1', because standard output is "
                               "not connected to a terminal.").arg(option->longRepresentation());
    }
#endif
}

void CommandLineParser::CommandLineParserPrivate::setupLogLevel()
{
    const LogLevelOption * const logLevelOption = optionPool.logLevelOption();
    const VerboseOption * const verboseOption = optionPool.verboseOption();
    const QuietOption * const quietOption = optionPool.quietOption();
    int logLevel = logLevelOption->logLevel();
    logLevel += verboseOption->count();
    logLevel -= quietOption->count();

    if (showProgress && logLevel != LoggerMinLevel) {
        const bool logLevelWasSetByUser
                = logLevelOption->logLevel() != defaultLogLevel()
                || verboseOption->count() > 0 || quietOption->count() > 0;
        if (logLevelWasSetByUser) {
            qbsInfo() << Tr::tr("Setting log level to '%1', because option '%2'"
                                " has been given.").arg(logLevelName(LoggerMinLevel),
                                optionPool.showProgressOption()->longRepresentation());
        }
        logLevel = LoggerMinLevel;
    }
    if (logLevel < LoggerMinLevel) {
        qbsWarning() << Tr::tr("Cannot decrease log level as much as specified; using '%1'.")
                .arg(logLevelName(LoggerMinLevel));
        logLevel = LoggerMinLevel;
    } else if (logLevel > LoggerMaxLevel) {
        qbsWarning() << Tr::tr("Cannot increase log level as much as specified; using '%1'.")
                .arg(logLevelName(LoggerMaxLevel));
        logLevel = LoggerMaxLevel;
    }

    logTime = optionPool.logTimeOption()->enabled();
    if (showProgress && logTime) {
        qbsWarning() << Tr::tr("Options '%1' and '%2' are incompatible. Ignoring '%2'.")
                .arg(optionPool.showProgressOption()->longRepresentation(),
                     optionPool.logTimeOption()->longRepresentation());
        logTime = false;
    }

    ConsoleLogger::instance().logSink()->setLogLevel(static_cast<LoggerLevel>(logLevel));
}

QString CommandLineParser::CommandLineParserPrivate::propertyName(const QString &aCommandLineName) const
{
    // Make fully-qualified, ie "platform" -> "qbs.platform"
    if (aCommandLineName.contains(QLatin1Char('.')))
        return aCommandLineName;
    else
        return QLatin1String("qbs.") + aCommandLineName;
}

bool CommandLineParser::CommandLineParserPrivate::checkForExistingBuildConfiguration(
        const QList<QVariantMap> &buildConfigs, const QString &buildVariant, const QString &profile)
{
    foreach (const QVariantMap &buildConfig, buildConfigs) {
        if (buildVariant == getBuildVariant(buildConfig)
            && isSameProfile(profile, getProfile(buildConfig))) {
            return true;
        }
    }
    return false;
}

bool CommandLineParser::CommandLineParserPrivate::isSameProfile(const QString &profile1,
                                                                const QString &profile2) const
{
    if (profile1 == profile2)
        return true;
    Settings settings(settingsDir());
    if (profile1.isEmpty())
        return profile2.isEmpty() || profile2 == settings.defaultProfile();
    if (profile2.isEmpty())
        return profile1 == settings.defaultProfile();
    return false;
}

bool CommandLineParser::CommandLineParserPrivate::withNonDefaultProducts() const
{
    if (command->type() == GenerateCommandType)
        return true;
    return optionPool.buildNonDefaultOption()->enabled();
}

bool CommandLineParser::CommandLineParserPrivate::dryRun() const
{
     if (command->type() == GenerateCommandType)
         return true;
     return optionPool.dryRunOption()->enabled();
}

CommandEchoMode CommandLineParser::CommandLineParserPrivate::echoMode() const
{
    if (command->type() == GenerateCommandType)
        return CommandEchoModeSilent;

    if (optionPool.commandEchoModeOption()->commandEchoMode() >= 0)
        return optionPool.commandEchoModeOption()->commandEchoMode();

    return defaultCommandEchoMode();
}

} // namespace qbs
