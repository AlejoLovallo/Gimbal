/****************************************************************************
** Meta object code from reading C++ file 'comserie.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interfaz/comserie.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comserie.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_comserie_t {
    QByteArrayData data[9];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_comserie_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_comserie_t qt_meta_stringdata_comserie = {
    {
QT_MOC_LITERAL(0, 0, 8), // "comserie"
QT_MOC_LITERAL(1, 9, 35), // "on_comboBoxPort_currentIndexC..."
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5), // "index"
QT_MOC_LITERAL(4, 52, 27), // "on_pushButtonEnviar_clicked"
QT_MOC_LITERAL(5, 80, 29), // "on_pushButtonConectar_clicked"
QT_MOC_LITERAL(6, 110, 10), // "on_Port_rx"
QT_MOC_LITERAL(7, 121, 20), // "on_comserie_finished"
QT_MOC_LITERAL(8, 142, 6) // "result"

    },
    "comserie\0on_comboBoxPort_currentIndexChanged\0"
    "\0index\0on_pushButtonEnviar_clicked\0"
    "on_pushButtonConectar_clicked\0on_Port_rx\0"
    "on_comserie_finished\0result"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_comserie[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    0,   42,    2, 0x08 /* Private */,
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    1,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void comserie::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<comserie *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_comboBoxPort_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_pushButtonEnviar_clicked(); break;
        case 2: _t->on_pushButtonConectar_clicked(); break;
        case 3: _t->on_Port_rx(); break;
        case 4: _t->on_comserie_finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject comserie::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_comserie.data,
    qt_meta_data_comserie,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *comserie::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *comserie::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_comserie.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int comserie::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE