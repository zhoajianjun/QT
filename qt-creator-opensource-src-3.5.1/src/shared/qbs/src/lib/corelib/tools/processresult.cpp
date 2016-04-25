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
#include "processresult.h"
#include "processresult_p.h"

/*!
 * \class SetupProjectParameters
 * \brief The \c ProcessResult class describes a finished qbs process command.
 */

namespace qbs {

ProcessResult::ProcessResult() : d(new Internal::ProcessResultPrivate)
{
}

ProcessResult::ProcessResult(const ProcessResult &other) : d(other.d)
{
}

ProcessResult &ProcessResult::operator=(const ProcessResult &other)
{
    d = other.d;
    return *this;
}

ProcessResult::~ProcessResult()
{
}

/*!
 * \brief Returns true iff the command finished successfully.
 */
bool ProcessResult::success() const
{
    return d->success;
}

/*!
 * \brief Returns the file path of the executable that was run.
 */
QString ProcessResult::executableFilePath() const
{
    return d->executableFilePath;
}

/*!
 * \brief Returns the command-line arguments with which the command was invoked.
 */
QStringList ProcessResult::arguments() const
{
    return d->arguments;
}

/*!
 * \brief Returns the working directory of the invoked command.
 */
QString ProcessResult::workingDirectory() const
{
    return d->workingDirectory;
}

/*!
 * \brief Returns the exit status of the command.
 */
QProcess::ExitStatus ProcessResult::exitStatus() const
{
    return d->exitStatus;
}

/*!
 * \brief Returns the exit code of the command.
 */
int ProcessResult::exitCode() const
{
    return d->exitCode;
}

/*!
 * \brief Returns the data the command wrote to the standard output channel.
 */
QStringList ProcessResult::stdOut() const
{
    return d->stdOut;
}

/*!
 * \brief Returns the data the command wrote to the standard error channel.
 */
QStringList ProcessResult::stdErr() const
{
    return d->stdErr;
}

} // namespace qbs
