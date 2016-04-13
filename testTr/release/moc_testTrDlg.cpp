/****************************************************************************
** Meta object code from reading C++ file 'testTrDlg.h'
**
** Created: Tue Jan 20 15:04:51 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../testTrDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testTrDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_testTrDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      21,   10,   10,   10, 0x0a,
      31,   10,   10,   10, 0x0a,
      47,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_testTrDlg[] = {
    "testTrDlg\0\0english()\0chinese()\0"
    "ILoveMyFamily()\0testTr()\0"
};

const QMetaObject testTrDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_testTrDlg,
      qt_meta_data_testTrDlg, 0 }
};

const QMetaObject *testTrDlg::metaObject() const
{
    return &staticMetaObject;
}

void *testTrDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_testTrDlg))
	return static_cast<void*>(const_cast< testTrDlg*>(this));
    if (!strcmp(_clname, "Ui::Dialog"))
	return static_cast< Ui::Dialog*>(const_cast< testTrDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int testTrDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: english(); break;
        case 1: chinese(); break;
        case 2: ILoveMyFamily(); break;
        case 3: testTr(); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
