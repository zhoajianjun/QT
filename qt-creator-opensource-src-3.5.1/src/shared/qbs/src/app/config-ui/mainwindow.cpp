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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <tools/settingsmodel.h>

#include <QAction>
#include <QKeyEvent>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QModelIndex>
#include <QPoint>
#include <QString>

MainWindow::MainWindow(const QString &settingsDir, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new qbs::SettingsModel(settingsDir, this);
    ui->treeView->setModel(m_model);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(expanded(QModelIndex)), SLOT(adjustColumns()));
    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(provideContextMenu(QPoint)));
    adjustColumns();

    QMenu * const fileMenu = menuBar()->addMenu(tr("&File"));
    QMenu * const viewMenu = menuBar()->addMenu(tr("&View"));

    QAction * const reloadAction = new QAction(tr("&Reload"), this);
    reloadAction->setShortcut(QKeySequence::Refresh);
    connect(reloadAction, SIGNAL(triggered()), SLOT(reloadSettings()));
    QAction * const saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered()), SLOT(saveSettings()));
    QAction * const expandAllAction = new QAction(tr("&Expand All"), this);
    expandAllAction->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(expandAllAction, SIGNAL(triggered()), SLOT(expandAll()));
    QAction * const collapseAllAction = new QAction(tr("C&ollapse All"), this);
    collapseAllAction->setShortcut(Qt::CTRL | Qt::Key_O);
    connect(collapseAllAction, SIGNAL(triggered()), SLOT(collapseAll()));
    QAction * const exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setMenuRole(QAction::QuitRole);
    connect(exitAction, SIGNAL(triggered()), SLOT(exit()));

    fileMenu->addAction(reloadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    viewMenu->addAction(expandAllAction);
    viewMenu->addAction(collapseAllAction);

    ui->treeView->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::adjustColumns()
{
    for (int column = 0; column < m_model->columnCount(); ++column)
        ui->treeView->resizeColumnToContents(column);
}

void MainWindow::expandAll()
{
    ui->treeView->expandAll();
    adjustColumns();
}

void MainWindow::collapseAll()
{
    ui->treeView->collapseAll();
    adjustColumns();
}

void MainWindow::reloadSettings()
{
    if (m_model->hasUnsavedChanges()) {
        const QMessageBox::StandardButton answer = QMessageBox::question(this,
                tr("Unsaved Changes"),
                tr("You have unsaved changes. Do you want to discard them?"));
        if (answer != QMessageBox::Yes)
            return;
    }
    m_model->reload();
}

void MainWindow::saveSettings()
{
    m_model->save();
}

void MainWindow::exit()
{
    if (m_model->hasUnsavedChanges()) {
        const QMessageBox::StandardButton answer = QMessageBox::question(this,
                tr("Unsaved Changes"),
                tr("You have unsaved changes. Do you want to save them now?"));
        if (answer == QMessageBox::Yes)
            m_model->save();
    }
    qApp->quit();
}

void MainWindow::provideContextMenu(const QPoint &pos)
{
    const QModelIndex index = ui->treeView->indexAt(pos);
    if (index.isValid() && index.column() != m_model->keyColumn())
        return;
    const QString settingsKey = m_model->data(index).toString();

    QMenu contextMenu;
    QAction addKeyAction(this);
    QAction removeKeyAction(this);
    if (index.isValid()) {
        addKeyAction.setText(tr("Add new key below '%1'").arg(settingsKey));
        removeKeyAction.setText(tr("Remove key '%1' and all its sub-keys").arg(settingsKey));
        contextMenu.addAction(&addKeyAction);
        contextMenu.addAction(&removeKeyAction);
    } else {
        addKeyAction.setText(tr("Add new top-level key"));
        contextMenu.addAction(&addKeyAction);
    }

    const QAction *action = contextMenu.exec(ui->treeView->mapToGlobal(pos));
    if (action == &addKeyAction)
        m_model->addNewKey(index);
    else if (action == &removeKeyAction)
        m_model->removeKey(index);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (ui->treeView->hasFocus() && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->matches(QKeySequence::Delete)) {
            const QModelIndexList indexes = ui->treeView->selectionModel()->selectedRows();
            if (indexes.count() == 1) {
                const QModelIndex index = indexes.first();
                if (index.isValid()) {
                    m_model->removeKey(index);
                    return true;
                }
            }
        }
    }

    return QMainWindow::eventFilter(watched, event);
}
