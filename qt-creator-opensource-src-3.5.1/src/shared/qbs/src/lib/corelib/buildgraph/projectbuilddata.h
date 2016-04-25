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
#ifndef QBS_PROJECTBUILDDATA_H
#define QBS_PROJECTBUILDDATA_H

#include "forward_decls.h"
#include <language/forward_decls.h>
#include <logging/logger.h>
#include <tools/persistentobject.h>

#include <QHash>
#include <QList>
#include <QScriptValue>
#include <QSet>
#include <QString>

namespace qbs {
namespace Internal {
class ArtifactSet;
class BuildGraphNode;
class FileDependency;
class FileResourceBase;
class ScriptEngine;

class ProjectBuildData : public PersistentObject
{
public:
    ProjectBuildData(const ProjectBuildData *other = 0);
    ~ProjectBuildData();

    static QString deriveBuildGraphFilePath(const QString &buildDir, const QString &projectId);

    void insertIntoLookupTable(FileResourceBase *fileres);
    void removeFromLookupTable(FileResourceBase *fileres);

    QList<FileResourceBase *> lookupFiles(const QString &filePath) const;
    QList<FileResourceBase *> lookupFiles(const QString &dirPath, const QString &fileName) const;
    QList<FileResourceBase *> lookupFiles(const Artifact *artifact) const;
    void insertFileDependency(FileDependency *dependency);
    void removeArtifactAndExclusiveDependents(Artifact *artifact, const Logger &logger,
            bool removeFromProduct = true, ArtifactSet *removedArtifacts = 0);
    void removeArtifact(Artifact *artifact, const Logger &logger, bool removeFromDisk = true,
                        bool removeFromProduct = true);


    QSet<FileDependency *> fileDependencies;

    // do not serialize:
    RulesEvaluationContextPtr evaluationContext;
    bool isDirty;

private:
    void load(PersistentPool &pool);
    void store(PersistentPool &pool) const;

    typedef QHash<QString, QList<FileResourceBase *> > ResultsPerDirectory;
    typedef QHash<QString, ResultsPerDirectory> ArtifactLookupTable;
    ArtifactLookupTable m_artifactLookupTable;
    bool m_doCleanupInDestructor;
};


class BuildDataResolver
{
public:
    BuildDataResolver(const Logger &logger);
    void resolveBuildData(const TopLevelProjectPtr &resolvedProject,
                          const RulesEvaluationContextPtr &evalContext);
    void resolveProductBuildDataForExistingProject(const TopLevelProjectPtr &project,
            const QList<ResolvedProductPtr> &freshProducts);

private:
    void resolveProductBuildData(const ResolvedProductPtr &product);
    RulesEvaluationContextPtr evalContext() const;
    ScriptEngine *engine() const;
    QScriptValue scope() const;

    TopLevelProjectPtr m_project;
    Logger m_logger;
};

} // namespace Internal
} // namespace qbs

#endif // QBS_PROJECTBUILDDATA_H
