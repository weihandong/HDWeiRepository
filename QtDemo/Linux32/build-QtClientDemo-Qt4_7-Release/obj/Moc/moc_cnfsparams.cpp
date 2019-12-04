/****************************************************************************
** Meta object code from reading C++ file 'cnfsparams.h'
**
** Created: Sun Dec 1 18:46:46 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ParaConfig/configure_params/RemoteParams/NetParams/cnfsparams.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cnfsparams.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CNfsParams[] = {

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
      18,   12,   11,   11, 0x0a,
      36,   11,   11,   11, 0x0a,
      48,   11,   11,   11, 0x0a,
      63,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CNfsParams[] = {
    "CNfsParams\0\0index\0comboChanged(int)\0"
    "clickSave()\0clickRefresh()\0"
    "on_btnExit_clicked()\0"
};

const QMetaObject CNfsParams::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CNfsParams,
      qt_meta_data_CNfsParams, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CNfsParams::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CNfsParams::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CNfsParams::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CNfsParams))
        return static_cast<void*>(const_cast< CNfsParams*>(this));
    return QDialog::qt_metacast(_clname);
}

int CNfsParams::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: comboChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: clickSave(); break;
        case 2: clickRefresh(); break;
        case 3: on_btnExit_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
