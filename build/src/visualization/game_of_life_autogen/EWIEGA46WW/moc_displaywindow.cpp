/****************************************************************************
** Meta object code from reading C++ file 'displaywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/visualization/displaywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'displaywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DisplayWindow_t {
    QByteArrayData data[21];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisplayWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisplayWindow_t qt_meta_stringdata_DisplayWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DisplayWindow"
QT_MOC_LITERAL(1, 14, 14), // "resetBoardZoom"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "resetAllCells"
QT_MOC_LITERAL(4, 44, 12), // "boardChanged"
QT_MOC_LITERAL(5, 57, 21), // "gameBoard::GameBoard*"
QT_MOC_LITERAL(6, 79, 5), // "board"
QT_MOC_LITERAL(7, 85, 12), // "newGameBoard"
QT_MOC_LITERAL(8, 98, 7), // "exitApp"
QT_MOC_LITERAL(9, 106, 11), // "stepForward"
QT_MOC_LITERAL(10, 118, 3), // "run"
QT_MOC_LITERAL(11, 122, 4), // "stop"
QT_MOC_LITERAL(12, 127, 13), // "increaseSpeed"
QT_MOC_LITERAL(13, 141, 13), // "decreaseSpeed"
QT_MOC_LITERAL(14, 155, 10), // "resetSpeed"
QT_MOC_LITERAL(15, 166, 14), // "updateCellInfo"
QT_MOC_LITERAL(16, 181, 1), // "x"
QT_MOC_LITERAL(17, 183, 1), // "y"
QT_MOC_LITERAL(18, 185, 23), // "increaseBoardGeneration"
QT_MOC_LITERAL(19, 209, 13), // "setCoordinate"
QT_MOC_LITERAL(20, 223, 16) // "removeCoordinate"

    },
    "DisplayWindow\0resetBoardZoom\0\0"
    "resetAllCells\0boardChanged\0"
    "gameBoard::GameBoard*\0board\0newGameBoard\0"
    "exitApp\0stepForward\0run\0stop\0increaseSpeed\0"
    "decreaseSpeed\0resetSpeed\0updateCellInfo\0"
    "x\0y\0increaseBoardGeneration\0setCoordinate\0"
    "removeCoordinate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisplayWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    1,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    2,  102,    2, 0x08 /* Private */,
      18,    0,  107,    2, 0x08 /* Private */,
      19,    2,  108,    2, 0x08 /* Private */,
      20,    0,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,
    QMetaType::Void,

       0        // eod
};

void DisplayWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DisplayWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetBoardZoom(); break;
        case 1: _t->resetAllCells(); break;
        case 2: _t->boardChanged((*reinterpret_cast< gameBoard::GameBoard*(*)>(_a[1]))); break;
        case 3: _t->newGameBoard(); break;
        case 4: _t->exitApp(); break;
        case 5: _t->stepForward(); break;
        case 6: _t->run(); break;
        case 7: _t->stop(); break;
        case 8: _t->increaseSpeed(); break;
        case 9: _t->decreaseSpeed(); break;
        case 10: _t->resetSpeed(); break;
        case 11: _t->updateCellInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->increaseBoardGeneration(); break;
        case 13: _t->setCoordinate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->removeCoordinate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DisplayWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DisplayWindow::resetBoardZoom)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DisplayWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DisplayWindow::resetAllCells)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DisplayWindow::*)(gameBoard::GameBoard * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DisplayWindow::boardChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DisplayWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_DisplayWindow.data,
    qt_meta_data_DisplayWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DisplayWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisplayWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int DisplayWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void DisplayWindow::resetBoardZoom()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DisplayWindow::resetAllCells()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DisplayWindow::boardChanged(gameBoard::GameBoard * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
