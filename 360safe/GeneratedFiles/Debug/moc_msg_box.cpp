/****************************************************************************
** Meta object code from reading C++ file 'msg_box.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../msg_box.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msg_box.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MsgBox_t {
    QByteArrayData data[8];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MsgBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MsgBox_t qt_meta_stringdata_MsgBox = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 15),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 10),
QT_MOC_LITERAL(4, 35, 10),
QT_MOC_LITERAL(5, 46, 5),
QT_MOC_LITERAL(6, 52, 9),
QT_MOC_LITERAL(7, 62, 13)
    },
    "MsgBox\0okMessageHidden\0\0is_checked\0"
    "msgChecked\0is_ok\0okOperate\0cancelOperate\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MsgBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x05,
       4,    2,   37,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    0,   42,    2, 0x08,
       7,    0,   43,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    3,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MsgBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MsgBox *_t = static_cast<MsgBox *>(_o);
        switch (_id) {
        case 0: _t->okMessageHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->msgChecked((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->okOperate(); break;
        case 3: _t->cancelOperate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MsgBox::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MsgBox::okMessageHidden)) {
                *result = 0;
            }
        }
        {
            typedef void (MsgBox::*_t)(bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MsgBox::msgChecked)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MsgBox::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_MsgBox.data,
      qt_meta_data_MsgBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *MsgBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MsgBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MsgBox.stringdata))
        return static_cast<void*>(const_cast< MsgBox*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int MsgBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropShadowWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MsgBox::okMessageHidden(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MsgBox::msgChecked(bool _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
