/****************************************************************************
** Meta object code from reading C++ file 'GraphicButtonGroup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UIs/GraphicButtonGroup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphicButtonGroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphicButtonGroup_t {
    QByteArrayData data[8];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicButtonGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicButtonGroup_t qt_meta_stringdata_GraphicButtonGroup = {
    {
QT_MOC_LITERAL(0, 0, 18), // "GraphicButtonGroup"
QT_MOC_LITERAL(1, 19, 9), // "emit_fold"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "emit_unfold"
QT_MOC_LITERAL(4, 42, 11), // "emit_packup"
QT_MOC_LITERAL(5, 54, 4), // "fold"
QT_MOC_LITERAL(6, 59, 6), // "unfold"
QT_MOC_LITERAL(7, 66, 6) // "packup"

    },
    "GraphicButtonGroup\0emit_fold\0\0emit_unfold\0"
    "emit_packup\0fold\0unfold\0packup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicButtonGroup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphicButtonGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphicButtonGroup *_t = static_cast<GraphicButtonGroup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emit_fold(); break;
        case 1: _t->emit_unfold(); break;
        case 2: _t->emit_packup(); break;
        case 3: _t->fold(); break;
        case 4: _t->unfold(); break;
        case 5: _t->packup(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphicButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicButtonGroup::emit_fold)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GraphicButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicButtonGroup::emit_unfold)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GraphicButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicButtonGroup::emit_packup)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GraphicButtonGroup::staticMetaObject = {
    { &QGraphicsWidget::staticMetaObject, qt_meta_stringdata_GraphicButtonGroup.data,
      qt_meta_data_GraphicButtonGroup,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphicButtonGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicButtonGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicButtonGroup.stringdata0))
        return static_cast<void*>(const_cast< GraphicButtonGroup*>(this));
    return QGraphicsWidget::qt_metacast(_clname);
}

int GraphicButtonGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsWidget::qt_metacall(_c, _id, _a);
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
void GraphicButtonGroup::emit_fold()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void GraphicButtonGroup::emit_unfold()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void GraphicButtonGroup::emit_packup()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
