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

#include "qv8profilerclient.h"

namespace QmlDebug {

class QV8ProfilerClientPrivate {
public:
    QV8ProfilerClientPrivate(QV8ProfilerClient *_q)
        : q(_q)
        , recording(false)
    {
    }

    void sendRecordingStatus();

    QV8ProfilerClient *q;
    bool recording;
};

} // namespace QmlDebug

using namespace QmlDebug;

void QV8ProfilerClientPrivate::sendRecordingStatus()
{
    QByteArray ba;
    QDataStream stream(&ba, QIODevice::WriteOnly);
    QByteArray cmd("V8PROFILER");
    QByteArray option("");
    QByteArray title("");

    if (recording)
        option = "start";
    else
        option = "stop";
    stream << cmd << option << title;
    q->sendMessage(ba);
}

QV8ProfilerClient::QV8ProfilerClient(QmlDebugConnection *client)
    : QmlDebugClient(QLatin1String("V8Profiler"), client)
    , d(new QV8ProfilerClientPrivate(this))
{
}

QV8ProfilerClient::~QV8ProfilerClient()
{
    //Disable profiling if started by client
    //Profiling data will be lost!!
    if (isRecording())
        setRecording(false);
    delete d;
}

void QV8ProfilerClient::clearData()
{
    emit cleared();
}

bool QV8ProfilerClient::isEnabled() const
{
    return state() == Enabled;
}

void QV8ProfilerClient::sendRecordingStatus()
{
    d->sendRecordingStatus();
}

bool QV8ProfilerClient::isRecording() const
{
    return d->recording;
}

void QV8ProfilerClient::setRecording(bool v)
{
    if (v == d->recording)
        return;

    d->recording = v;

    if (state() == Enabled)
        sendRecordingStatus();

    emit recordingChanged(v);
}

void QV8ProfilerClient::setRecordingFromServer(bool v)
{
    if (v == d->recording)
        return;

    d->recording = v;

    emit recordingChanged(v);
}

void QV8ProfilerClient::stateChanged(State /*status*/)
{
    emit enabledChanged();
}

void QV8ProfilerClient::messageReceived(const QByteArray &data)
{
    QByteArray rwData = data;
    QDataStream stream(&rwData, QIODevice::ReadOnly);

    int messageType;

    stream >> messageType;

    if (messageType == V8Complete) {
        setRecordingFromServer(false);
        emit complete();
    } else if (messageType == V8ProfilingStarted) {
        setRecordingFromServer(true);
    } else if (messageType == V8Entry) {
        QString filename;
        QString function;
        int lineNumber;
        double totalTime;
        double selfTime;
        int depth;

        stream  >> filename >> function >> lineNumber >> totalTime >> selfTime >> depth;
        emit this->v8range(depth, function, filename, lineNumber, totalTime, selfTime);
    }
}

