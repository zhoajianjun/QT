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
#ifndef QBS_COMMAND_H
#define QBS_COMMAND_H

#include "commandlineoption.h"
#include "commandtype.h"

namespace qbs {
class CommandLineOptionPool;

class Command
{
public:
    virtual ~Command();

    virtual CommandType type() const = 0;
    virtual QString shortDescription() const = 0;
    virtual QString longDescription() const = 0;
    virtual QString representation() const = 0;

    void parse(QStringList &input);
    QStringList additionalArguments() const { return m_additionalArguments; }

protected:
    Command(CommandLineOptionPool &optionPool) : m_optionPool(optionPool) {}

    const CommandLineOptionPool &optionPool() const { return m_optionPool; }
    void addAllToAdditionalArguments(QStringList &input);
    void addOneToAdditionalArguments(const QString &argument);
    QString supportedOptionsDescription() const;

private:
    QList<CommandLineOption::Type> actualSupportedOptions() const;
    void parseOptions(QStringList &input);

    virtual void parseMore(QStringList &input);
    virtual QList<CommandLineOption::Type> supportedOptions() const = 0;

    QStringList m_additionalArguments;
    const CommandLineOptionPool &m_optionPool;
};

class ResolveCommand : public Command
{
public:
    ResolveCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return ResolveCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

class GenerateCommand : public Command
{
public:
    GenerateCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return GenerateCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

class BuildCommand : public Command
{
public:
    BuildCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return BuildCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

class CleanCommand : public Command
{
public:
    CleanCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return CleanCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

class InstallCommand : public Command
{
public:
    InstallCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return InstallCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

class RunCommand : public Command
{
public:
    RunCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}
    QStringList targetParameters() const { return m_targetParameters; }

private:
    CommandType type() const { return RunCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
    void parseMore(QStringList &input);

    QStringList m_targetParameters;
};

class ShellCommand : public Command
{
public:
    ShellCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return ShellCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

// TODO: It seems wrong that a configuration has to be given here. Ideally, this command would just track *all* files regardless of conditions. Is that possible?
class StatusCommand : public Command
{
public:
    StatusCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return StatusCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

class UpdateTimestampsCommand : public Command
{
public:
    UpdateTimestampsCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const { return UpdateTimestampsCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
};

class DumpNodesTreeCommand : public Command
{
public:
    DumpNodesTreeCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}

private:
    CommandType type() const Q_DECL_OVERRIDE { return DumpNodesTreeCommandType; }
    QString shortDescription() const Q_DECL_OVERRIDE;
    QString longDescription() const Q_DECL_OVERRIDE;
    QString representation() const Q_DECL_OVERRIDE;
    QList<CommandLineOption::Type> supportedOptions() const Q_DECL_OVERRIDE;
};

class HelpCommand : public Command
{
public:
    HelpCommand(CommandLineOptionPool &optionPool) : Command(optionPool) {}
    QString commandToDescribe() const { return m_command; }

private:
    CommandType type() const { return HelpCommandType; }
    QString shortDescription() const;
    QString longDescription() const;
    QString representation() const;
    QList<CommandLineOption::Type> supportedOptions() const;
    void parseMore(QStringList &input);

    QString m_command;
};

} // namespace qbs

#endif // QBS_COMMAND_H
