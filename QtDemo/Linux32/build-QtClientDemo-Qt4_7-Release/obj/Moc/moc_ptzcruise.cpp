/****************************************************************************
** Meta object code from reading C++ file 'ptzcruise.h'
**
** Created: Sun Dec 1 18:46:30 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/RealPlay/PTZ/PtzCruise/ptzcruise.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ptzcruise.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PtzCruise[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      50,   10,   10,   10, 0x08,
      92,   10,   10,   10, 0x08,
     127,  121,   10,   10, 0x08,
     178,  121,   10,   10, 0x08,
     230,  121,   10,   10, 0x08,
     288,  121,   10,   10, 0x08,
     339,  121,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PtzCruise[] = {
    "PtzCruise\0\0on_pushButton_addcruisepoint_clicked()\0"
    "on_pushButton_deletecruisepoint_clicked()\0"
    "on_pushButton_exit_clicked()\0index\0"
    "on_comboBox_ptzcruisepath_currentIndexChanged(int)\0"
    "on_comboBox_ptzcruisepoint_currentIndexChanged(int)\0"
    "on_comboBox_ptzcruisepresetpoint_currentIndexChanged(int)\0"
    "on_comboBox_ptzcruisetime_currentIndexChanged(int)\0"
    "on_comboBox_ptzcruisespeed_currentIndexChanged(int)\0"
};

const QMetaObject PtzCruise::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PtzCruise,
      qt_meta_data_PtzCruise, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PtzCruise::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PtzCruise::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PtzCruise::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PtzCruise))
        return static_cast<void*>(const_cast< PtzCruise*>(this));
    return QDialog::qt_metacast(_clname);
}

int PtzCruise::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_addcruisepoint_clicked(); break;
        case 1: on_pushButton_deletecruisepoint_clicked(); break;
        case 2: on_pushButton_exit_clicked(); break;
        case 3: on_comboBox_ptzcruisepath_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on_comboBox_ptzcruisepoint_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_comboBox_ptzcruisepresetpoint_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_comboBox_ptzcruisetime_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_comboBox_ptzcruisespeed_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE