/****************************************************************************
** Meta object code from reading C++ file 'importconfig.h'
**
** Created: Sun Dec 1 18:46:38 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/OtherFunc/ImportConfig/importconfig.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'importconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImportConfig[] = {

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
      26,   14,   13,   13, 0x08,
      61,   13,   13,   13, 0x08,
      92,   13,   13,   13, 0x08,
     123,   13,   13,   13, 0x08,
     152,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImportConfig[] = {
    "ImportConfig\0\0item,column\0"
    "importDevice(QTreeWidgetItem*,int)\0"
    "on_pushButton_export_clicked()\0"
    "on_pushButton_import_clicked()\0"
    "on_pushButton_exit_clicked()\0"
    "on_pushButton_browse_clicked()\0"
};

const QMetaObject ImportConfig::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ImportConfig,
      qt_meta_data_ImportConfig, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImportConfig::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImportConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImportConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImportConfig))
        return static_cast<void*>(const_cast< ImportConfig*>(this));
    return QDialog::qt_metacast(_clname);
}

int ImportConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: importDevice((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: on_pushButton_export_clicked(); break;
        case 2: on_pushButton_import_clicked(); break;
        case 3: on_pushButton_exit_clicked(); break;
        case 4: on_pushButton_browse_clicked(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
