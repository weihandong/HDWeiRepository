/****************************************************************************
** Meta object code from reading C++ file 'cchannelparams.h'
**
** Created: Sun Dec 1 18:46:50 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ParaConfig/configure_params/RemoteParams/ChannelParams/cchannelparams.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cchannelparams.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CChannelParams[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   16,   15,   15, 0x0a,
      63,   52,   15,   15, 0x0a,
     100,   85,   15,   15, 0x0a,
     136,  126,   15,   15, 0x0a,
     162,   15,   15,   15, 0x0a,
     185,   15,   15,   15, 0x0a,
     202,   15,   15,   15, 0x0a,
     220,   15,   15,   15, 0x0a,
     243,   15,   15,   15, 0x0a,
     264,   15,   15,   15, 0x0a,
     288,   15,   15,   15, 0x0a,
     313,   15,   15,   15, 0x0a,
     332,   15,   15,   15, 0x0a,
     352,   15,   15,   15, 0x0a,
     371,   15,   15,   15, 0x0a,
     388,   15,   15,   15, 0x0a,
     404,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CChannelParams[] = {
    "CChannelParams\0\0iChannelIndex\0"
    "comboChNoChanged(int)\0iCompIndex\0"
    "comboCompChanged(int)\0iVideoBitIndex\0"
    "comboVideoBitChanged(int)\0iStringNo\0"
    "comboStringNoChanged(int)\0"
    "clickBtnRemoteRecord()\0clickBtnVILost()\0"
    "clickBtnShelter()\0on_btnMotion_clicked()\0"
    "on_btnHide_clicked()\0clickCheckVideoRecord()\0"
    "clickCheckShowChanName()\0clickCheckVILost()\0"
    "clickCheckShelter()\0clickCheckMotion()\0"
    "clickCheckHide()\0clickCheckOSD()\0"
    "clickCheckShowString()\0"
};

const QMetaObject CChannelParams::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CChannelParams,
      qt_meta_data_CChannelParams, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CChannelParams::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CChannelParams::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CChannelParams::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CChannelParams))
        return static_cast<void*>(const_cast< CChannelParams*>(this));
    return QWidget::qt_metacast(_clname);
}

int CChannelParams::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: comboChNoChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: comboCompChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: comboVideoBitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: comboStringNoChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: clickBtnRemoteRecord(); break;
        case 5: clickBtnVILost(); break;
        case 6: clickBtnShelter(); break;
        case 7: on_btnMotion_clicked(); break;
        case 8: on_btnHide_clicked(); break;
        case 9: clickCheckVideoRecord(); break;
        case 10: clickCheckShowChanName(); break;
        case 11: clickCheckVILost(); break;
        case 12: clickCheckShelter(); break;
        case 13: clickCheckMotion(); break;
        case 14: clickCheckHide(); break;
        case 15: clickCheckOSD(); break;
        case 16: clickCheckShowString(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
