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

#ifndef QBS_PROCESS_H
#define QBS_PROCESS_H

#include <logging/logger.h>

#include <QObject>
#include <QProcessEnvironment>
#include <QScriptable>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QProcess;
class QTextStream;
QT_END_NAMESPACE

namespace qbs {
namespace Internal {
void initializeJsExtensionProcess(QScriptValue extensionObject);

class Process : public QObject, public QScriptable
{
    Q_OBJECT
public:
    static QScriptValue ctor(QScriptContext *context, QScriptEngine *engine);
    Process(QScriptContext *context);
    ~Process();

    Q_INVOKABLE QString getEnv(const QString &name);
    Q_INVOKABLE void setEnv(const QString &name, const QString &value);
    Q_INVOKABLE void setCodec(const QString &codec);

    Q_INVOKABLE QString workingDirectory();
    Q_INVOKABLE void setWorkingDirectory(const QString &dir);

    Q_INVOKABLE bool start(const QString &program, const QStringList &arguments);
    Q_INVOKABLE int exec(const QString &program, const QStringList &arguments,
                         bool throwOnError = false);
    Q_INVOKABLE void close();
    Q_INVOKABLE bool waitForFinished(int msecs = 30000);
    Q_INVOKABLE void terminate();
    Q_INVOKABLE void kill();

    Q_INVOKABLE QString readLine();
    Q_INVOKABLE QString readStdOut();
    Q_INVOKABLE QString readStdErr();

    Q_INVOKABLE void write(const QString &str);
    Q_INVOKABLE void writeLine(const QString &str);

    Q_INVOKABLE int exitCode() const;

private:
    Logger logger() const;
    QString findExecutable(const QString &filePath) const;

    QProcess *m_qProcess;
    QProcessEnvironment m_environment;
    QString m_workingDirectory;
    QTextStream *m_textStream;
};

} // namespace Internal
} // namespace qbs

Q_DECLARE_METATYPE(qbs::Internal::Process *)

#endif // QBS_PROCESS_H
