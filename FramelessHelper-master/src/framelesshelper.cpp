//#include "stdafx.h"

#include "framelesshelper.h"
#include "framelesshelperprivate.h"

#include <QWidget>
#include <QPushButton>
#include <QDebug>

FramelessHelper::FramelessHelper(QWidget *parent) : QObject(parent)
{
    d = new FramelessHelperPrivate(parent);
}

void FramelessHelper::setResizeMargins(int margin)
{
    setResizeMargins(QMargins(margin, margin, margin, margin));
}

void FramelessHelper::setResizeMargins(const QMargins &margins)
{
    d->margins = margins;
}

void FramelessHelper::setCloseButton(QPushButton *button, bool edgeResize)
{
    d->buttonClose = button;
    connect(d->buttonClose, SIGNAL(clicked(bool)),
            d->parent, SLOT(close()));

    if(edgeResize) {
        d->addEdgeWidget(button);
    }
}

void FramelessHelper::setMaximizedButton(QPushButton *button, bool edgeResize)
{
    d->buttonMaximized = button;
    connect(d->buttonMaximized, SIGNAL(clicked(bool)),
            d->parent, SLOT(showMaximized()));

    if(edgeResize) {
        d->addEdgeWidget(button);
    }

    d->refreshMaximizedButton();
}

void FramelessHelper::setMinimizedButton(QPushButton *button, bool edgeResize)
{
    d->buttonMinimized = button;
    connect(d->buttonMinimized, SIGNAL(clicked(bool)),
            d->parent, SLOT(showMinimized()));

    if(edgeResize) {
        d->addEdgeWidget(button);
    }
}

void FramelessHelper::setRestoreButton(QPushButton *button, bool edgeResize)
{
    d->buttonRestore = button;
    connect(d->buttonRestore, SIGNAL(clicked(bool)),
            d->parent, SLOT(showNormal()));

    if(edgeResize) {
        d->addEdgeWidget(button);
    }

    d->refreshMaximizedButton();
}

void FramelessHelper::addEdgeWidget(QWidget *widget)
{
    d->addEdgeWidget(widget);
}

void FramelessHelper::addDragWidget(QWidget *widget)
{
    d->addDragWidget(widget);
}










