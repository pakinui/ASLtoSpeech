/****************************************************************************
** Meta object code from reading C++ file 'camera.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../testingApp/camera.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCameraENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCameraENDCLASS = QtMocHelpers::stringData(
    "Camera",
    "displayCameraError",
    "",
    "updateCameraDevice",
    "QAction*",
    "action",
    "updateCameras",
    "setCamera",
    "QCameraDevice",
    "cameraDevice",
    "updateCameraActive",
    "active",
    "startCamera",
    "stopCamera"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCameraENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[7];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[9];
    char stringdata5[7];
    char stringdata6[14];
    char stringdata7[10];
    char stringdata8[14];
    char stringdata9[13];
    char stringdata10[19];
    char stringdata11[7];
    char stringdata12[12];
    char stringdata13[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCameraENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCameraENDCLASS_t qt_meta_stringdata_CLASSCameraENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Camera"
        QT_MOC_LITERAL(7, 18),  // "displayCameraError"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 18),  // "updateCameraDevice"
        QT_MOC_LITERAL(46, 8),  // "QAction*"
        QT_MOC_LITERAL(55, 6),  // "action"
        QT_MOC_LITERAL(62, 13),  // "updateCameras"
        QT_MOC_LITERAL(76, 9),  // "setCamera"
        QT_MOC_LITERAL(86, 13),  // "QCameraDevice"
        QT_MOC_LITERAL(100, 12),  // "cameraDevice"
        QT_MOC_LITERAL(113, 18),  // "updateCameraActive"
        QT_MOC_LITERAL(132, 6),  // "active"
        QT_MOC_LITERAL(139, 11),  // "startCamera"
        QT_MOC_LITERAL(151, 10)   // "stopCamera"
    },
    "Camera",
    "displayCameraError",
    "",
    "updateCameraDevice",
    "QAction*",
    "action",
    "updateCameras",
    "setCamera",
    "QCameraDevice",
    "cameraDevice",
    "updateCameraActive",
    "active",
    "startCamera",
    "stopCamera"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCameraENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    1,   57,    2, 0x08,    2 /* Private */,
       6,    0,   60,    2, 0x08,    4 /* Private */,
       7,    1,   61,    2, 0x08,    5 /* Private */,
      10,    1,   64,    2, 0x08,    7 /* Private */,
      12,    0,   67,    2, 0x08,    9 /* Private */,
      13,    0,   68,    2, 0x08,   10 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Camera::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSCameraENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCameraENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCameraENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Camera, std::true_type>,
        // method 'displayCameraError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateCameraDevice'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAction *, std::false_type>,
        // method 'updateCameras'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCameraDevice &, std::false_type>,
        // method 'updateCameraActive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'startCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Camera *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->displayCameraError(); break;
        case 1: _t->updateCameraDevice((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 2: _t->updateCameras(); break;
        case 3: _t->setCamera((*reinterpret_cast< std::add_pointer_t<QCameraDevice>>(_a[1]))); break;
        case 4: _t->updateCameraActive((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->startCamera(); break;
        case 6: _t->stopCamera(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *Camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Camera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCameraENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
