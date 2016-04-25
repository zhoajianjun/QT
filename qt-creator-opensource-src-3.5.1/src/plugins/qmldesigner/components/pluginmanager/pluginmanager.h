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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "pluginpath.h"

#include <QObject>
#include <QList>

QT_BEGIN_NAMESPACE
class QString;
class QAbstractItemModel;
class QDialog;
QT_END_NAMESPACE

namespace QmlDesigner {

class IPlugin;

// PluginManager: Loads the plugin libraries on demand "as lazy as
// possible", that is, directories are scanned and
// instances are created only when  instances() is called.

class PluginManager
{
    Q_DISABLE_COPY(PluginManager)

    typedef QList<PluginPath> PluginPathList;

public:
    typedef QList<IPlugin *> IPluginList;

    PluginManager();

    void setPluginPaths(const QStringList &paths);

    IPluginList instances();

    QDialog *createAboutPluginDialog(QWidget *parent);

private: // functions
    // Convenience to create a model for an "About Plugins"
    // dialog. Forces plugin initialization.
    QAbstractItemModel *createModel(QObject *parent = 0);

private: // variables
    PluginPathList m_paths;
};

} // namespace QmlDesigner
#endif // PLUGINMANAGER_H
