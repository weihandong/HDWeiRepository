/****************************************************************************
** Meta object code from reading C++ file 'calarminptz.h'
**
** Created: Sun Dec 1 18:46:53 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ParaConfig/configure_params/RemoteParams/AlarmParams/calarminptz.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calarminptz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CAlarmInPTZ[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x0a,
      46,   40,   12,   12, 0x0a,
      69,   12,   12,   12, 0x0a,
      93,   12,   12,   12, 0x0a,
     117,   12,   12,   12, 0x0a,
     143,   12,   12,   12, 0x0a,
     164,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CAlarmInPTZ[] = {
    "CAlarmInPTZ\0\0index\0changeChanIndex(int)\0"
    "event\0showEvent(QShowEvent*)\0"
    "on_rBtnPreset_clicked()\0on_rBtnCruise_clicked()\0"
    "on_rBtnPtzTrack_clicked()\0"
    "on_btnSave_clicked()\0on_btnExit_clicked()\0"
};

const QMetaObject CAlarmInPTZ::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CAlarmInPTZ,
      qt_meta_data_CAlarmInPTZ, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CAlarmInPTZ::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CAlarmInPTZ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CAlarmInPTZ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CAlarmInPTZ))
        return static_cast<void*>(const_cast< CAlarmInPTZ*>(this));
    return QDialog::qt_metacast(_clname);
}

int CAlarmInPTZ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeChanIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 2: on_rBtnPreset_clicked(); break;
        case 3: on_rBtnCruise_clicked(); break;
        case 4: on_rBtnPtzTrack_clicked(); break;
        case 5: on_btnSave_clicked(); break;
        case 6: on_btnExit_clicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
