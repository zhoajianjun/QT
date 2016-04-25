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

#include "qmlerror.h"

#include <QtCore/qdebug.h>
#include <QtCore/qfile.h>
#include <QtCore/qstringlist.h>

namespace QbsQmlJS {

/*!
    \class QmlError
    \since 5.0
    \inmodule QtQml
    \brief The QmlError class encapsulates a QML error.

    QmlError includes a textual description of the error, as well
    as location information (the file, line, and column). The toString()
    method creates a single-line, human-readable string containing all of
    this information, for example:
    \code
    file:///home/user/test.qml:7:8: Invalid property assignment: double expected
    \endcode

    You can use qDebug() or qWarning() to output errors to the console. This method
    will attempt to open the file indicated by the error
    and include additional contextual information.
    \code
    file:///home/user/test.qml:7:8: Invalid property assignment: double expected
            y: "hello"
               ^
    \endcode

    Note that the QtQuick 1 version is named QDeclarativeError

    \sa QQuickView::errors(), QmlComponent::errors()
*/
class QmlErrorPrivate
{
public:
    QmlErrorPrivate();

    QUrl url;
    QString description;
    int line;
    int column;
};

QmlErrorPrivate::QmlErrorPrivate()
: line(-1), column(-1)
{
}

/*!
    Creates an empty error object.
*/
QmlError::QmlError()
: d(0)
{
}

/*!
    Creates a copy of \a other.
*/
QmlError::QmlError(const QmlError &other)
: d(0)
{
    *this = other;
}

/*!
    Assigns \a other to this error object.
*/
QmlError &QmlError::operator=(const QmlError &other)
{
    if (!other.d) {
        delete d;
        d = 0;
    } else {
        if (!d) d = new QmlErrorPrivate;
        d->url = other.d->url;
        d->description = other.d->description;
        d->line = other.d->line;
        d->column = other.d->column;
    }
    return *this;
}

/*!
    \internal
*/
QmlError::~QmlError()
{
    delete d; d = 0;
}

/*!
    Returns true if this error is valid, otherwise false.
*/
bool QmlError::isValid() const
{
    return d != 0;
}

/*!
    Returns the url for the file that caused this error.
*/
QUrl QmlError::url() const
{
    if (d) return d->url;
    else return QUrl();
}

/*!
    Sets the \a url for the file that caused this error.
*/
void QmlError::setUrl(const QUrl &url)
{
    if (!d) d = new QmlErrorPrivate;
    d->url = url;
}

/*!
    Returns the error description.
*/
QString QmlError::description() const
{
    if (d) return d->description;
    else return QString();
}

/*!
    Sets the error \a description.
*/
void QmlError::setDescription(const QString &description)
{
    if (!d) d = new QmlErrorPrivate;
    d->description = description;
}

/*!
    Returns the error line number.
*/
int QmlError::line() const
{
    if (d) return d->line;
    else return -1;
}

/*!
    Sets the error \a line number.
*/
void QmlError::setLine(int line)
{
    if (!d) d = new QmlErrorPrivate;
    d->line = line;
}

/*!
    Returns the error column number.
*/
int QmlError::column() const
{
    if (d) return d->column;
    else return -1;
}

/*!
    Sets the error \a column number.
*/
void QmlError::setColumn(int column)
{
    if (!d) d = new QmlErrorPrivate;
    d->column = column;
}

/*!
    Returns the error as a human readable string.
*/
QString QmlError::toString() const
{
    QString rv;
    if (url().isEmpty()) {
        rv = QLatin1String("<Unknown File>");
    } else if (line() != -1) {
        rv = url().toString() + QLatin1Char(':') + QString::number(line());
        if (column() != -1)
            rv += QLatin1Char(':') + QString::number(column());
    } else {
        rv = url().toString();
    }

    rv += QLatin1String(": ") + description();

    return rv;
}

} // namespace QbsQmlJS

QT_BEGIN_NAMESPACE

using namespace QbsQmlJS;

/*!
    \relates QmlError
    \fn QDebug operator<<(QDebug debug, const QmlError &error)

    Outputs a human readable version of \a error to \a debug.
*/

QDebug operator<<(QDebug debug, const QmlError &error)
{
    debug << qPrintable(error.toString());

    QUrl url = error.url();

    if (error.line() > 0 && url.scheme() == QLatin1String("file")) {
        QString file = url.toLocalFile();
        QFile f(file);
        if (f.open(QIODevice::ReadOnly)) {
            QByteArray data = f.readAll();
            QTextStream stream(data, QIODevice::ReadOnly);
#ifndef QT_NO_TEXTCODEC
            stream.setCodec("UTF-8");
#endif
            const QString code = stream.readAll();
            const QStringList lines = code.split(QLatin1Char('\n'));

            if (lines.count() >= error.line()) {
                const QString &line = lines.at(error.line() - 1);
                debug << "\n    " << qPrintable(line);

                if (error.column() > 0) {
                    int column = qMax(0, error.column() - 1);
                    column = qMin(column, line.length());

                    QByteArray ind;
                    ind.reserve(column);
                    for (int i = 0; i < column; ++i) {
                        const QChar ch = line.at(i);
                        if (ch.isSpace())
                            ind.append(ch.unicode());
                        else
                            ind.append(' ');
                    }
                    ind.append('^');
                    debug << "\n    " << ind.constData();
                }
            }
        }
    }
    return debug;
}

QT_END_NAMESPACE
