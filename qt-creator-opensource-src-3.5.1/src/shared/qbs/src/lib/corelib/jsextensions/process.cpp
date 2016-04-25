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

#include "process.h"

#include <language/scriptengine.h>
#include <logging/translator.h>
#include <tools/executablefinder.h>
#include <tools/hostosinfo.h>

#include <QProcess>
#include <QScriptEngine>
#include <QScriptValue>
#include <QTextCodec>
#include <QTextStream>

namespace qbs {
namespace Internal {

void initializeJsExtensionProcess(QScriptValue extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    QScriptValue obj = engine->newQMetaObject(&Process::staticMetaObject, engine->newFunction(&Process::ctor));
    extensionObject.setProperty(QLatin1String("Process"), obj);
}

QScriptValue Process::ctor(QScriptContext *context, QScriptEngine *engine)
{
    Process *t;
    switch (context->argumentCount()) {
    case 0:
        t = new Process(context);
        break;
    default:
        return context->throwError(QLatin1String("Process()"));
    }

    QScriptValue obj = engine->newQObject(t, QScriptEngine::ScriptOwnership);

    // Get environment
    QVariant v = engine->property("_qbs_procenv");
    if (v.isNull()) {
        // The build environment is not initialized yet.
        // This can happen if one uses Process on the RHS of a binding like Group.name.
        t->m_environment = static_cast<ScriptEngine *>(engine)->environment();
    } else {
        t->m_environment
            = QProcessEnvironment(*reinterpret_cast<QProcessEnvironment*>(v.value<void*>()));
    }

    return obj;
}

Process::~Process()
{
    delete m_textStream;
    delete m_qProcess;
}

Process::Process(QScriptContext *context)
{
    Q_UNUSED(context);
    Q_ASSERT(thisObject().engine() == engine());

    m_qProcess = new QProcess;
    m_textStream = new QTextStream(m_qProcess);
}

QString Process::getEnv(const QString &name)
{
    Q_ASSERT(thisObject().engine() == engine());
    return m_environment.value(name);
}

void Process::setEnv(const QString &name, const QString &value)
{
    Q_ASSERT(thisObject().engine() == engine());
    m_environment.insert(name, value);
}

QString Process::workingDirectory()
{
    Q_ASSERT(thisObject().engine() == engine());
    return m_workingDirectory;
}

void Process::setWorkingDirectory(const QString &dir)
{
    Q_ASSERT(thisObject().engine() == engine());
    m_workingDirectory = dir;
}

bool Process::start(const QString &program, const QStringList &arguments)
{
    Q_ASSERT(thisObject().engine() == engine());

    if (!m_workingDirectory.isEmpty())
        m_qProcess->setWorkingDirectory(m_workingDirectory);

    m_qProcess->setProcessEnvironment(m_environment);
    m_qProcess->start(findExecutable(program), arguments);
    return m_qProcess->waitForStarted();
}

int Process::exec(const QString &program, const QStringList &arguments, bool throwOnError)
{
    Q_ASSERT(thisObject().engine() == engine());

    if (!start(findExecutable(program), arguments)) {
        if (throwOnError) {
            context()->throwError(Tr::tr("Error running '%1': %2")
                                  .arg(program, m_qProcess->errorString()));
        }
        return -1;
    }
    m_qProcess->closeWriteChannel();
    m_qProcess->waitForFinished(-1);
    if (throwOnError) {
        if (m_qProcess->error() != QProcess::UnknownError) {
            context()->throwError(Tr::tr("Error running '%1': %2")
                                  .arg(program, m_qProcess->errorString()));
        } else if (m_qProcess->exitCode() != 0) {
            QString errorMessage = Tr::tr("Process '%1' finished with exit code %2.")
                    .arg(program).arg(m_qProcess->exitCode());
            const QString stdErr = readStdErr();
            if (!stdErr.isEmpty())
                errorMessage.append(Tr::tr(" The standard error output was:\n")).append(stdErr);
            context()->throwError(errorMessage);
        }
    }
    if (m_qProcess->error() != QProcess::UnknownError)
        return -1;
    return m_qProcess->exitCode();
}

void Process::close()
{
    Q_ASSERT(thisObject().engine() == engine());
    delete m_textStream;
    m_textStream = 0;
    delete m_qProcess;
    m_qProcess = 0;
}

bool Process::waitForFinished(int msecs)
{
    Q_ASSERT(thisObject().engine() == engine());

    if (m_qProcess->state() == QProcess::NotRunning)
        return true;
    return m_qProcess->waitForFinished(msecs);
}

void Process::terminate()
{
    m_qProcess->terminate();
}

void Process::kill()
{
    m_qProcess->kill();
}

void Process::setCodec(const QString &codec)
{
    Q_ASSERT(thisObject().engine() == engine());
    m_textStream->setCodec(qPrintable(codec));
}

QString Process::readLine()
{
    return m_textStream->readLine();
}

QString Process::readStdOut()
{
    return m_textStream->readAll();
}

QString Process::readStdErr()
{
    return m_textStream->codec()->toUnicode(m_qProcess->readAllStandardError());
}

int Process::exitCode() const
{
    return m_qProcess->exitCode();
}

Logger Process::logger() const
{
    ScriptEngine *scriptEngine = static_cast<ScriptEngine *>(engine());
    return scriptEngine->logger();
}

QString Process::findExecutable(const QString &filePath) const
{
    ExecutableFinder exeFinder(ResolvedProductPtr(), m_environment, logger());
    return exeFinder.findExecutable(filePath, m_workingDirectory);
}

void Process::write(const QString &str)
{
    (*m_textStream) << str;
}

void Process::writeLine(const QString &str)
{
    (*m_textStream) << str;
    if (HostOsInfo::isWindowsHost())
        (*m_textStream) << '\r';
    (*m_textStream) << '\n';
}

} // namespace Internal
} // namespace qbs
