/****************************************************************************
** Meta object code from reading C++ file 'formatdisk.h'
**
** Created: Sun Dec 1 18:46:34 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ManageDevice/Format/formatdisk.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formatdisk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormatDisk[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x08,
      55,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormatDisk[] = {
    "FormatDisk\0\0index\0"
    "on_comboBox_currentIndexChanged(int)\0"
    "on_pushButton_format_clicked()\0"
    "on_pushButton_exit_clicked()\0"
};

const QMetaObject FormatDisk::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FormatDisk,
      qt_meta_data_FormatDisk, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormatDisk::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormatDisk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormatDisk::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormatDisk))
        return static_cast<void*>(const_cast< FormatDisk*>(this));
    return QDialog::qt_metacast(_clname);
}

int FormatDisk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_pushButton_format_clicked(); break;
        case 2: on_pushButton_exit_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE