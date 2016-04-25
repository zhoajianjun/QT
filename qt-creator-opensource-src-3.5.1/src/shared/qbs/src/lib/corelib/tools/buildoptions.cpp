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
#include "buildoptions.h"

#include <QSharedData>
#include <QThread>

namespace qbs {
namespace Internal {

class BuildOptionsPrivate : public QSharedData
{
public:
    BuildOptionsPrivate()
        : maxJobCount(0), dryRun(false), keepGoing(false), forceTimestampCheck(false),
          logElapsedTime(false), echoMode(defaultCommandEchoMode()), install(true),
          removeExistingInstallation(false)
    {
    }

    QStringList changedFiles;
    QStringList filesToConsider;
    QStringList activeFileTags;
    int maxJobCount;
    bool dryRun;
    bool keepGoing;
    bool forceTimestampCheck;
    bool logElapsedTime;
    CommandEchoMode echoMode;
    bool install;
    bool removeExistingInstallation;
};

} // namespace Internal

/*!
 * \class BuildOptions
 * \brief The \c BuildOptions class comprises parameters that influence the behavior of
 * build and clean operations.
 */

/*!
 * \brief Creates a \c BuildOptions object and initializes its members to sensible default values.
 */
BuildOptions::BuildOptions() : d(new Internal::BuildOptionsPrivate)
{
}

BuildOptions::BuildOptions(const BuildOptions &other) : d(other.d)
{
}

BuildOptions &BuildOptions::operator=(const BuildOptions &other)
{
    d = other.d;
    return *this;
}

BuildOptions::~BuildOptions()
{
}

/*!
 * \brief If non-empty, qbs pretends that only these files have changed.
 * By default, this list is empty.
 */
QStringList BuildOptions::changedFiles() const
{
    return d->changedFiles;
}

/*!
 * \brief If the given list is empty, qbs will pretend only the listed files are changed.
 * \note The list elements must be absolute file paths.
 */
void BuildOptions::setChangedFiles(const QStringList &changedFiles)
{
    d->changedFiles = changedFiles;
}

/*!
 * \brief The list of files to consider.
 * \sa setFilesToConsider.
 * By default, this list is empty.
 */
QStringList BuildOptions::filesToConsider() const
{
    return d->filesToConsider;
}

/*!
 * \brief If the given list is non-empty, qbs will run only commands whose rule has at least one
 *        of these files as an input.
 * \note The list elements must be absolute file paths.
 */
void BuildOptions::setFilesToConsider(const QStringList &files)
{
    d->filesToConsider = files;
}

/*!
 * \brief The list of active file tags.
 * \sa setActiveFileTags
 */
QStringList BuildOptions::activeFileTags() const
{
    return d->activeFileTags;
}

/*!
 * \brief Set the list of active file tags.
 * If this list is non-empty, then every transformer with non-matching output file tags is skipped.
 * E.g. call \c setFilesToConsider() with "foo.cpp" and \c setActiveFileTags() with "obj" to
 * run the compiler on foo.cpp without further processing like linking.
 * \sa activeFileTags
 */
void BuildOptions::setActiveFileTags(const QStringList &fileTags)
{
    d->activeFileTags = fileTags;
}

/*!
 * \brief Returns the default value for \c maxJobCount.
 * This value will be used when \c maxJobCount has not been set explicitly.
 */
int BuildOptions::defaultMaxJobCount()
{
    return QThread::idealThreadCount();
}

/*!
 * \brief Returns the maximum number of build commands to run concurrently.
 * If the value is not valid (i.e. <= 0), a sensible one will be derived at build time
 * from the number of available processor cores at build time.
 * The default is 0.
 * \sa BuildOptions::defaultMaxJobCount
 */
int BuildOptions::maxJobCount() const
{
    return d->maxJobCount;
}

/*!
 * \brief Controls how many build commands can be run in parallel.
 * A value <= 0 leaves the decision to qbs.
 */
void BuildOptions::setMaxJobCount(int jobCount)
{
    d->maxJobCount = jobCount;
}

/*!
 * \brief Returns true iff qbs will not actually execute any commands, but just show what
 *        would happen.
 * The default is false.
 */
bool BuildOptions::dryRun() const
{
    return d->dryRun;
}

/*!
 * \brief Controls whether qbs will actually build something.
 * If the argument is true, qbs will just emit information about what it would do. Otherwise,
 * the build is actually done.
 * \note After you build with this setting enabled, the next call to \c build() on the same
 * \c Project object will do nothing, since the internal state needs to be updated the same way
 * as if an actual build had happened. You'll need to create a new \c Project object to do
 * a real build afterwards.
 */
void BuildOptions::setDryRun(bool dryRun)
{
    d->dryRun = dryRun;
}

/*!
 * \brief Returns true iff a build will continue after an error.
 * E.g. a failed compile command will result in a warning message being printed, instead of
 * stopping the build process right away. However, there might still be fatal errors after which the
 * build process cannot continue.
 * The default is \c false.
 */
bool BuildOptions::keepGoing() const
{
    return d->keepGoing;
}

/*!
 * \brief Controls whether a qbs will try to continue building after an error has occurred.
 */
void BuildOptions::setKeepGoing(bool keepGoing)
{
    d->keepGoing = keepGoing;
}

/*!
 * \brief Returns true if qbs is to use physical timestamps instead of the timestamps stored in the
 * build graph.
 * The default is \c false.
 */
bool BuildOptions::forceTimestampCheck() const
{
    return d->forceTimestampCheck;
}

/*!
 * \brief Controls whether qbs should use physical timestamps for up-to-date checks.
 */
void BuildOptions::setForceTimestampCheck(bool enabled)
{
    d->forceTimestampCheck = enabled;
}

/*!
 * \brief Returns true iff the time the operation takes will be logged.
 * The default is \c false.
 */
bool BuildOptions::logElapsedTime() const
{
    return d->logElapsedTime;
}

/*!
 * \brief Controls whether the build time will be measured and logged.
 */
void BuildOptions::setLogElapsedTime(bool log)
{
    d->logElapsedTime = log;
}

/*!
 * \brief The kind of output that is displayed when executing commands.
 */
CommandEchoMode BuildOptions::echoMode() const
{
    return d->echoMode;
}

/*!
 * \brief Controls the kind of output that is displayed when executing commands.
 */
void BuildOptions::setEchoMode(CommandEchoMode echoMode)
{
    d->echoMode = echoMode;
}

/*!
 * \brief Returns true iff installation should happen as part of the build.
 * The default is \c true.
 */
bool BuildOptions::install() const
{
    return d->install;
}

/*!
 * \brief Controls whether to install artifacts as part of the build process.
 */
void BuildOptions::setInstall(bool install)
{
    d->install = install;
}

/*!
 * \brief Returns true iff an existing installation will be removed prior to building.
 * The default is false.
 */
bool BuildOptions::removeExistingInstallation() const
{
    return d->removeExistingInstallation;
}

/*!
 * Controls whether to remove an existing installation before installing.
 * \note qbs may do some safety checks and refuse to remove certain directories such as
 *       a user's home directory. You should still be careful with this option, since it
 *       deletes recursively.
 */
void BuildOptions::setRemoveExistingInstallation(bool removeExisting)
{
    d->removeExistingInstallation = removeExisting;
}


bool operator==(const BuildOptions &bo1, const BuildOptions &bo2)
{
    return bo1.changedFiles() == bo2.changedFiles()
            && bo1.dryRun() == bo2.dryRun()
            && bo1.keepGoing() == bo2.keepGoing()
            && bo1.logElapsedTime() == bo2.logElapsedTime()
            && bo1.echoMode() == bo2.echoMode()
            && bo1.maxJobCount() == bo2.maxJobCount()
            && bo1.install() == bo2.install()
            && bo1.removeExistingInstallation() == bo2.removeExistingInstallation();
}

} // namespace qbs
