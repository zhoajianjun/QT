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

#include "propertymapinternal.h"

#include <tools/persistence.h>
#include <tools/propertyfinder.h>
#include <tools/scripttools.h>

namespace qbs {
namespace Internal {

/*!
 * \class PropertyMapInternal
 * \brief The \c PropertyMapInternal class contains a set of properties and their values.
 * An instance of this class is attached to every \c ResolvedProduct.
 * \c ResolvedGroups inherit their properties from the respective \c ResolvedProduct, \c SourceArtifacts
 * inherit theirs from the respective \c ResolvedGroup. \c ResolvedGroups can override the value of an
 * inherited property, \c SourceArtifacts cannot. If a property value is overridden, a new
 * \c PropertyMapInternal object is allocated, otherwise the pointer is shared.
 * \sa ResolvedGroup
 * \sa ResolvedProduct
 * \sa SourceArtifact
 */
PropertyMapInternal::PropertyMapInternal()
{
}

PropertyMapInternal::PropertyMapInternal(const PropertyMapInternal &other)
    : PersistentObject(other), m_value(other.m_value)
{
}

QVariant PropertyMapInternal::qbsPropertyValue(const QString &key) const
{
    return PropertyFinder().propertyValue(value(), QLatin1String("qbs"), key);
}

void PropertyMapInternal::setValue(const QVariantMap &map)
{
    m_value = map;
}

static QString toJSLiteral_impl(const QVariantMap &vm, int level = 0)
{
    QString indent;
    for (int i = 0; i < level; ++i)
        indent += QLatin1String("    ");
    QString str;
    for (QVariantMap::const_iterator it = vm.begin(); it != vm.end(); ++it) {
        if (it.value().type() == QVariant::Map) {
            str += indent + it.key() + QLatin1String(": {\n");
            str += toJSLiteral_impl(it.value().toMap(), level + 1);
            str += indent + QLatin1String("}\n");
        } else {
            str += indent + it.key() + QLatin1String(": ") + toJSLiteral(it.value())
                    + QLatin1Char('\n');
        }
    }
    return str;
}

QString PropertyMapInternal::toJSLiteral() const
{
    return toJSLiteral_impl(m_value);
}

void PropertyMapInternal::load(PersistentPool &pool)
{
    m_value = pool.loadVariantMap();
}

void PropertyMapInternal::store(PersistentPool &pool) const
{
    pool.store(m_value);
}

} // namespace Internal
} // namespace qbs
