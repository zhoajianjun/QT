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
#ifndef QBS_INTERNALJOBS_H
#define QBS_INTERNALJOBS_H

#include <buildgraph/forward_decls.h>
#include <language/forward_decls.h>
#include <logging/logger.h>
#include <tools/buildoptions.h>
#include <tools/cleanoptions.h>
#include <tools/installoptions.h>
#include <tools/error.h>
#include <tools/setupprojectparameters.h>

#include <QList>
#include <QObject>
#include <QThread>

namespace qbs {
class ProcessResult;
class Settings;

namespace Internal {
class BuildGraphLoadResult;
class BuildGraphLocker;
class Executor;
class JobObserver;
class ScriptEngine;

class InternalJob : public QObject
{
    Q_OBJECT
    friend class JobObserver;
public:
    ~InternalJob();

    void cancel();
    ErrorInfo error() const { return m_error; }
    void setError(const ErrorInfo &error) { m_error = error; }

    Logger logger() const { return m_logger; }
    bool timed() const { return m_timed; }
    void shareObserverWith(InternalJob *otherJob);

protected:
    explicit InternalJob(const Logger &logger, QObject *parent = 0);

    JobObserver *observer() const { return m_observer; }
    void setTimed(bool timed) { m_timed = timed; }
    void storeBuildGraph(const TopLevelProjectPtr &project);

signals:
    void finished(Internal::InternalJob *job);
    void newTaskStarted(const QString &description, int totalEffort, Internal::InternalJob *job);
    void totalEffortChanged(int totalEffort, Internal::InternalJob *job);
    void taskProgress(int value, Internal::InternalJob *job);

private:
    ErrorInfo m_error;
    JobObserver *m_observer;
    bool m_ownsObserver;
    Logger m_logger;
    bool m_timed;
};


class InternalJobThreadWrapper : public InternalJob
{
    Q_OBJECT
public:
    InternalJobThreadWrapper(InternalJob *synchronousJob, QObject *parent = 0);
    ~InternalJobThreadWrapper();

    void start();
    InternalJob *synchronousJob() const { return m_job; }

signals:
    void startRequested();

private slots:
    void handleFinished();

private:
    QThread m_thread;
    InternalJob *m_job;
    bool m_running;
};

class InternalSetupProjectJob : public InternalJob
{
    Q_OBJECT
public:
    InternalSetupProjectJob(const Logger &logger);
    ~InternalSetupProjectJob();

    void init(const TopLevelProjectPtr &existingProject, const SetupProjectParameters &parameters);
    void reportError(const ErrorInfo &error);

    TopLevelProjectPtr project() const;

private slots:
    void start();

private:
    void resolveProjectFromScratch(Internal::ScriptEngine *engine);
    void resolveBuildDataFromScratch(const RulesEvaluationContextPtr &evalContext);
    BuildGraphLoadResult restoreProject(const RulesEvaluationContextPtr &evalContext);
    void execute();

    TopLevelProjectPtr m_existingProject;
    TopLevelProjectPtr m_newProject;
    SetupProjectParameters m_parameters;
};


class BuildGraphTouchingJob : public InternalJob
{
    Q_OBJECT
public:
    const QList<ResolvedProductPtr> &products() const { return m_products; }
    const TopLevelProjectPtr &project() const { return m_project; }

signals:
    void reportCommandDescription(const QString &highlight, const QString &message);
    void reportProcessResult(const qbs::ProcessResult &result);

protected:
    BuildGraphTouchingJob(const Logger &logger, QObject *parent = 0);
    ~BuildGraphTouchingJob();

    void setup(const TopLevelProjectPtr &project, const QList<ResolvedProductPtr> &products,
               bool dryRun);
    void storeBuildGraph();

private:
    TopLevelProjectPtr m_project;
    QList<ResolvedProductPtr> m_products;
    bool m_dryRun;
};


class InternalBuildJob : public BuildGraphTouchingJob
{
    Q_OBJECT
public:
    InternalBuildJob(const Logger &logger, QObject *parent = 0);

    void build(const TopLevelProjectPtr &project, const QList<ResolvedProductPtr> &products,
               const BuildOptions &buildOptions);

private slots:
    void handleFinished();
    void emitFinished();

private:
    Executor *m_executor;
};


class InternalCleanJob : public BuildGraphTouchingJob
{
    Q_OBJECT
public:
    InternalCleanJob(const Logger &logger, QObject *parent = 0);

    void init(const TopLevelProjectPtr &project, const QList<ResolvedProductPtr> &products,
            const CleanOptions &options);

private slots:
    void start();

private:
    CleanOptions m_options;
};


class InternalInstallJob : public InternalJob
{
    Q_OBJECT
public:
    InternalInstallJob(const Logger &logger);
    ~InternalInstallJob();

    void init(const TopLevelProjectPtr &project, const QList<ResolvedProductPtr> &products,
            const InstallOptions &options);

private slots:
    void start();

private:
    TopLevelProjectPtr m_project;
    QList<ResolvedProductPtr> m_products;
    InstallOptions m_options;
};

} // namespace Internal
} // namespace qbs

#endif // QBS_INTERNALJOBS_H
