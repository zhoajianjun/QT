/****************************************************************************
** Meta object code from reading C++ file 'filetransfer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../NetChat/filetransfer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filetransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileTransfer_t {
    QByteArrayData data[10];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileTransfer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileTransfer_t qt_meta_stringdata_FileTransfer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FileTransfer"
QT_MOC_LITERAL(1, 13, 26), // "on_Open_pushButton_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 26), // "on_Send_pushButton_clicked"
QT_MOC_LITERAL(4, 68, 32), // "on_FileName_lineEdit_textChanged"
QT_MOC_LITERAL(5, 101, 4), // "arg1"
QT_MOC_LITERAL(6, 106, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 128, 8), // "SendFile"
QT_MOC_LITERAL(8, 137, 14), // "UpdateProgress"
QT_MOC_LITERAL(9, 152, 8) // "numBytes"

    },
    "FileTransfer\0on_Open_pushButton_clicked\0"
    "\0on_Send_pushButton_clicked\0"
    "on_FileName_lineEdit_textChanged\0arg1\0"
    "on_pushButton_clicked\0SendFile\0"
    "UpdateProgress\0numBytes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileTransfer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    1,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    9,

       0        // eod
};

void FileTransfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileTransfer *_t = static_cast<FileTransfer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Open_pushButton_clicked(); break;
        case 1: _t->on_Send_pushButton_clicked(); break;
        case 2: _t->on_FileName_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->SendFile(); break;
        case 5: _t->UpdateProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FileTransfer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FileTransfer.data,
      qt_meta_data_FileTransfer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileTransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileTransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileTransfer.stringdata0))
        return static_cast<void*>(const_cast< FileTransfer*>(this));
    return QWidget::qt_metacast(_clname);
}

int FileTransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
