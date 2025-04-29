/****************************************************************************
** Meta object code from reading C++ file 'transparentmask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../transparentmask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transparentmask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TransparentMask_t {
    QByteArrayData data[11];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransparentMask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransparentMask_t qt_meta_stringdata_TransparentMask = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TransparentMask"
QT_MOC_LITERAL(1, 16, 10), // "FinishShot"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "rect"
QT_MOC_LITERAL(4, 33, 15), // "ScreenShotStart"
QT_MOC_LITERAL(5, 49, 7), // "ShowPic"
QT_MOC_LITERAL(6, 57, 3), // "pic"
QT_MOC_LITERAL(7, 61, 7), // "SavePic"
QT_MOC_LITERAL(8, 69, 4), // "path"
QT_MOC_LITERAL(9, 74, 7), // "ClipPic"
QT_MOC_LITERAL(10, 82, 6) // "PinPic"

    },
    "TransparentMask\0FinishShot\0\0rect\0"
    "ScreenShotStart\0ShowPic\0pic\0SavePic\0"
    "path\0ClipPic\0PinPic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransparentMask[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   48,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,
       9,    0,   54,    2, 0x08 /* Private */,
      10,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QRect,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QPixmap,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TransparentMask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TransparentMask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FinishShot((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 1: _t->ScreenShotStart(); break;
        case 2: _t->ShowPic((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 3: _t->SavePic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->ClipPic(); break;
        case 5: _t->PinPic(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TransparentMask::*)(QRect );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TransparentMask::FinishShot)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TransparentMask::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TransparentMask::ScreenShotStart)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TransparentMask::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TransparentMask.data,
    qt_meta_data_TransparentMask,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TransparentMask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransparentMask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TransparentMask.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TransparentMask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TransparentMask::FinishShot(QRect _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TransparentMask::ScreenShotStart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
