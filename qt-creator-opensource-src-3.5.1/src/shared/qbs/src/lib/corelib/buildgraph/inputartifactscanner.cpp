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

#include "inputartifactscanner.h"

#include "artifact.h"
#include "buildgraph.h"
#include "productbuilddata.h"
#include "projectbuilddata.h"
#include "transformer.h"
#include "depscanner.h"
#include "rulesevaluationcontext.h"

#include <language/language.h>
#include <tools/fileinfo.h>
#include <tools/scannerpluginmanager.h>
#include <tools/qbsassert.h>
#include <tools/error.h>

#include <QDir>
#include <QSet>
#include <QStringList>
#include <QVariantMap>

namespace qbs {
namespace Internal {

InputArtifactScannerContext::InputArtifactScannerContext(ScanResultCache *scanResultCache)
    : scanResultCache(scanResultCache)
{
}

InputArtifactScannerContext::~InputArtifactScannerContext()
{
}

static void resolveWithIncludePath(const QString &includePath,
        const ScanResultCache::Dependency &dependency, const ResolvedProduct *product,
        ResolvedDependency *result)
{
    QString absDirPath = dependency.dirPath().isEmpty() ? includePath : FileInfo::resolvePath(includePath, dependency.dirPath());
    if (!dependency.isClean())
        absDirPath = QDir::cleanPath(absDirPath);

    ResolvedProject *project = product->project.data();
    FileDependency *fileDependencyArtifact = 0;
    Artifact *dependencyInProduct = 0;
    Artifact *dependencyInOtherProduct = 0;
    foreach (FileResourceBase *lookupResult, project->topLevelProject()
             ->buildData->lookupFiles(absDirPath, dependency.fileName())) {
        if ((fileDependencyArtifact = dynamic_cast<FileDependency *>(lookupResult)))
            continue;
        Artifact * const foundArtifact = dynamic_cast<Artifact *>(lookupResult);
        if (foundArtifact->product == product)
            dependencyInProduct = foundArtifact;
        else
            dependencyInOtherProduct = foundArtifact;
    }

    // prioritize found artifacts
    if ((result->file = dependencyInProduct)
        || (result->file = dependencyInOtherProduct)
        || (result->file = fileDependencyArtifact))
    {
        result->filePath = result->file->filePath();
        return;
    }

    QString absFilePath = absDirPath + QLatin1Char('/') + dependency.fileName();
    if (FileInfo::exists(absFilePath))
        result->filePath = absFilePath;
}

static void resolveAbsolutePath(const ScanResultCache::Dependency &dependency,
        const ResolvedProduct *product, ResolvedDependency *result)
{
    QString absDirPath = dependency.dirPath();
    if (!dependency.isClean())
        absDirPath = QDir::cleanPath(absDirPath);

    ResolvedProject *project = product->project.data();
    FileDependency *fileDependencyArtifact = 0;
    Artifact *dependencyInProduct = 0;
    Artifact *dependencyInOtherProduct = 0;
    foreach (FileResourceBase *lookupResult, project->topLevelProject()
             ->buildData->lookupFiles(absDirPath, dependency.fileName())) {
        if ((fileDependencyArtifact = dynamic_cast<FileDependency *>(lookupResult)))
            continue;
        Artifact * const foundArtifact = dynamic_cast<Artifact *>(lookupResult);
        if (foundArtifact->product == product)
            dependencyInProduct = foundArtifact;
        else
            dependencyInOtherProduct = foundArtifact;
    }

    // prioritize found artifacts
    if ((result->file = dependencyInProduct)
        || (result->file = dependencyInOtherProduct)
        || (result->file = fileDependencyArtifact)) {
        result->filePath = result->file->filePath();
        return;
    }

    if (FileInfo::exists(dependency.filePath()))
        result->filePath = dependency.filePath();
}

static void scanWithScannerPlugin(DependencyScanner *scanner,
                                  FileResourceBase *fileToBeScanned,
                                  ScanResultCache::Result *scanResult)
{
    QStringList dependencies = scanner->collectDependencies(fileToBeScanned);
    foreach (const QString &s, dependencies)
        scanResult->deps += ScanResultCache::Dependency(s);
    scanResult->valid = true;
}

InputArtifactScanner::InputArtifactScanner(Artifact *artifact, InputArtifactScannerContext *ctx,
                                           const Logger &logger)
    : m_artifact(artifact), m_context(ctx), m_newDependencyAdded(false), m_logger(logger)
{
}

void InputArtifactScanner::scan()
{
    if (m_artifact->inputsScanned)
        return;

    if (m_logger.traceEnabled()) {
        m_logger.qbsTrace()
                << QString::fromLocal8Bit("[DEPSCAN] inputs for %1 [%2] in product '%3'")
                   .arg(m_artifact->filePath(),
                        m_artifact->fileTags().toStringList().join(QLatin1String(", ")),
                        m_artifact->product->name);
    }

    m_artifact->inputsScanned = true;

    // clear file dependencies; they will be regenerated
    m_artifact->fileDependencies.clear();

    // Remove all connections to children that were added by the dependency scanner.
    // They will be regenerated.
    foreach (Artifact *dependency, m_artifact->childrenAddedByScanner)
        disconnect(m_artifact, dependency, m_logger);

    ArtifactSet::const_iterator it = m_artifact->transformer->inputs.begin();
    for (; it != m_artifact->transformer->inputs.end(); ++it) {
        Artifact *inputArtifact = *it;
        scanForFileDependencies(inputArtifact);
    }
}

void InputArtifactScanner::scanForFileDependencies(Artifact *inputArtifact)
{
    if (m_logger.traceEnabled()) {
        m_logger.qbsTrace()
                << QString::fromLocal8Bit("[DEPSCAN] input artifact %1 [%2]")
                   .arg(inputArtifact->filePath(),
                        inputArtifact->fileTags().toStringList().join(QLatin1String(", ")));
    }

    InputArtifactScannerContext::CacheItem &cacheItem = m_context->cache[inputArtifact->properties];
    QSet<QString> visitedFilePaths;
    QList<FileResourceBase *> filesToScan;
    filesToScan.append(inputArtifact);
    const QSet<DependencyScanner *> scanners = scannersForArtifact(inputArtifact);
    while (!filesToScan.isEmpty()) {
        FileResourceBase *fileToBeScanned = filesToScan.takeFirst();
        const QString &filePathToBeScanned = fileToBeScanned->filePath();
        if (visitedFilePaths.contains(filePathToBeScanned))
            continue;
        visitedFilePaths.insert(filePathToBeScanned);

        foreach (DependencyScanner *scanner, scanners) {
            scanForScannerFileDependencies(scanner, inputArtifact, fileToBeScanned,
                scanner->recursive() ? &filesToScan : 0, cacheItem[scanner->key()]);
        }
    }
}

QSet<DependencyScanner *> InputArtifactScanner::scannersForArtifact(const Artifact *artifact) const
{
    QSet<DependencyScanner *> scanners;
    ResolvedProduct *product = artifact->product.data();
    QHash<FileTag, InputArtifactScannerContext::DependencyScannerCacheItem> &scannerCache
            = m_context->scannersCache[product];
    foreach (const FileTag &fileTag, artifact->fileTags()) {
        InputArtifactScannerContext::DependencyScannerCacheItem &cache = scannerCache[fileTag];
        if (!cache.valid) {
            cache.valid = true;
            foreach (ScannerPlugin *scanner, ScannerPluginManager::scannersForFileTag(fileTag)) {
                PluginDependencyScanner *pluginScanner = new PluginDependencyScanner(scanner);
                cache.scanners += DependencyScannerPtr(pluginScanner);
            }
            foreach (const ResolvedScannerConstPtr &scanner, product->scanners) {
                if (scanner->inputs.contains(fileTag)) {
                    cache.scanners += DependencyScannerPtr(
                                new UserDependencyScanner(scanner, m_logger));
                    break;
                }
            }
        }
        foreach (const DependencyScannerPtr &scanner, cache.scanners) {
            scanners += scanner.data();
        }
    }
    return scanners;
}

void InputArtifactScanner::scanForScannerFileDependencies(DependencyScanner *scanner,
        Artifact *inputArtifact, FileResourceBase *fileToBeScanned,
        QList<FileResourceBase *> *filesToScan,
        InputArtifactScannerContext::ScannerResolvedDependenciesCache &cache)
{
    if (m_logger.traceEnabled()) {
        m_logger.qbsTrace() << QString::fromLocal8Bit("[DEPSCAN] file %1")
                .arg(fileToBeScanned->filePath());
    }

    const bool cacheHit = cache.valid;
    if (!cacheHit) {
        cache.valid = true;
        cache.searchPaths = scanner->collectSearchPaths(inputArtifact);
    }
    if (m_logger.traceEnabled()) {
        m_logger.qbsTrace()
                << "[DEPSCAN] include paths (cache " << (cacheHit ? "hit)" : "miss)");
        foreach (const QString &s, cache.searchPaths)
            m_logger.qbsTrace() << "    " << s;
    }

    const QString &filePathToBeScanned = fileToBeScanned->filePath();
    ScanResultCache::Result scanResult = m_context->scanResultCache->value(scanner->key(), filePathToBeScanned);
    if (!scanResult.valid) {
        try {
            scanWithScannerPlugin(scanner, fileToBeScanned, &scanResult);
        } catch (const ErrorInfo &error) {
            m_logger.printWarning(error);
            return;
        }
        m_context->scanResultCache->insert(scanner->key(), filePathToBeScanned, scanResult);
    }

    resolveScanResultDependencies(inputArtifact, scanResult, filesToScan, cache);
}

void InputArtifactScanner::resolveScanResultDependencies(const Artifact *inputArtifact,
        const ScanResultCache::Result &scanResult, QList<FileResourceBase *> *artifactsToScan,
        InputArtifactScannerContext::ScannerResolvedDependenciesCache &cache)
{
    foreach (const ScanResultCache::Dependency &dependency, scanResult.deps) {
        const QString &dependencyFilePath = dependency.filePath();
        InputArtifactScannerContext::ResolvedDependencyCacheItem &cachedResolvedDependencyItem
                = cache.resolvedDependenciesCache[dependency.dirPath()][dependency.fileName()];
        ResolvedDependency &resolvedDependency = cachedResolvedDependencyItem.resolvedDependency;
        if (cachedResolvedDependencyItem.valid) {
            if (resolvedDependency.filePath.isEmpty())
                goto unresolved;
            goto resolved;
        }
        cachedResolvedDependencyItem.valid = true;

        if (FileInfo::isAbsolute(dependencyFilePath)) {
            resolveAbsolutePath(dependency, inputArtifact->product.data(),
                                &resolvedDependency);
            goto resolved;
        }

        // try include paths
        foreach (const QString &includePath, cache.searchPaths) {
            resolveWithIncludePath(includePath, dependency, inputArtifact->product.data(),
                                   &resolvedDependency);
            if (resolvedDependency.isValid())
                goto resolved;
        }

unresolved:
        if (m_logger.traceEnabled())
            m_logger.qbsWarning() << "[DEPSCAN] unresolved dependency " << dependencyFilePath;
        continue;

resolved:
        handleDependency(resolvedDependency);
        if (artifactsToScan && resolvedDependency.file) {
            if (Artifact *artifactDependency = dynamic_cast<Artifact *>(resolvedDependency.file)) {
                // Do not scan artifacts that are being built. Otherwise we might read an incomplete
                // file or conflict with the writing process.
                if (artifactDependency->buildState != BuildGraphNode::Building)
                    artifactsToScan->append(artifactDependency);
            } else {
                // Add file dependency to the next round of scanning.
                artifactsToScan->append(resolvedDependency.file);
            }
        }
    }
}

void InputArtifactScanner::handleDependency(ResolvedDependency &dependency)
{
    const ResolvedProductPtr product = m_artifact->product;
    bool insertIntoProduct = true;
    QBS_CHECK(m_artifact->artifactType == Artifact::Generated);
    QBS_CHECK(product);

    Artifact *artifactDependency = dynamic_cast<Artifact *>(dependency.file);
    FileDependency *fileDependency
            = artifactDependency ? 0 : dynamic_cast<FileDependency *>(dependency.file);
    QBS_CHECK(!dependency.file || artifactDependency || fileDependency);

    if (!dependency.file) {
        // The dependency is an existing file but does not exist in the build graph.
        if (m_logger.traceEnabled())
            m_logger.qbsTrace() << "[DEPSCAN] add new file dependency " << dependency.filePath;

        fileDependency = new FileDependency();
        dependency.file = fileDependency;
        fileDependency->setFilePath(dependency.filePath);
        product->topLevelProject()->buildData->insertFileDependency(fileDependency);
    } else if (fileDependency) {
        // The dependency exists in the project's list of file dependencies.
        if (m_logger.traceEnabled()) {
            m_logger.qbsTrace() << "[DEPSCAN] add existing file dependency "
                                << dependency.filePath;
        }
    } else if (artifactDependency->product == product) {
        // The dependency is in our product.
        if (m_logger.traceEnabled()) {
            m_logger.qbsTrace() << "[DEPSCAN] add artifact dependency " << dependency.filePath
                                << " (from this product)";
        }
        insertIntoProduct = false;
    } else {
        // The dependency is in some other product.
        ResolvedProduct * const otherProduct = artifactDependency->product;
        if (m_logger.traceEnabled()) {
            m_logger.qbsTrace() << "[DEPSCAN] add artifact dependency " << dependency.filePath
                                << " (from product " << otherProduct->uniqueName() << ')';
        }
        insertIntoProduct = false;
    }

    if (m_artifact == dependency.file)
        return;

    if (fileDependency) {
        m_artifact->fileDependencies.insert(fileDependency);
    } else {
        if (m_artifact->children.contains(artifactDependency))
            return;
        if (insertIntoProduct && !product->buildData->nodes.contains(artifactDependency))
            insertArtifact(product, artifactDependency, m_logger);
        safeConnect(m_artifact, artifactDependency, m_logger);
        m_artifact->childrenAddedByScanner += artifactDependency;
        m_newDependencyAdded = true;
    }
}

InputArtifactScannerContext::DependencyScannerCacheItem::DependencyScannerCacheItem() : valid(false)
{
}

InputArtifactScannerContext::DependencyScannerCacheItem::~DependencyScannerCacheItem()
{
}

} // namespace Internal
} // namespace qbs
