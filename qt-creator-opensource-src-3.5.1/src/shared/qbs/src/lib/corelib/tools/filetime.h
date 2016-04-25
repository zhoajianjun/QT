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

#ifndef QBS_FILETIME_H
#define QBS_FILETIME_H

#include <QDataStream>
#include <QDebug>

#if defined(Q_OS_UNIX)
#include <time.h>
#endif

namespace qbs {
namespace Internal {

class FileTime
{
public:
#if defined(Q_OS_UNIX)
    typedef time_t InternalType;
#elif defined(Q_OS_WIN)
    typedef quint64 InternalType;
#else
#   error unknown platform
#endif

    FileTime();
    FileTime(const InternalType &ft)
        : m_fileTime(ft)
    { }

    bool operator < (const FileTime &rhs) const;
    bool operator > (const FileTime &rhs) const;
    bool operator <= (const FileTime &rhs) const;
    bool operator >= (const FileTime &rhs) const;
    bool operator == (const FileTime &rhs) const;
    bool operator != (const FileTime &rhs) const;

    void clear();
    bool isValid() const;
    QString toString() const;

    static FileTime currentTime();
    static FileTime oldestTime();

    friend class FileInfo;
    InternalType m_fileTime;
};

inline bool FileTime::operator > (const FileTime &rhs) const
{
    return rhs < *this;
}

inline bool FileTime::operator <= (const FileTime &rhs) const
{
    return operator < (rhs) || operator == (rhs);
}

inline bool FileTime::operator >= (const FileTime &rhs) const
{
    return operator > (rhs) || operator == (rhs);
}

inline bool FileTime::operator == (const FileTime &rhs) const
{
    return m_fileTime == rhs.m_fileTime;
}

inline bool FileTime::operator != (const FileTime &rhs) const
{
    return !operator==(rhs);
}

} // namespace Internal
} // namespace qbs

QT_BEGIN_NAMESPACE

inline QDataStream& operator>>(QDataStream &stream, qbs::Internal::FileTime &ft)
{
    quint64 u;
    stream >> u;
    ft.m_fileTime = u;
    return stream;
}

inline QDataStream& operator<<(QDataStream &stream, const qbs::Internal::FileTime &ft)
{
    stream << (quint64)ft.m_fileTime;
    return stream;
}

inline QDebug operator<<(QDebug dbg, const qbs::Internal::FileTime &t)
{
    dbg.nospace() << t.toString();
    return dbg.space();
}

QT_END_NAMESPACE

#endif // QBS_FILETIME_H
