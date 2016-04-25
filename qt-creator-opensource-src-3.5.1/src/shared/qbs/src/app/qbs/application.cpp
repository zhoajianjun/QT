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

#include "application.h"

#include "commandlinefrontend.h"
#include "ctrlchandler.h"

namespace qbs {

Application::Application(int &argc, char **argv)
    : QCoreApplication(argc, argv), m_clFrontend(0), m_canceled(false)
{
    setApplicationName(QLatin1String("qbs"));
    setOrganizationName(QLatin1String("QtProject"));
    setOrganizationDomain(QLatin1String("qt-project.org"));
}

Application *Application::instance()
{
    return qobject_cast<Application *>(QCoreApplication::instance());
}

void Application::setCommandLineFrontend(CommandLineFrontend *clFrontend)
{
    installCtrlCHandler();
    m_clFrontend = clFrontend;
}

/**
 * Interrupt the application. This is directly called from a signal handler.
 */
void Application::userInterrupt()
{
    if (m_canceled)
        return;
    Q_ASSERT(m_clFrontend);
    m_canceled = true;
    m_clFrontend->cancel();
}

} // namespace qbs
