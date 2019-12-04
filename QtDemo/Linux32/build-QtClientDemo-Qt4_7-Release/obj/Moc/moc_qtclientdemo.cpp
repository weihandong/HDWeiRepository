/****************************************************************************
** Meta object code from reading C++ file 'qtclientdemo.h'
**
** Created: Sun Dec 1 18:46:42 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/qtclientdemo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtclientdemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtClientDemo[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      47,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      27,   13,   13,   13, 0x08,
      58,   13,   13,   13, 0x08,
      86,   13,   13,   13, 0x08,
     115,   13,   13,   13, 0x08,
     127,   13,   13,   13, 0x08,
     150,   13,   13,   13, 0x08,
     175,   13,   13,   13, 0x08,
     189,   13,   13,   13, 0x08,
     204,   13,   13,   13, 0x08,
     219,   13,   13,   13, 0x08,
     237,   13,   13,   13, 0x08,
     250,   13,   13,   13, 0x08,
     270,   13,   13,   13, 0x08,
     295,   13,   13,   13, 0x08,
     322,   13,   13,   13, 0x08,
     348,   13,   13,   13, 0x08,
     376,   13,   13,   13, 0x08,
     391,   13,   13,   13, 0x08,
     406,   13,   13,   13, 0x08,
     419,   13,   13,   13, 0x08,
     434,   13,   13,   13, 0x08,
     451,   13,   13,   13, 0x08,
     471,   13,   13,   13, 0x08,
     485,   13,   13,   13, 0x08,
     510,   13,   13,   13, 0x08,
     534,   13,   13,   13, 0x08,
     551,   13,   13,   13, 0x08,
     568,   13,   13,   13, 0x08,
     592,   13,   13,   13, 0x08,
     612,   13,   13,   13, 0x08,
     628,   13,   13,   13, 0x08,
     645,   13,   13,   13, 0x08,
     661,   13,   13,   13, 0x08,
     676,   13,   13,   13, 0x08,
     693,   13,   13,   13, 0x08,
     727,   13,   13,   13, 0x08,
     759,   13,   13,   13, 0x08,
     792,   13,   13,   13, 0x08,
     823,   13,   13,   13, 0x08,
     853,   13,   13,   13, 0x08,
     882,   13,   13,   13, 0x08,
     916,   13,   13,   13, 0x08,
     951,   13,   13,   13, 0x08,
     988,   13,   13,   13, 0x08,
    1024,   13,   13,   13, 0x08,
    1064,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtClientDemo[] = {
    "QtClientDemo\0\0updateTime()\0"
    "OnDoubleClickTree(QModelIndex)\0"
    "showTreeContextMenu(QPoint)\0"
    "pressedTreeView(QModelIndex)\0enterview()\0"
    "addDeviceSureClicked()\0addDeviceCancelClicked()\0"
    "loginDevice()\0logoutDevice()\0"
    "deleteDevice()\0showDevAttrDial()\0"
    "getJPEGpic()\0showChannAttrDial()\0"
    "modfDevAttrSureClicked()\0"
    "modfDevAttrCancelClicked()\0"
    "modfChanAttrSureClicked()\0"
    "modfChanAttrCancelClicked()\0timingDevice()\0"
    "updateDevice()\0formatDisk()\0rebootDevice()\0"
    "shutdownDevice()\0searchlogOnDevice()\0"
    "deviceState()\0setDeviceDefaultConfig()\0"
    "deploymentOrNotDevice()\0manualSaveFile()\0"
    "serialTransfer()\0devicePanelSimulation()\0"
    "importExortConfig()\0auidoIntercom()\0"
    "audioBroadcast()\0audioTransfer()\0"
    "exitDemoSure()\0exitDemoCancel()\0"
    "on_Configure_pushButton_clicked()\0"
    "on_Preview_pushButton_clicked()\0"
    "on_PlayBack_pushButton_clicked()\0"
    "on_Manage_pushButton_clicked()\0"
    "on_Other_pushButton_clicked()\0"
    "on_Exit_pushButton_clicked()\0"
    "on_radioButton_locallog_pressed()\0"
    "on_radioButton_alarminfo_pressed()\0"
    "on_pushButton_logaramclear_clicked()\0"
    "on_pushButton_logaramsave_clicked()\0"
    "on_pushButton_logaramlistconf_clicked()\0"
    "on_pushButton_logaramtest_clicked()\0"
};

const QMetaObject QtClientDemo::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtClientDemo,
      qt_meta_data_QtClientDemo, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtClientDemo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtClientDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtClientDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtClientDemo))
        return static_cast<void*>(const_cast< QtClientDemo*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtClientDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateTime(); break;
        case 1: OnDoubleClickTree((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: showTreeContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: pressedTreeView((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: enterview(); break;
        case 5: addDeviceSureClicked(); break;
        case 6: addDeviceCancelClicked(); break;
        case 7: loginDevice(); break;
        case 8: logoutDevice(); break;
        case 9: deleteDevice(); break;
        case 10: showDevAttrDial(); break;
        case 11: getJPEGpic(); break;
        case 12: showChannAttrDial(); break;
        case 13: modfDevAttrSureClicked(); break;
        case 14: modfDevAttrCancelClicked(); break;
        case 15: modfChanAttrSureClicked(); break;
        case 16: modfChanAttrCancelClicked(); break;
        case 17: timingDevice(); break;
        case 18: updateDevice(); break;
        case 19: formatDisk(); break;
        case 20: rebootDevice(); break;
        case 21: shutdownDevice(); break;
        case 22: searchlogOnDevice(); break;
        case 23: deviceState(); break;
        case 24: setDeviceDefaultConfig(); break;
        case 25: deploymentOrNotDevice(); break;
        case 26: manualSaveFile(); break;
        case 27: serialTransfer(); break;
        case 28: devicePanelSimulation(); break;
        case 29: importExortConfig(); break;
        case 30: auidoIntercom(); break;
        case 31: audioBroadcast(); break;
        case 32: audioTransfer(); break;
        case 33: exitDemoSure(); break;
        case 34: exitDemoCancel(); break;
        case 35: on_Configure_pushButton_clicked(); break;
        case 36: on_Preview_pushButton_clicked(); break;
        case 37: on_PlayBack_pushButton_clicked(); break;
        case 38: on_Manage_pushButton_clicked(); break;
        case 39: on_Other_pushButton_clicked(); break;
        case 40: on_Exit_pushButton_clicked(); break;
        case 41: on_radioButton_locallog_pressed(); break;
        case 42: on_radioButton_alarminfo_pressed(); break;
        case 43: on_pushButton_logaramclear_clicked(); break;
        case 44: on_pushButton_logaramsave_clicked(); break;
        case 45: on_pushButton_logaramlistconf_clicked(); break;
        case 46: on_pushButton_logaramtest_clicked(); break;
        default: ;
        }
        _id -= 47;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
