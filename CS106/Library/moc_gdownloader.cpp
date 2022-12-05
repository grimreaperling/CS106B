/****************************************************************************
** Meta object code from reading C++ file 'gdownloader.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "graphics/gdownloader.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gdownloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_GDownloader_t {
    uint offsetsAndSizes[32];
    char stringdata0[12];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[18];
    char stringdata5[28];
    char stringdata6[12];
    char stringdata7[19];
    char stringdata8[12];
    char stringdata9[7];
    char stringdata10[9];
    char stringdata11[13];
    char stringdata12[15];
    char stringdata13[17];
    char stringdata14[15];
    char stringdata15[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GDownloader_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_GDownloader_t qt_meta_stringdata_GDownloader = {
    {
        QT_MOC_LITERAL(0, 11),  // "GDownloader"
        QT_MOC_LITERAL(12, 10),  // "downloaded"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 16),  // "downloadInternal"
        QT_MOC_LITERAL(41, 17),  // "fileDownloadError"
        QT_MOC_LITERAL(59, 27),  // "QNetworkReply::NetworkError"
        QT_MOC_LITERAL(87, 11),  // "reportNoSSL"
        QT_MOC_LITERAL(99, 18),  // "saveDownloadedData"
        QT_MOC_LITERAL(118, 11),  // "std::string"
        QT_MOC_LITERAL(130, 6),  // "member"
        QT_MOC_LITERAL(137, 8),  // "filename"
        QT_MOC_LITERAL(146, 12),  // "sslErrorsNam"
        QT_MOC_LITERAL(159, 14),  // "QNetworkReply*"
        QT_MOC_LITERAL(174, 16),  // "QList<QSslError>"
        QT_MOC_LITERAL(191, 14),  // "sslErrorsReply"
        QT_MOC_LITERAL(206, 15)   // "waitForDownload"
    },
    "GDownloader",
    "downloaded",
    "",
    "downloadInternal",
    "fileDownloadError",
    "QNetworkReply::NetworkError",
    "reportNoSSL",
    "saveDownloadedData",
    "std::string",
    "member",
    "filename",
    "sslErrorsNam",
    "QNetworkReply*",
    "QList<QSslError>",
    "sslErrorsReply",
    "waitForDownload"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_GDownloader[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    1,   70,    2, 0x08,    3 /* Private */,
       6,    0,   73,    2, 0x08,    5 /* Private */,
       7,    2,   74,    2, 0x08,    6 /* Private */,
       7,    1,   79,    2, 0x28,    9 /* Private | MethodCloned */,
      11,    2,   82,    2, 0x08,   11 /* Private */,
      14,    1,   87,    2, 0x08,   14 /* Private */,
      15,    0,   90,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 13,    2,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GDownloader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GDownloader.offsetsAndSizes,
    qt_meta_data_GDownloader,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_GDownloader_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GDownloader, std::true_type>,
        // method 'downloaded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'downloadInternal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fileDownloadError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply::NetworkError, std::false_type>,
        // method 'reportNoSSL'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveDownloadedData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        // method 'saveDownloadedData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        // method 'sslErrorsNam'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<QSslError>, std::false_type>,
        // method 'sslErrorsReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<QSslError>, std::false_type>,
        // method 'waitForDownload'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GDownloader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->downloaded(); break;
        case 1: _t->downloadInternal(); break;
        case 2: _t->fileDownloadError((*reinterpret_cast< std::add_pointer_t<QNetworkReply::NetworkError>>(_a[1]))); break;
        case 3: _t->reportNoSSL(); break;
        case 4: _t->saveDownloadedData((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2]))); break;
        case 5: _t->saveDownloadedData((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 6: _t->sslErrorsNam((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<QSslError>>>(_a[2]))); break;
        case 7: _t->sslErrorsReply((*reinterpret_cast< std::add_pointer_t<QList<QSslError>>>(_a[1]))); break;
        case 8: _t->waitForDownload(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply::NetworkError >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QSslError> >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GDownloader::*)();
            if (_t _q_method = &GDownloader::downloaded; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *GDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GDownloader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GDownloader::downloaded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
