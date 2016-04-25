/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
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

#ifndef QMLINSPECTORAGENT_H
#define QMLINSPECTORAGENT_H

#include <QStack>
#include <QPointer>
#include <QTimer>

#include <qmldebug/baseenginedebugclient.h>

namespace Debugger {
namespace Internal {

class DebuggerEngine;
class WatchData;

//map <filename, editorRevision> -> <lineNumber, columnNumber> -> debugId
typedef
QHash<QPair<QString, int>, QHash<QPair<int, int>, QList<int> > > DebugIdHash;

class QmlInspectorAgent : public QObject
{
    Q_OBJECT
public:
    explicit QmlInspectorAgent(DebuggerEngine *engine, QObject *parent = 0);

    void fetchObject(int debugId);
    quint32 queryExpressionResult(int debugId, const QString &expression);

    void assignValue(const WatchData *data, const QString &expression, const QVariant &valueV);
    void updateWatchData(const WatchData &data);
    void watchDataSelected(quint64 id);
    bool selectObjectInTree(int debugId);

    quint32 setBindingForObject(int objectDebugId,
                                const QString &propertyName,
                                const QVariant &value,
                                bool isLiteralValue,
                                QString source,
                                int line);
    quint32 setMethodBodyForObject(int objectDebugId, const QString &methodName,
                                   const QString &methodBody);
    quint32 resetBindingForObject(int objectDebugId,
                                  const QString &propertyName);

    QmlDebug::ObjectReference objectForName(const QString &objectId) const;
    QmlDebug::ObjectReference objectForId(int objectDebugId) const;
    int objectIdForLocation(int line, int column) const;
    QHash<int, QString> rootObjectIds() const;
    DebugIdHash debugIdHash() const { return m_debugIdHash; }

    bool addObjectWatch(int objectDebugId);
    bool isObjectBeingWatched(int objectDebugId);
    bool removeObjectWatch(int objectDebugId);
    void removeAllObjectWatches();

    void setEngineClient(QmlDebug::BaseEngineDebugClient *client);
    QString displayName(int objectDebugId) const;
    int parentIdForObject(int objectDebugId);
    void reloadEngines();

public slots:
    void fetchContextObjectsForLocation(const QString &file,
                                         int lineNumber, int columnNumber);
    void queryEngineContext();

signals:
    void objectTreeUpdated();
    void objectFetched(const QmlDebug::ObjectReference &ref);
    void expressionResult(quint32 queryId, const QVariant &value);
    void propertyChanged(int debugId, const QByteArray &propertyName,
                         const QVariant &propertyValue);
    void automaticUpdateFailed();
    void jumpToObjectDefinition(const QmlDebug::FileReference &objSource, int debugId);

private slots:
    void updateState();
    void onResult(quint32 queryId, const QVariant &value, const QByteArray &type);
    void newObject(int engineId, int objectId, int parentId);
    void onValueChanged(int debugId, const QByteArray &propertyName, const QVariant &value);

private:
    void updateObjectTree(const QmlDebug::ContextReference &context);
    void verifyAndInsertObjectInTree(const QmlDebug::ObjectReference &object);
    void insertObjectInTree(const QmlDebug::ObjectReference &result);

    void buildDebugIdHashRecursive(const QmlDebug::ObjectReference &ref);
    void addWatchData(const QmlDebug::ObjectReference &obj,
                      const QByteArray &parentIname, bool append);

    enum LogDirection {
        LogSend,
        LogReceive
    };
    void log(LogDirection direction, const QString &message);

    bool isConnected() const;
    void clearObjectTree();

private:
    QPointer<DebuggerEngine> m_debuggerEngine;
    QmlDebug::BaseEngineDebugClient *m_engineClient;

    quint32 m_engineQueryId;
    quint32 m_rootContextQueryId;
    int m_objectToSelect;
    QList<quint32> m_objectTreeQueryIds;
    QStack<QmlDebug::ObjectReference> m_objectStack;
    QmlDebug::EngineReference m_engine;
    QHash<int, QByteArray> m_debugIdToIname;
    QHash<int, QmlDebug::FileReference> m_debugIdLocations;
    DebugIdHash m_debugIdHash;

    QList<int> m_objectWatches;
    QList<int> m_fetchDataIds;
    QTimer m_delayQueryTimer;
};

} // Internal
} // Debugger

#endif // QMLINSPECTORAGENT_H
