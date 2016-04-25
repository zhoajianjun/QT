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

#include "invalidargumentexception.h"
#include <QString>
#include <QCoreApplication>
/*!
\class QmlDesigner::InvalidArgumentException
\ingroup CoreExceptions
\brief The InvalidArgumentException class provides an exception for an invalid
argument.

*/
namespace QmlDesigner {

/*!
    Constructs the exception for \a argument. \a line uses the __LINE__ macro,
    \a function uses the __FUNCTION__ or the Q_FUNC_INFO macro, and \a file uses
    the __FILE__ macro.
*/
InvalidArgumentException::InvalidArgumentException(int line,
                                                   const QString &function,
                                                   const QString &file,
                                                   const QString &argument)
 : Exception(line, function, file), m_argument(argument)
{
    createWarning();
}

QString InvalidArgumentException::description() const
{
    if (function() == "createNode")
        return QCoreApplication::translate("QmlDesigner::InvalidArgumentException", "Failed to create item of type %1").arg(m_argument);

    return Exception::description();
}

/*!
    Returns the type of the exception as a string.
*/
QString InvalidArgumentException::type() const
{
    return "InvalidArgumentException";
}

/*!
    Returns the argument of the exception as a string.
*/
QString InvalidArgumentException::argument() const
{
    return m_argument;
}

}
