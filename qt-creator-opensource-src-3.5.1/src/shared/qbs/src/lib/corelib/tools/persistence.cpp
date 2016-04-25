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

#include "persistence.h"

#include "fileinfo.h"
#include <logging/translator.h>
#include <tools/error.h>
#include <tools/qbsassert.h>

#include <QDir>
#include <QScopedPointer>

namespace qbs {
namespace Internal {

static const char QBS_PERSISTENCE_MAGIC[] = "QBSPERSISTENCE-80";

PersistentPool::PersistentPool(const Logger &logger) : m_logger(logger)
{
    m_stream.setVersion(QDataStream::Qt_4_8);
}

PersistentPool::~PersistentPool()
{
    closeStream();
}

void PersistentPool::load(const QString &filePath)
{
    QScopedPointer<QFile> file(new QFile(filePath));
    if (!file->exists())
        throw ErrorInfo(Tr::tr("No build graph exists yet for this configuration."));
    if (!file->open(QFile::ReadOnly)) {
        throw ErrorInfo(Tr::tr("Could not open open build graph file '%1': %2")
                    .arg(filePath, file->errorString()));
    }

    m_stream.setDevice(file.data());
    QByteArray magic;
    m_stream >> magic;
    if (magic != QBS_PERSISTENCE_MAGIC) {
        file->close();
        file->remove();
        m_stream.setDevice(0);
        throw ErrorInfo(Tr::tr("Cannot use stored build graph at '%1': Incompatible file format. "
                           "Expected magic token '%2', got '%3'.")
                    .arg(filePath, QString::fromLatin1(QBS_PERSISTENCE_MAGIC),
                         QString::fromLatin1(magic)));
    }

    m_stream >> m_headData.projectConfig;
    file.take();
    m_loadedRaw.clear();
    m_loaded.clear();
    m_storageIndices.clear();
    m_stringStorage.clear();
    m_inverseStringStorage.clear();
}

void PersistentPool::setupWriteStream(const QString &filePath)
{
    QString dirPath = FileInfo::path(filePath);
    if (!FileInfo::exists(dirPath) && !QDir().mkpath(dirPath)) {
        throw ErrorInfo(Tr::tr("Failure storing build graph: Cannot create directory '%1'.")
                        .arg(dirPath));
    }

    if (QFile::exists(filePath) && !QFile::remove(filePath)) {
        throw ErrorInfo(Tr::tr("Failure storing build graph: Cannot remove old file '%1'")
                        .arg(filePath));
    }
    QBS_CHECK(!QFile::exists(filePath));
    QScopedPointer<QFile> file(new QFile(filePath));
    if (!file->open(QFile::WriteOnly)) {
        throw ErrorInfo(Tr::tr("Failure storing build graph: "
                "Cannot open file '%1' for writing: %2").arg(filePath, file->errorString()));
    }

    m_stream.setDevice(file.take());
    m_stream << QByteArray(qstrlen(QBS_PERSISTENCE_MAGIC), 0) << m_headData.projectConfig;
    m_lastStoredObjectId = 0;
    m_lastStoredStringId = 0;
}

void PersistentPool::finalizeWriteStream()
{
    if (m_stream.status() != QDataStream::Ok)
        throw ErrorInfo(Tr::tr("Failure serializing build graph."));
    m_stream.device()->seek(0);
    m_stream << QByteArray(QBS_PERSISTENCE_MAGIC);
    if (m_stream.status() != QDataStream::Ok)
        throw ErrorInfo(Tr::tr("Failure serializing build graph."));
    QFile * const file = static_cast<QFile *>(m_stream.device());
    if (!file->flush()) {
        file->close();
        file->remove();
        throw ErrorInfo(Tr::tr("Failure serializing build graph: %1").arg(file->errorString()));
    }
}

void PersistentPool::closeStream()
{
    delete m_stream.device();
    m_stream.setDevice(0);
}

void PersistentPool::store(const PersistentObject *object)
{
    if (!object) {
        m_stream << -1;
        return;
    }
    PersistentObjectId id = m_storageIndices.value(object, -1);
    if (id < 0) {
        id = m_lastStoredObjectId++;
        m_storageIndices.insert(object, id);
        m_stream << id;
        object->store(*this);
    } else {
        m_stream << id;
    }
}

void PersistentPool::store(const QVariantMap &map)
{
    m_stream << map.count();
    for (QVariantMap::ConstIterator it = map.constBegin(); it != map.constEnd(); ++it) {
        storeString(it.key());
        store(it.value());
    }
}

QVariantMap PersistentPool::loadVariantMap()
{
    int count;
    m_stream >> count;
    QVariantMap map;
    for (int i = 0; i < count; ++i) {
        const QString key = idLoadString();
        const QVariant value = loadVariant();
        map.insert(key, value);
    }
    return map;
}

void PersistentPool::store(const QVariant &variant)
{
    const quint32 type = static_cast<quint32>(variant.type());
    m_stream << type;
    switch (type) {
    case QMetaType::QString:
        storeString(variant.toString());
        break;
    case QMetaType::QStringList:
        storeStringList(variant.toStringList());
        break;
    case QMetaType::QVariantList:
        storeContainer(variant.toList());
        break;
    case QMetaType::QVariantMap:
        store(variant.toMap());
        break;
    default:
        m_stream << variant;
    }
}

QVariant PersistentPool::loadVariant()
{
    quint32 type;
    m_stream >> type;
    QVariant value;
    switch (type) {
    case QMetaType::QString:
        value = idLoadString();
        break;
    case QMetaType::QStringList:
        value = idLoadStringList();
        break;
    case QMetaType::QVariantList: {
        QVariantList l;
        int count;
        m_stream >> count;
        for (int i = 0; i < count; ++i)
            l << loadVariant();
        value = l;
        break;
    }
    case QMetaType::QVariantMap:
        value = loadVariantMap();
        break;
    default:
        m_stream >> value;
    }
    return value;
}

void PersistentPool::clear()
{
    m_loaded.clear();
    m_storageIndices.clear();
    m_stringStorage.clear();
    m_inverseStringStorage.clear();
}

QDataStream &PersistentPool::stream()
{
    return m_stream;
}

const int StringNotFoundId = -1;
const int NullStringId = -2;

void PersistentPool::storeString(const QString &t)
{
    if (t.isNull()) {
        m_stream << NullStringId;
        return;
    }

    int id = m_inverseStringStorage.value(t, StringNotFoundId);
    if (id < 0) {
        id = m_lastStoredStringId++;
        m_inverseStringStorage.insert(t, id);
        m_stream << id << t;
    } else {
        m_stream << id;
    }
}

QString PersistentPool::loadString(int id)
{
    if (id == NullStringId)
        return QString();

    QBS_CHECK(id >= 0);

    if (id >= m_stringStorage.count()) {
        QString s;
        m_stream >> s;
        m_stringStorage.resize(id + 1);
        m_stringStorage[id] = s;
        return s;
    }

    return m_stringStorage.at(id);
}

QString PersistentPool::idLoadString()
{
    int id;
    m_stream >> id;
    return loadString(id);
}

void PersistentPool::storeStringSet(const QSet<QString> &t)
{
    m_stream << t.count();
    foreach (const QString &s, t)
        storeString(s);
}

QSet<QString> PersistentPool::idLoadStringSet()
{
    int i;
    m_stream >> i;
    QSet<QString> result;
    for (; --i >= 0;)
        result += idLoadString();
    return result;
}

void PersistentPool::storeStringList(const QStringList &t)
{
    m_stream << t.count();
    foreach (const QString &s, t)
        storeString(s);
}

QStringList PersistentPool::idLoadStringList()
{
    int i;
    m_stream >> i;
    QStringList result;
    for (; --i >= 0;)
        result += idLoadString();
    return result;
}

} // namespace Internal
} // namespace qbs
