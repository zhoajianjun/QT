/****************************************************************************
**
** Copyright (C) 2015 Petroules Corporation.
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

#import <Foundation/Foundation.h>
#include "propertylistutils.h"
#include <QByteArray>
#include <QDateTime>
#include <QString>
#include <QVariantMap>

static inline QDateTime QDateTime_fromNSDate(const NSDate *date)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    return QDateTime::fromNSDate(date);
#else
    if (!date)
        return QDateTime();
    return QDateTime::fromMSecsSinceEpoch(static_cast<qint64>([date timeIntervalSince1970] * 1000));
#endif
}

static inline NSDate *QDateTime_toNSDate(const QDateTime &qdatetime)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    return qdatetime.toNSDate();
#else
    return [NSDate
        dateWithTimeIntervalSince1970:static_cast<NSTimeInterval>(qdatetime.toMSecsSinceEpoch()) / 1000];
#endif
}

static QVariant fromObject(id obj);
static QVariantMap fromDictionary(NSDictionary *dict);
static QVariantList fromArray(NSArray *array);

static QVariant fromObject(id obj)
{
    QVariant value;
    if (!obj) {
        return value;
    } else if ([obj isKindOfClass:[NSDictionary class]]) {
        value = fromDictionary(obj);
    } else if ([obj isKindOfClass:[NSArray class]]) {
        value = fromArray(obj);
    } else if ([obj isKindOfClass:[NSString class]]) {
        value = QString_fromNSString(obj);
    } else if ([obj isKindOfClass:[NSData class]]) {
        value = QByteArray_fromNSData(obj);
    } else if ([obj isKindOfClass:[NSDate class]]) {
        value = QDateTime_fromNSDate(obj);
    } else if ([obj isKindOfClass:[NSNumber class]]) {
        if (strcmp([(NSNumber *)obj objCType], @encode(BOOL)) == 0) {
            value = static_cast<bool>([obj boolValue]);
        } else if (strcmp([(NSNumber *)obj objCType], @encode(signed char)) == 0) {
            value = [obj charValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(unsigned char)) == 0) {
            value = [obj unsignedCharValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(signed short)) == 0) {
            value = [obj shortValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(unsigned short)) == 0) {
            value = [obj unsignedShortValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(signed int)) == 0) {
            value = [obj intValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(unsigned int)) == 0) {
            value = [obj unsignedIntValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(signed long long)) == 0) {
            value = [obj longLongValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(unsigned long long)) == 0) {
            value = [obj unsignedLongLongValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(float)) == 0) {
            value = [obj floatValue];
        } else if (strcmp([(NSNumber *)obj objCType], @encode(double)) == 0) {
            value = [obj doubleValue];
        } else {
            // NSDecimal or unknown
            value = [obj doubleValue];
        }
    } else if ([obj isKindOfClass:[NSNull class]]) {
        // A null variant, close enough...
    } else {
        // unknown
    }

    return value;
}

static QVariantMap fromDictionary(NSDictionary *dict)
{
    QVariantMap map;
    for (NSString *key in dict)
        map[QString_fromNSString(key)] = fromObject([dict objectForKey:key]);
    return map;
}

static QVariantList fromArray(NSArray *array)
{
    QVariantList list;
    for (id obj in array)
        list.append(fromObject(obj));
    return list;
}

QVariant QPropertyListUtils::fromPropertyList(id plist)
{
    return fromObject(plist);
}

static id toObject(const QVariant &variant);
static NSDictionary *toDictionary(const QVariantMap &map);
static NSArray *toArray(const QVariantList &list);

static id toObject(const QVariant &variant)
{
    if (variant.type() == QVariant::Hash) {
        return toDictionary(qHashToMap(variant.toHash()));
    } else if (variant.type() == QVariant::Map) {
        return toDictionary(variant.toMap());
    } else if (variant.type() == QVariant::List) {
        return toArray(variant.toList());
    } else if (variant.type() == QVariant::String) {
        return QString_toNSString(variant.toString());
    } else if (variant.type() == QVariant::ByteArray) {
        return QByteArray_toNSData(variant.toByteArray());
    } else if (variant.type() == QVariant::Date ||
               variant.type() == QVariant::DateTime) {
        return QDateTime_toNSDate(variant.toDateTime());
    } else if (variant.type() == QVariant::Bool) {
        return variant.toBool()
                ? [NSNumber numberWithBool:YES]
                : [NSNumber numberWithBool:NO];
    } else if (variant.type() == QVariant::Char ||
               variant.type() == QVariant::Int) {
        return [NSNumber numberWithInt:variant.toInt()];
    } else if (variant.type() == QVariant::UInt) {
        return [NSNumber numberWithUnsignedInt:variant.toUInt()];
    } else if (variant.type() == QVariant::LongLong) {
        return [NSNumber numberWithLongLong:variant.toLongLong()];
    } else if (variant.type() == QVariant::ULongLong) {
        return [NSNumber numberWithUnsignedLongLong:variant.toULongLong()];
    } else if (variant.type() == QVariant::Double) {
        return [NSNumber numberWithDouble:variant.toDouble()];
    } else {
        return [NSNull null];
    }
}

static NSDictionary *toDictionary(const QVariantMap &map)
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        [dict setObject:toObject(i.value()) forKey:QString_toNSString(i.key())];
    }
    return [NSDictionary dictionaryWithDictionary:dict];
}

static NSArray *toArray(const QVariantList &list)
{
    NSMutableArray *array = [NSMutableArray array];
    foreach (const QVariant &variant, list)
        [array addObject:toObject(variant)];
    return [NSArray arrayWithArray:array];
}

id QPropertyListUtils::toPropertyList(const QVariant &variant)
{
    return toObject(variant);
}
