/****************************************************************************
** Meta object code from reading C++ file 'snipasteapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../snipasteapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'snipasteapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SnipasteApp_t {
    QByteArrayData data[12];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SnipasteApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SnipasteApp_t qt_meta_stringdata_SnipasteApp = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SnipasteApp"
QT_MOC_LITERAL(1, 12, 8), // "Finished"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "pix"
QT_MOC_LITERAL(4, 26, 7), // "SavePic"
QT_MOC_LITERAL(5, 34, 4), // "path"
QT_MOC_LITERAL(6, 39, 7), // "ClipPic"
QT_MOC_LITERAL(7, 47, 6), // "PinPic"
QT_MOC_LITERAL(8, 54, 10), // "ScreenShot"
QT_MOC_LITERAL(9, 65, 11), // "funcHandler"
QT_MOC_LITERAL(10, 77, 8), // "QAction*"
QT_MOC_LITERAL(11, 86, 6) // "action"

    },
    "SnipasteApp\0Finished\0\0pix\0SavePic\0"
    "path\0ClipPic\0PinPic\0ScreenShot\0"
    "funcHandler\0QAction*\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SnipasteApp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    0,   50,    2, 0x06 /* Public */,
       7,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   52,    2, 0x08 /* Private */,
       9,    1,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPixmap,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void SnipasteApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SnipasteApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Finished((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 1: _t->SavePic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ClipPic(); break;
        case 3: _t->PinPic(); break;
        case 4: _t->ScreenShot(); break;
        case 5: _t->funcHandler((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SnipasteApp::*)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SnipasteApp::Finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SnipasteApp::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SnipasteApp::SavePic)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SnipasteApp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SnipasteApp::ClipPic)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SnipasteApp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SnipasteApp::PinPic)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SnipasteApp::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SnipasteApp.data,
    qt_meta_data_SnipasteApp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SnipasteApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SnipasteApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SnipasteApp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SnipasteApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SnipasteApp::Finished(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SnipasteApp::SavePic(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SnipasteApp::ClipPic()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SnipasteApp::PinPic()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
