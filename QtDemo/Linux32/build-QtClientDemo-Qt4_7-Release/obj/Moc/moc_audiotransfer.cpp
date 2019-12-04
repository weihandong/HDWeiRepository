/****************************************************************************
** Meta object code from reading C++ file 'audiotransfer.h'
**
** Created: Sun Dec 1 18:46:40 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/OtherFunc/AudioTransfer/audiotransfer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audiotransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AudioTransfer[] = {

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
      15,   14,   14,   14, 0x08,
      56,   44,   14,   14, 0x08,
      98,   14,   14,   14, 0x08,
     129,   14,   14,   14, 0x08,
     164,   14,   14,   14, 0x08,
     196,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AudioTransfer[] = {
    "AudioTransfer\0\0on_pushButton_exit_clicked()\0"
    "item,column\0audioTransferDevice(QTreeWidgetItem*,int)\0"
    "on_pushButton_browse_clicked()\0"
    "on_pushButton_talkmrsend_clicked()\0"
    "on_pushButton_startmr_clicked()\0"
    "on_pushButton_stopmr_clicked()\0"
};

const QMetaObject AudioTransfer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AudioTransfer,
      qt_meta_data_AudioTransfer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioTransfer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioTransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioTransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioTransfer))
        return static_cast<void*>(const_cast< AudioTransfer*>(this));
    return QDialog::qt_metacast(_clname);
}

int AudioTransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_exit_clicked(); break;
        case 1: audioTransferDevice((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: on_pushButton_browse_clicked(); break;
        case 3: on_pushButton_talkmrsend_clicked(); break;
        case 4: on_pushButton_startmr_clicked(); break;
        case 5: on_pushButton_stopmr_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
