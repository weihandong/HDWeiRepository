/****************************************************************************
** Meta object code from reading C++ file 'devicepan.h'
**
** Created: Sun Dec 1 18:46:38 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/OtherFunc/DevicePan/devicepan.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devicepan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DevicePan[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      44,   10,   10,   10, 0x08,
      76,   10,   10,   10, 0x08,
     108,   10,   10,   10, 0x08,
     140,   10,   10,   10, 0x08,
     172,   10,   10,   10, 0x08,
     207,   10,   10,   10, 0x08,
     239,   10,   10,   10, 0x08,
     273,   10,   10,   10, 0x08,
     306,   10,   10,   10, 0x08,
     339,   10,   10,   10, 0x08,
     372,   10,   10,   10, 0x08,
     404,   10,   10,   10, 0x08,
     437,   10,   10,   10, 0x08,
     470,   10,   10,   10, 0x08,
     503,   10,   10,   10, 0x08,
     536,   10,   10,   10, 0x08,
     565,   10,   10,   10, 0x08,
     594,   10,   10,   10, 0x08,
     623,   10,   10,   10, 0x08,
     656,   10,   10,   10, 0x08,
     688,   10,   10,   10, 0x08,
     720,   10,   10,   10, 0x08,
     752,   10,   10,   10, 0x08,
     784,   10,   10,   10, 0x08,
     814,   10,   10,   10, 0x08,
     844,   10,   10,   10, 0x08,
     872,   10,   10,   10, 0x08,
     908,   10,   10,   10, 0x08,
     937,   10,   10,   10, 0x08,
     970,   10,   10,   10, 0x08,
    1005,   10,   10,   10, 0x08,
    1032,   10,   10,   10, 0x08,
    1062,   10,   10,   10, 0x08,
    1091,   10,   10,   10, 0x08,
    1123,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DevicePan[] = {
    "DevicePan\0\0on_pushButton_ptzstart_clicked()\0"
    "on_pushButton_button8_clicked()\0"
    "on_pushButton_button5_clicked()\0"
    "on_pushButton_button6_clicked()\0"
    "on_pushButton_button7_clicked()\0"
    "on_pushButton_ptzcontrol_clicked()\0"
    "on_pushButton_panlock_clicked()\0"
    "on_pushButton_panunlock_clicked()\0"
    "on_pushButton_button11_clicked()\0"
    "on_pushButton_button10_clicked()\0"
    "on_pushButton_button12_clicked()\0"
    "on_pushButton_button9_clicked()\0"
    "on_pushButton_button15_clicked()\0"
    "on_pushButton_button14_clicked()\0"
    "on_pushButton_button16_clicked()\0"
    "on_pushButton_button13_clicked()\0"
    "on_pushButton_play_clicked()\0"
    "on_pushButton_edit_clicked()\0"
    "on_pushButton_save_clicked()\0"
    "on_pushButton_mainmenu_clicked()\0"
    "on_pushButton_button3_clicked()\0"
    "on_pushButton_button2_clicked()\0"
    "on_pushButton_button4_clicked()\0"
    "on_pushButton_button1_clicked()\0"
    "on_pushButton_enter_clicked()\0"
    "on_pushButton_input_clicked()\0"
    "on_pushButton_esc_clicked()\0"
    "on_pushButton_multiwindow_clicked()\0"
    "on_pushButton_down_clicked()\0"
    "on_pushButton_intercom_clicked()\0"
    "on_pushButton_systeminfo_clicked()\0"
    "on_pushButton_up_clicked()\0"
    "on_pushButton_right_clicked()\0"
    "on_pushButton_left_clicked()\0"
    "on_pushButton_ptzstop_clicked()\0"
    "on_pushButton_exit_clicked()\0"
};

const QMetaObject DevicePan::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DevicePan,
      qt_meta_data_DevicePan, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DevicePan::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DevicePan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DevicePan::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DevicePan))
        return static_cast<void*>(const_cast< DevicePan*>(this));
    return QDialog::qt_metacast(_clname);
}

int DevicePan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_ptzstart_clicked(); break;
        case 1: on_pushButton_button8_clicked(); break;
        case 2: on_pushButton_button5_clicked(); break;
        case 3: on_pushButton_button6_clicked(); break;
        case 4: on_pushButton_button7_clicked(); break;
        case 5: on_pushButton_ptzcontrol_clicked(); break;
        case 6: on_pushButton_panlock_clicked(); break;
        case 7: on_pushButton_panunlock_clicked(); break;
        case 8: on_pushButton_button11_clicked(); break;
        case 9: on_pushButton_button10_clicked(); break;
        case 10: on_pushButton_button12_clicked(); break;
        case 11: on_pushButton_button9_clicked(); break;
        case 12: on_pushButton_button15_clicked(); break;
        case 13: on_pushButton_button14_clicked(); break;
        case 14: on_pushButton_button16_clicked(); break;
        case 15: on_pushButton_button13_clicked(); break;
        case 16: on_pushButton_play_clicked(); break;
        case 17: on_pushButton_edit_clicked(); break;
        case 18: on_pushButton_save_clicked(); break;
        case 19: on_pushButton_mainmenu_clicked(); break;
        case 20: on_pushButton_button3_clicked(); break;
        case 21: on_pushButton_button2_clicked(); break;
        case 22: on_pushButton_button4_clicked(); break;
        case 23: on_pushButton_button1_clicked(); break;
        case 24: on_pushButton_enter_clicked(); break;
        case 25: on_pushButton_input_clicked(); break;
        case 26: on_pushButton_esc_clicked(); break;
        case 27: on_pushButton_multiwindow_clicked(); break;
        case 28: on_pushButton_down_clicked(); break;
        case 29: on_pushButton_intercom_clicked(); break;
        case 30: on_pushButton_systeminfo_clicked(); break;
        case 31: on_pushButton_up_clicked(); break;
        case 32: on_pushButton_right_clicked(); break;
        case 33: on_pushButton_left_clicked(); break;
        case 34: on_pushButton_ptzstop_clicked(); break;
        case 35: on_pushButton_exit_clicked(); break;
        default: ;
        }
        _id -= 36;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
