/****************************************************************************
** Meta object code from reading C++ file 'cadvancednetparams.h'
**
** Created: Sun Dec 1 18:46:46 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ParaConfig/configure_params/RemoteParams/NetParams/cadvancednetparams.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cadvancednetparams.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CAdvancedNetParams[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      33,   19,   19,   19, 0x0a,
      44,   19,   19,   19, 0x0a,
      56,   19,   19,   19, 0x0a,
      69,   19,   19,   19, 0x0a,
      85,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CAdvancedNetParams[] = {
    "CAdvancedNetParams\0\0clickPPPoE()\0"
    "clickNTP()\0clickDDNS()\0saveParams()\0"
    "refreshParams()\0on_btnExit_clicked()\0"
};

const QMetaObject CAdvancedNetParams::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CAdvancedNetParams,
      qt_meta_data_CAdvancedNetParams, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CAdvancedNetParams::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CAdvancedNetParams::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CAdvancedNetParams::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CAdvancedNetParams))
        return static_cast<void*>(const_cast< CAdvancedNetParams*>(this));
    return QDialog::qt_metacast(_clname);
}

int CAdvancedNetParams::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickPPPoE(); break;
        case 1: clickNTP(); break;
        case 2: clickDDNS(); break;
        case 3: saveParams(); break;
        case 4: refreshParams(); break;
        case 5: on_btnExit_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
