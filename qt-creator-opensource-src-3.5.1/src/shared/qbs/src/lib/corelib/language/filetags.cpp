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

#include "filetags.h"
#include <QStringList>

namespace qbs {
namespace Internal {

void FileTag::clear()
{
    Id::operator=(Id());
}

QStringList FileTags::toStringList() const
{
    QStringList strlst;
    foreach (const FileTag &tag, *this)
        strlst += tag.toString();
    return strlst;
}

FileTags FileTags::fromStringList(const QStringList &strings)
{
    FileTags result;
    foreach (const QString &str, strings)
        result += FileTag(str.toLocal8Bit());
    return result;
}

/*!
 * \return \c{true} if this file tags set has file tags in common with \c{other}.
 */
bool FileTags::matches(const FileTags &other) const
{
    for (FileTags::const_iterator it = other.begin(); it != other.end(); ++it)
        if (contains(*it))
            return true;
    return false;
}

LogWriter operator <<(LogWriter w, const FileTags &tags)
{
    bool firstLoop = true;
    w.write('(');
    foreach (const FileTag &tag, tags) {
        if (firstLoop)
            firstLoop = false;
        else
            w.write(QLatin1String(", "));
        w.write(tag.toString());
    }
    w.write(')');
    return w;
}

QDataStream &operator >>(QDataStream &s, FileTags &tags)
{
    int i;
    s >> i;
    tags.clear();
    tags.reserve(i);
    QVariant v;
    while (--i >= 0) {
        s >> v;
        tags += FileTag::fromSetting(v);
    }
    return s;
}

QDataStream &operator <<(QDataStream &s, const FileTags &tags)
{
    s << tags.count();
    foreach (const FileTag &ft, tags)
        s << ft.toSetting();
    return s;
}

} // namespace Internal
} // namespace qbs
