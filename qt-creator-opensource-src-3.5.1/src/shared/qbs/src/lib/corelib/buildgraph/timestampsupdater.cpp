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
#include "timestampsupdater.h"

#include "artifact.h"
#include "artifactvisitor.h"
#include "productbuilddata.h"
#include "projectbuilddata.h"

#include <language/language.h>
#include <tools/fileinfo.h>
#include <tools/filetime.h>
#include <tools/qbsassert.h>

#include <QFile>

namespace qbs {
namespace Internal {

class TimestampsUpdateVisitor : public ArtifactVisitor
{
public:
    TimestampsUpdateVisitor()
        : ArtifactVisitor(Artifact::Generated), m_now(FileTime::currentTime()) {}

    void visitProduct(const ResolvedProductConstPtr &product)
    {
        QBS_CHECK(product->buildData);
        ArtifactVisitor::visitProduct(product);

        // For target artifacts, we have to update the on-disk timestamp, because
        // the executor will look at it.
        foreach (Artifact * const targetArtifact, product->targetArtifacts()) {
            if (FileInfo(targetArtifact->filePath()).exists())
                QFile(targetArtifact->filePath()).open(QIODevice::WriteOnly | QIODevice::Append);
        }
    }

private:
    void doVisit(Artifact *artifact)
    {
        if (FileInfo(artifact->filePath()).exists())
            artifact->setTimestamp(m_now);
    }

    FileTime m_now;
};

void TimestampsUpdater::updateTimestamps(const TopLevelProjectPtr &project,
        const QList<ResolvedProductPtr> &products, const Logger &logger)
{
    TimestampsUpdateVisitor v;
    foreach (const ResolvedProductPtr &product, products)
        v.visitProduct(product);
    project->buildData->isDirty = !products.isEmpty();
    project->store(logger);
}

} // namespace Internal
} // namespace qbs
