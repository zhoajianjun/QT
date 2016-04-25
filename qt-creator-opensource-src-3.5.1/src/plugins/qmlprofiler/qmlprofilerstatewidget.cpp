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

#include "qmlprofilerstatewidget.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTime>
#include <QDebug>

namespace QmlProfiler {
namespace Internal {

class QmlProfilerStateWidget::QmlProfilerStateWidgetPrivate
{
    public:
    QmlProfilerStateWidgetPrivate(QmlProfilerStateWidget *qq) { Q_UNUSED(qq); }

    QLabel *text;
    QProgressBar *progressBar;
    QPixmap shadowPic;

    QmlProfilerStateManager *m_profilerState;
    QmlProfilerModelManager *m_modelManager;

    bool isRecording;
    bool appKilled;
    bool emptyList;
    bool traceAvailable;
    bool loadingDone;
    QTime profilingTimer;
    qint64 estimatedProfilingTime;
};

QmlProfilerStateWidget::QmlProfilerStateWidget(QmlProfilerStateManager *stateManager,
                                QmlProfilerModelManager *modelManager, QWidget *parent)
    : QWidget(parent), d(new QmlProfilerStateWidgetPrivate(this))
{
    setObjectName(QLatin1String("QML Profiler State Display"));

    // UI elements
    QVBoxLayout *layout = new QVBoxLayout(this);
    resize(200,70);

    d->shadowPic.load(QLatin1String(":/timeline/dialog_shadow.png"));

    d->text = new QLabel(this);
    d->text->setAlignment(Qt::AlignCenter);
    layout->addWidget(d->text);

    d->progressBar = new QProgressBar(this);
    layout->addWidget(d->progressBar);
    d->progressBar->setMaximum(1000);
    d->progressBar->setVisible(false);

    setLayout(layout);

    // internal state
    d->isRecording = false;
    d->appKilled = false;
    d->traceAvailable = false;
    d->loadingDone = true;
    d->emptyList = true;

    // profiler state
    d->m_modelManager = modelManager;
    connect(d->m_modelManager,SIGNAL(stateChanged()), this, SLOT(dataStateChanged()));
    connect(d->m_modelManager,SIGNAL(progressChanged()), this, SLOT(dataStateChanged()));
    connect(this, SIGNAL(newTimeEstimation(qint64)), d->m_modelManager, SLOT(newTimeEstimation(qint64)));
    d->m_profilerState = stateManager;
    connect(d->m_profilerState,SIGNAL(stateChanged()), this, SLOT(profilerStateChanged()));
    connect(d->m_profilerState, SIGNAL(serverRecordingChanged()),
            this, SLOT(profilerStateChanged()));

    updateDisplay();
}

QmlProfilerStateWidget::~QmlProfilerStateWidget()
{
    delete d;
}

void QmlProfilerStateWidget::reposition()
{
    QWidget *parentWidget = qobject_cast<QWidget *>(parent());
    // positioning it at 2/3 height (it looks better)
    move(parentWidget->width()/2 - width()/2, parentWidget->height()/3 - height()/2);
}

void QmlProfilerStateWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.save();

    // Shadow
    // there is no actual qpainter borderimage, hacking it here
    int borderWidth = 4;

    // topleft
    painter.drawPixmap(QRect(0, 0, borderWidth, borderWidth),
                      d->shadowPic,
                      QRect(0, 0, borderWidth, borderWidth));
    // topright
    painter.drawPixmap(QRect(width()-borderWidth, 0, borderWidth, borderWidth),
                      d->shadowPic,
                      QRect(d->shadowPic.width()-borderWidth, 0, borderWidth, borderWidth));
    // bottomleft
    painter.drawPixmap(QRect(0, height()-borderWidth, borderWidth, borderWidth),
                      d->shadowPic,
                      QRect(0, d->shadowPic.height()-borderWidth, borderWidth, borderWidth));
    // bottomright
    painter.drawPixmap(QRect(width()-borderWidth, height()-borderWidth, borderWidth, borderWidth),
                      d->shadowPic,
                      QRect(d->shadowPic.width()-borderWidth,
                            d->shadowPic.height()-borderWidth,
                            borderWidth,
                            borderWidth));
    // top
    painter.drawPixmap(QRect(borderWidth, 0, width()-2*borderWidth, borderWidth),
                      d->shadowPic,
                      QRect(borderWidth, 0, d->shadowPic.width()-2*borderWidth, borderWidth));
    // bottom
    painter.drawPixmap(QRect(borderWidth, height()-borderWidth, width()-2*borderWidth, borderWidth),
                      d->shadowPic,
                      QRect(borderWidth,
                            d->shadowPic.height()-borderWidth,
                            d->shadowPic.width()-2*borderWidth,
                            borderWidth));
    // left
    painter.drawPixmap(QRect(0, borderWidth, borderWidth, height()-2*borderWidth),
                      d->shadowPic,
                      QRect(0, borderWidth, borderWidth, d->shadowPic.height()-2*borderWidth));
    // right
    painter.drawPixmap(QRect(width()-borderWidth, borderWidth, borderWidth, height()-2*borderWidth),
                      d->shadowPic,
                      QRect(d->shadowPic.width()-borderWidth,
                            borderWidth,
                            borderWidth,
                            d->shadowPic.height()-2*borderWidth));
    // center
    painter.drawPixmap(QRect(borderWidth, borderWidth, width()-2*borderWidth, height()-2*borderWidth),
                      d->shadowPic,
                      QRect(borderWidth,
                            borderWidth,
                            d->shadowPic.width()-2*borderWidth,
                            d->shadowPic.height()-2*borderWidth));


    // Background
    painter.setBrush(QColor("#E0E0E0"));
    painter.setPen(QColor("#666666"));
    painter.drawRoundedRect(QRect(borderWidth, 0, width()-2*borderWidth, height()-borderWidth), 6, 6);

    // restore painter
    painter.restore();

}

void QmlProfilerStateWidget::showText(const QString &text, bool showProgress)
{
    setVisible(true);
    if (showProgress) {
        if (d->isRecording) {
            d->isRecording = false;
            d->estimatedProfilingTime = d->profilingTimer.elapsed();
            emit newTimeEstimation(d->estimatedProfilingTime);
        }
        d->progressBar->setValue(d->m_modelManager->progress() * 1000);
    }
    d->progressBar->setVisible(showProgress);
    d->text->setText(text);
    resize(300, 70);
    reposition();
}

void QmlProfilerStateWidget::updateDisplay()
{
    // When datamodel is acquiring data
    if (!d->loadingDone && !d->emptyList && !d->appKilled) {
        showText(tr("Loading data"), true);
        return;
    }

    // When application is being profiled
    if (d->isRecording) {
        showText(tr("Profiling application"));
        return;
    }

    // After profiling, there is an empty trace
    if (d->traceAvailable && d->loadingDone && d->emptyList) {
        showText(tr("No QML events recorded"));
        return;
    }

    // Application died before all data could be read
    if (!d->loadingDone && !d->emptyList && d->appKilled) {
        showText(tr("Application stopped before loading all data"), true);
        return;
    }

    // There is a trace on view, hide this dialog
    d->progressBar->setVisible(false);
    setVisible(false);
}

void QmlProfilerStateWidget::dataStateChanged()
{
    // consider possible rounding errors
    d->loadingDone = d->m_modelManager->state() == QmlProfilerDataState::Done ||
            d->m_modelManager->state() == QmlProfilerDataState::Empty;
    d->traceAvailable = d->m_modelManager->traceTime()->duration() > 0;
    d->emptyList = d->m_modelManager->isEmpty() || d->m_modelManager->progress() == 0;
    updateDisplay();
}

void QmlProfilerStateWidget::profilerStateChanged()
{
    if (d->m_profilerState->currentState() == QmlProfilerStateManager::AppKilled)
        d->appKilled = true;
    else
        if (d->m_profilerState->currentState() == QmlProfilerStateManager::AppStarting)
            d->appKilled = false;

    if (d->m_profilerState->serverRecording()) {
        d->profilingTimer.start();
        d->isRecording = true;
    } else if (d->isRecording) {
        // estimated time in ns
        d->estimatedProfilingTime = d->profilingTimer.elapsed() * 1e6;
        emit newTimeEstimation(d->estimatedProfilingTime);
        d->isRecording = false;
    }
    updateDisplay();
}

}
}
