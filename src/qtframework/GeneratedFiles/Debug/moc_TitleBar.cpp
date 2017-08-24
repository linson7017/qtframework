/****************************************************************************
** Meta object code from reading C++ file 'TitleBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UIs/TitleBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TitleBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TitleBar_t {
    QByteArrayData data[8];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TitleBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TitleBar_t qt_meta_stringdata_TitleBar = {
    {
QT_MOC_LITERAL(0, 0, 8), // "TitleBar"
QT_MOC_LITERAL(1, 9, 21), // "minimizeButtonClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 21), // "maximizeButtonClicked"
QT_MOC_LITERAL(4, 54, 18), // "closeButtonClicked"
QT_MOC_LITERAL(5, 73, 20), // "minimizeParentWidget"
QT_MOC_LITERAL(6, 94, 20), // "maximizeParentWidget"
QT_MOC_LITERAL(7, 115, 17) // "closeParentWidget"

    },
    "TitleBar\0minimizeButtonClicked\0\0"
    "maximizeButtonClicked\0closeButtonClicked\0"
    "minimizeParentWidget\0maximizeParentWidget\0"
    "closeParentWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TitleBar[] = {

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
       5,    0,   47,    2, 0x09 /* Protected */,
       6,    0,   48,    2, 0x09 /* Protected */,
       7,    0,   49,    2, 0x09 /* Protected */,

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

void TitleBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TitleBar *_t = static_cast<TitleBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->minimizeButtonClicked(); break;
        case 1: _t->maximizeButtonClicked(); break;
        case 2: _t->closeButtonClicked(); break;
        case 3: _t->minimizeParentWidget(); break;
        case 4: _t->maximizeParentWidget(); break;
        case 5: _t->closeParentWidget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TitleBar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleBar::minimizeButtonClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TitleBar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleBar::maximizeButtonClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TitleBar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TitleBar::closeButtonClicked)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TitleBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TitleBar.data,
      qt_meta_data_TitleBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TitleBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TitleBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TitleBar.stringdata0))
        return static_cast<void*>(const_cast< TitleBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int TitleBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TitleBar::minimizeButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TitleBar::maximizeButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TitleBar::closeButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
