/****************************************************************************
** Meta object code from reading C++ file 'Viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Enki__ViewerWidget_t {
    QByteArrayData data[33];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Enki__ViewerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Enki__ViewerWidget_t qt_meta_stringdata_Enki__ViewerWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "Enki::ViewerWidget"
QT_MOC_LITERAL(1, 19, 9), // "hideGraph"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "updateGraph"
QT_MOC_LITERAL(4, 42, 5), // "iters"
QT_MOC_LITERAL(5, 48, 7), // "anlStep"
QT_MOC_LITERAL(6, 56, 9), // "setCamera"
QT_MOC_LITERAL(7, 66, 3), // "pos"
QT_MOC_LITERAL(8, 70, 8), // "altitude"
QT_MOC_LITERAL(9, 79, 3), // "yaw"
QT_MOC_LITERAL(10, 83, 5), // "pitch"
QT_MOC_LITERAL(11, 89, 1), // "x"
QT_MOC_LITERAL(12, 91, 1), // "y"
QT_MOC_LITERAL(13, 93, 13), // "setWallHeight"
QT_MOC_LITERAL(14, 107, 12), // "_wallsHeight"
QT_MOC_LITERAL(15, 120, 27), // "setManagedObjectsAliasesMap"
QT_MOC_LITERAL(16, 148, 24), // "ManagedObjectsAliasesMap"
QT_MOC_LITERAL(17, 173, 3), // "map"
QT_MOC_LITERAL(18, 177, 17), // "centerCameraWorld"
QT_MOC_LITERAL(19, 195, 17), // "restartDumpFrames"
QT_MOC_LITERAL(20, 213, 13), // "setDumpFrames"
QT_MOC_LITERAL(21, 227, 6), // "doDump"
QT_MOC_LITERAL(22, 234, 11), // "setTracking"
QT_MOC_LITERAL(23, 246, 7), // "doTrack"
QT_MOC_LITERAL(24, 254, 14), // "toggleTracking"
QT_MOC_LITERAL(25, 269, 14), // "addInfoMessage"
QT_MOC_LITERAL(26, 284, 7), // "message"
QT_MOC_LITERAL(27, 292, 11), // "persistance"
QT_MOC_LITERAL(28, 304, 5), // "color"
QT_MOC_LITERAL(29, 310, 4), // "link"
QT_MOC_LITERAL(30, 315, 8), // "showHelp"
QT_MOC_LITERAL(31, 324, 8), // "speedSim"
QT_MOC_LITERAL(32, 333, 10) // "timerSpeed"

    },
    "Enki::ViewerWidget\0hideGraph\0\0updateGraph\0"
    "iters\0anlStep\0setCamera\0pos\0altitude\0"
    "yaw\0pitch\0x\0y\0setWallHeight\0_wallsHeight\0"
    "setManagedObjectsAliasesMap\0"
    "ManagedObjectsAliasesMap\0map\0"
    "centerCameraWorld\0restartDumpFrames\0"
    "setDumpFrames\0doDump\0setTracking\0"
    "doTrack\0toggleTracking\0addInfoMessage\0"
    "message\0persistance\0color\0link\0showHelp\0"
    "speedSim\0timerSpeed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Enki__ViewerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    1,  105,    2, 0x06 /* Public */,
       5,    0,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    4,  109,    2, 0x0a /* Public */,
       6,    5,  118,    2, 0x0a /* Public */,
      13,    1,  129,    2, 0x0a /* Public */,
      15,    1,  132,    2, 0x0a /* Public */,
      18,    0,  135,    2, 0x0a /* Public */,
      19,    0,  136,    2, 0x0a /* Public */,
      20,    1,  137,    2, 0x0a /* Public */,
      22,    1,  140,    2, 0x0a /* Public */,
      24,    0,  143,    2, 0x0a /* Public */,
      25,    4,  144,    2, 0x0a /* Public */,
      25,    3,  153,    2, 0x2a /* Public | MethodCloned */,
      25,    2,  160,    2, 0x2a /* Public | MethodCloned */,
      25,    1,  165,    2, 0x2a /* Public | MethodCloned */,
      30,    0,  168,    2, 0x0a /* Public */,
      31,    1,  169,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QPointF, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   11,   12,    8,    9,   10,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::QColor, QMetaType::QUrl,   26,   27,   28,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::QColor,   26,   27,   28,
    QMetaType::Void, QMetaType::QString, QMetaType::Double,   26,   27,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,

       0        // eod
};

void Enki::ViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewerWidget *_t = static_cast<ViewerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideGraph(); break;
        case 1: _t->updateGraph((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->anlStep(); break;
        case 3: _t->setCamera((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 4: _t->setCamera((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 5: _t->setWallHeight((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setManagedObjectsAliasesMap((*reinterpret_cast< ManagedObjectsAliasesMap(*)>(_a[1]))); break;
        case 7: _t->centerCameraWorld(); break;
        case 8: _t->restartDumpFrames(); break;
        case 9: _t->setDumpFrames((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setTracking((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->toggleTracking(); break;
        case 12: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< const QColor(*)>(_a[3])),(*reinterpret_cast< const QUrl(*)>(_a[4]))); break;
        case 13: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< const QColor(*)>(_a[3]))); break;
        case 14: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 15: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->showHelp(); break;
        case 17: _t->speedSim((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ViewerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewerWidget::hideGraph)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ViewerWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewerWidget::updateGraph)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ViewerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewerWidget::anlStep)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Enki::ViewerWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Enki__ViewerWidget.data,
      qt_meta_data_Enki__ViewerWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Enki::ViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enki::ViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Enki__ViewerWidget.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int Enki::ViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void Enki::ViewerWidget::hideGraph()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Enki::ViewerWidget::updateGraph(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Enki::ViewerWidget::anlStep()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_Enki__Settings_t {
    QByteArrayData data[4];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Enki__Settings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Enki__Settings_t qt_meta_stringdata_Enki__Settings = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Enki::Settings"
QT_MOC_LITERAL(1, 15, 15), // "settingsChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3) // "arg"

    },
    "Enki::Settings\0settingsChanged\0\0arg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Enki__Settings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Enki::Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Settings *_t = static_cast<Settings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingsChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Settings::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::settingsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Enki::Settings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Enki__Settings.data,
      qt_meta_data_Enki__Settings,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Enki::Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enki::Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Enki__Settings.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Enki::Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Enki::Settings::settingsChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Enki__QAnalytics_t {
    QByteArrayData data[14];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Enki__QAnalytics_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Enki__QAnalytics_t qt_meta_stringdata_Enki__QAnalytics = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Enki::QAnalytics"
QT_MOC_LITERAL(1, 17, 7), // "newTopQ"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "iter"
QT_MOC_LITERAL(4, 31, 7), // "quality"
QT_MOC_LITERAL(5, 39, 7), // "newAvgQ"
QT_MOC_LITERAL(6, 47, 11), // "getListVars"
QT_MOC_LITERAL(7, 59, 12), // "QStringList*"
QT_MOC_LITERAL(8, 72, 10), // "getListVar"
QT_MOC_LITERAL(9, 83, 22), // "std::vector<roboStat>*"
QT_MOC_LITERAL(10, 106, 11), // "std::string"
QT_MOC_LITERAL(11, 118, 4), // "name"
QT_MOC_LITERAL(12, 123, 6), // "evolve"
QT_MOC_LITERAL(13, 130, 12) // "checkVarList"

    },
    "Enki::QAnalytics\0newTopQ\0\0iter\0quality\0"
    "newAvgQ\0getListVars\0QStringList*\0"
    "getListVar\0std::vector<roboStat>*\0"
    "std::string\0name\0evolve\0checkVarList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Enki__QAnalytics[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   54,    2, 0x0a /* Public */,
       8,    1,   55,    2, 0x0a /* Public */,
      12,    0,   58,    2, 0x0a /* Public */,
      13,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,

 // slots: parameters
    0x80000000 | 7,
    0x80000000 | 9, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Enki::QAnalytics::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QAnalytics *_t = static_cast<QAnalytics *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newTopQ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->newAvgQ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: { QStringList* _r = _t->getListVars();
            if (_a[0]) *reinterpret_cast< QStringList**>(_a[0]) = std::move(_r); }  break;
        case 3: { std::vector<roboStat>* _r = _t->getListVar((*reinterpret_cast< const std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::vector<roboStat>**>(_a[0]) = std::move(_r); }  break;
        case 4: _t->evolve(); break;
        case 5: _t->checkVarList(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QAnalytics::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QAnalytics::newTopQ)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QAnalytics::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QAnalytics::newAvgQ)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Enki::QAnalytics::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Enki__QAnalytics.data,
      qt_meta_data_Enki__QAnalytics,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Enki::QAnalytics::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enki::QAnalytics::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Enki__QAnalytics.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Enki::QAnalytics::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Enki::QAnalytics::newTopQ(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Enki::QAnalytics::newAvgQ(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_Enki__eChart_t {
    QByteArrayData data[7];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Enki__eChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Enki__eChart_t qt_meta_stringdata_Enki__eChart = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Enki::eChart"
QT_MOC_LITERAL(1, 13, 8), // "addPoint"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 2), // "it"
QT_MOC_LITERAL(4, 26, 7), // "quality"
QT_MOC_LITERAL(5, 34, 10), // "zoomAction"
QT_MOC_LITERAL(6, 45, 7) // "enabled"

    },
    "Enki::eChart\0addPoint\0\0it\0quality\0"
    "zoomAction\0enabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Enki__eChart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a /* Public */,
       5,    1,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,

       0        // eod
};

void Enki::eChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        eChart *_t = static_cast<eChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addPoint((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->zoomAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Enki::eChart::staticMetaObject = {
    { &QChart::staticMetaObject, qt_meta_stringdata_Enki__eChart.data,
      qt_meta_data_Enki__eChart,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Enki::eChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enki::eChart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Enki__eChart.stringdata0))
        return static_cast<void*>(this);
    return QChart::qt_metacast(_clname);
}

int Enki::eChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChart::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_Enki__viewerChart_t {
    QByteArrayData data[12];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Enki__viewerChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Enki__viewerChart_t qt_meta_stringdata_Enki__viewerChart = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Enki::viewerChart"
QT_MOC_LITERAL(1, 18, 10), // "zoomSignal"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "act"
QT_MOC_LITERAL(4, 34, 12), // "changeSignal"
QT_MOC_LITERAL(5, 47, 6), // "change"
QT_MOC_LITERAL(6, 54, 19), // "const std::string[]"
QT_MOC_LITERAL(7, 74, 6), // "params"
QT_MOC_LITERAL(8, 81, 22), // "std::vector<roboStat>*"
QT_MOC_LITERAL(9, 104, 5), // "lista"
QT_MOC_LITERAL(10, 110, 8), // "ecUpdate"
QT_MOC_LITERAL(11, 119, 2) // "it"

    },
    "Enki::viewerChart\0zoomSignal\0\0act\0"
    "changeSignal\0change\0const std::string[]\0"
    "params\0std::vector<roboStat>*\0lista\0"
    "ecUpdate\0it"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Enki__viewerChart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   38,    2, 0x0a /* Public */,
      10,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void Enki::viewerChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        viewerChart *_t = static_cast<viewerChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->zoomSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeSignal(); break;
        case 2: _t->change((*reinterpret_cast< const std::string(*)[]>(_a[1])),(*reinterpret_cast< std::vector<roboStat>*(*)>(_a[2]))); break;
        case 3: _t->ecUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (viewerChart::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&viewerChart::zoomSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (viewerChart::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&viewerChart::changeSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Enki::viewerChart::staticMetaObject = {
    { &QChartView::staticMetaObject, qt_meta_stringdata_Enki__viewerChart.data,
      qt_meta_data_Enki__viewerChart,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Enki::viewerChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enki::viewerChart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Enki__viewerChart.stringdata0))
        return static_cast<void*>(this);
    return QChartView::qt_metacast(_clname);
}

int Enki::viewerChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChartView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Enki::viewerChart::zoomSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Enki::viewerChart::changeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_Enki__ViewerWindow_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Enki__ViewerWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Enki__ViewerWindow_t qt_meta_stringdata_Enki__ViewerWindow = {
    {
QT_MOC_LITERAL(0, 0, 18), // "Enki::ViewerWindow"
QT_MOC_LITERAL(1, 19, 9), // "hideGraph"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "manageSettings"
QT_MOC_LITERAL(4, 45, 12), // "manageGraphs"
QT_MOC_LITERAL(5, 58, 12), // "getVariables"
QT_MOC_LITERAL(6, 71, 12) // "QStringList*"

    },
    "Enki::ViewerWindow\0hideGraph\0\0"
    "manageSettings\0manageGraphs\0getVariables\0"
    "QStringList*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Enki__ViewerWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       4,    0,   38,    2, 0x0a /* Public */,
       5,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    0x80000000 | 6,

       0        // eod
};

void Enki::ViewerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewerWindow *_t = static_cast<ViewerWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideGraph(); break;
        case 1: _t->manageSettings((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->manageGraphs(); break;
        case 3: { QStringList* _r = _t->getVariables();
            if (_a[0]) *reinterpret_cast< QStringList**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Enki::ViewerWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Enki__ViewerWindow.data,
      qt_meta_data_Enki__ViewerWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Enki::ViewerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enki::ViewerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Enki__ViewerWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Enki::ViewerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
