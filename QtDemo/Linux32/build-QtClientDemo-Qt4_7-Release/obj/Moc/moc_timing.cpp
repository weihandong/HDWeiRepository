/****************************************************************************
** Meta object code from reading C++ file 'timing.h'
**
** Created: Sun Dec 1 18:46:32 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ManageDevice/Timing/timing.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Timing[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      39,    7,    7,    7, 0x08,
      80,   68,    7,    7, 0x08,
     124,  115,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Timing[] = {
    "Timing\0\0on_pushButton_timing_clicked()\0"
    "on_pushButton_exit_clicked()\0item,column\0"
    "timingDevice(QTreeWidgetItem*,int)\0"
    "datetime\0on_dateTimeEdit_dateTimeChanged(QDateTime)\0"
};

const QMetaObject Timing::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Timing,
      qt_meta_data_Timing, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Timing::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Timing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Timing::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Timing))
        return static_cast<void*>(const_cast< Timing*>(this));
    return QDialog::qt_metacast(_clname);
}

int Timing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_timing_clicked(); break;
        case 1: on_pushButton_exit_clicked(); break;
        case 2: timingDevice((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: on_dateTimeEdit_dateTimeChanged((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE