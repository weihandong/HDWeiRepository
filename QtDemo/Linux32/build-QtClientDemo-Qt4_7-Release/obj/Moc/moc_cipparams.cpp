/****************************************************************************
** Meta object code from reading C++ file 'cipparams.h'
**
** Created: Sun Dec 1 18:46:55 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ParaConfig/configure_params/IPParams/cipparams.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cipparams.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CIPParams[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   11,   10, 0x0a,
      41,   10,   10,   10, 0x0a,
      62,   10,   10,   10, 0x0a,
      85,   10,   10,   10, 0x0a,
     108,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CIPParams[] = {
    "CIPParams\0\0int\0iRow\0clickTabChannel(int)\0"
    "on_btnEdit_clicked()\0on_btnDelete_clicked()\0"
    "on_btnEnable_clicked()\0on_btnDisenable_clicked()\0"
};

const QMetaObject CIPParams::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CIPParams,
      qt_meta_data_CIPParams, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CIPParams::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CIPParams::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CIPParams::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CIPParams))
        return static_cast<void*>(const_cast< CIPParams*>(this));
    return QWidget::qt_metacast(_clname);
}

int CIPParams::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = clickTabChannel((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: on_btnEdit_clicked(); break;
        case 2: on_btnDelete_clicked(); break;
        case 3: on_btnEnable_clicked(); break;
        case 4: on_btnDisenable_clicked(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
