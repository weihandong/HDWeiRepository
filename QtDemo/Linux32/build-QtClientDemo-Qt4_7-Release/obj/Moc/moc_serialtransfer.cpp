/****************************************************************************
** Meta object code from reading C++ file 'serialtransfer.h'
**
** Created: Sun Dec 1 18:46:39 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/OtherFunc/SerialTransfer/serialtransfer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialtransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialTransfer[] = {

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
      22,   16,   15,   15, 0x08,
      71,   16,   15,   15, 0x08,
     119,   16,   15,   15, 0x08,
     170,   15,   15,   15, 0x08,
     199,   15,   15,   15, 0x08,
     235,   15,   15,   15, 0x08,
     270,   15,   15,   15, 0x08,
     304,  299,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SerialTransfer[] = {
    "SerialTransfer\0\0index\0"
    "on_comboBox_channeltype_currentIndexChanged(int)\0"
    "on_comboBox_channelnum_currentIndexChanged(int)\0"
    "on_comboBox_sendinterface_currentIndexChanged(int)\0"
    "on_pushButton_send_clicked()\0"
    "on_pushButton_startserial_clicked()\0"
    "on_pushButton_stopserial_clicked()\0"
    "on_pushButton_exit_clicked()\0text\0"
    "on_lineEdit_textChanged(QString)\0"
};

const QMetaObject SerialTransfer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SerialTransfer,
      qt_meta_data_SerialTransfer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialTransfer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialTransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialTransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialTransfer))
        return static_cast<void*>(const_cast< SerialTransfer*>(this));
    return QDialog::qt_metacast(_clname);
}

int SerialTransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_comboBox_channeltype_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_comboBox_channelnum_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_comboBox_sendinterface_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_pushButton_send_clicked(); break;
        case 4: on_pushButton_startserial_clicked(); break;
        case 5: on_pushButton_stopserial_clicked(); break;
        case 6: on_pushButton_exit_clicked(); break;
        case 7: on_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
