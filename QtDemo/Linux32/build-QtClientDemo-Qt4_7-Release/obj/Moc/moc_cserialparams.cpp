/****************************************************************************
** Meta object code from reading C++ file 'cserialparams.h'
**
** Created: Sun Dec 1 18:46:51 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ParaConfig/configure_params/RemoteParams/SerialParams/cserialparams.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cserialparams.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSerialParams[] = {

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
      15,   14,   14,   14, 0x0a,
      37,   31,   14,   14, 0x0a,
      58,   31,   14,   14, 0x0a,
      82,   14,   14,   14, 0x0a,
      95,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSerialParams[] = {
    "CSerialParams\0\0refreshparams()\0index\0"
    "changeChanIndex(int)\0change232WorkState(int)\0"
    "saveparams()\0PppSetup()\0"
};

const QMetaObject CSerialParams::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSerialParams,
      qt_meta_data_CSerialParams, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSerialParams::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSerialParams::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSerialParams::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSerialParams))
        return static_cast<void*>(const_cast< CSerialParams*>(this));
    return QWidget::qt_metacast(_clname);
}

int CSerialParams::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refreshparams(); break;
        case 1: changeChanIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: change232WorkState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: saveparams(); break;
        case 4: PppSetup(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
