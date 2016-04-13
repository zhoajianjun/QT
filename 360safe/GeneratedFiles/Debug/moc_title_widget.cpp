/****************************************************************************
** Meta object code from reading C++ file 'title_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../title_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'title_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TitleWidget_t {
    QByteArrayData data[8];
    char stringdata[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TitleWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TitleWidget_t qt_meta_stringdata_TitleWidget = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 8),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 7),
QT_MOC_LITERAL(4, 30, 12),
QT_MOC_LITERAL(5, 43, 11),
QT_MOC_LITERAL(6, 55, 8),
QT_MOC_LITERAL(7, 64, 12)
    },
    "TitleWidget\0showSkin\0\0showMin\0"
    "showMainMenu\0closeWidget\0turnPage\0"
    "current_page\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TitleWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x05,
       3,    0,   45,    2, 0x05,
       4,    0,   46,    2, 0x05,
       5,    0,   47,    2, 0x05,
       6,    1,   48,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    1,   51,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void TitleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TitleWidget *_t = static_cast<TitleWidget *>(_o);
        switch (_id) {
        case 0: _t->showSkin(); break;
        case 1: _t->showMin(); break;
        case 2: _t->showMainMenu(); break;
        case 3: _t->closeWidget(); break;
        case 4: _t->turnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->turnPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TitleWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleWidget::showSkin)) {
                *result = 0;
            }
        }
        {
            typedef void (TitleWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleWidget::showMin)) {
                *result = 1;
            }
        }
        {
            typedef void (TitleWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleWidget::showMainMenu)) {
                *result = 2;
            }
        }
        {
            typedef void (TitleWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleWidget::closeWidget)) {
                *result = 3;
            }
        }
        {
            typedef void (TitleWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleWidget::turnPage)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject TitleWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TitleWidget.data,
      qt_meta_data_TitleWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *TitleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TitleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TitleWidget.stringdata))
        return static_cast<void*>(const_cast< TitleWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TitleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TitleWidget::showSkin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TitleWidget::showMin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void TitleWidget::showMainMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void TitleWidget::closeWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void TitleWidget::turnPage(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
