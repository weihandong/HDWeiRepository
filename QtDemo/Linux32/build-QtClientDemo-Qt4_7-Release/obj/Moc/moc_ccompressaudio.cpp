/****************************************************************************
** Meta object code from reading C++ file 'ccompressaudio.h'
**
** Created: Sun Dec 1 18:46:45 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ParaConfig/configure_params/RemoteParams/NetParams/ccompressaudio.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccompressaudio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCompressAudio[] = {

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
      16,   15,   15,   15, 0x0a,
      28,   15,   15,   15, 0x0a,
      43,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CCompressAudio[] = {
    "CCompressAudio\0\0clickSave()\0clickRefresh()\0"
    "on_btnExit_clicked()\0"
};

const QMetaObject CCompressAudio::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CCompressAudio,
      qt_meta_data_CCompressAudio, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCompressAudio::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCompressAudio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCompressAudio::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCompressAudio))
        return static_cast<void*>(const_cast< CCompressAudio*>(this));
    return QDialog::qt_metacast(_clname);
}

int CCompressAudio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickSave(); break;
        case 1: clickRefresh(); break;
        case 2: on_btnExit_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
