/****************************************************************************
** Meta object code from reading C++ file 'protocolsegment.h'
**
** Created: Mon Apr 13 11:53:52 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../protocolsegment.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocolsegment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PDS__ProtocolSegment[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      41,   21,   21,   21, 0x05,
      59,   21,   21,   21, 0x05,
      80,   21,   21,   21, 0x05,
      92,   21,   21,   21, 0x05,
     138,   21,   21,   21, 0x05,
     187,   21,   21,   21, 0x05,
     225,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     248,   21,   21,   21, 0x08,
     264,   21,   21,   21, 0x08,
     280,   21,   21,   21, 0x08,
     295,   21,   21,   21, 0x08,
     323,  321,   21,   21, 0x08,
     376,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PDS__ProtocolSegment[] = {
    "PDS::ProtocolSegment\0\0beforeConnecting()\0"
    "socketConnected()\0socketDisconnected()\0"
    "hostFound()\0connectionError(QAbstractSocket::SocketError)\0"
    "socketStateChanged(QAbstractSocket::SocketState)\0"
    "readChannelFinished(ProtocolSegment*)\0"
    "hintNotFound(QString&)\0connectedSlot()\0"
    "encryptedSlot()\0dataReceived()\0"
    "readChannelFinishedSlot()\0s\0"
    "socketStateChangedSlot(QAbstractSocket::SocketState)\0"
    "disconnectedSlot()\0"
};

const QMetaObject PDS::ProtocolSegment::staticMetaObject = {
    { &ComponentContainer::staticMetaObject, qt_meta_stringdata_PDS__ProtocolSegment,
      qt_meta_data_PDS__ProtocolSegment, 0 }
};

const QMetaObject *PDS::ProtocolSegment::metaObject() const
{
    return &staticMetaObject;
}

void *PDS::ProtocolSegment::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PDS__ProtocolSegment))
        return static_cast<void*>(const_cast< ProtocolSegment*>(this));
    return ComponentContainer::qt_metacast(_clname);
}

int PDS::ProtocolSegment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ComponentContainer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: beforeConnecting(); break;
        case 1: socketConnected(); break;
        case 2: socketDisconnected(); break;
        case 3: hostFound(); break;
        case 4: connectionError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: socketStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 6: readChannelFinished((*reinterpret_cast< ProtocolSegment*(*)>(_a[1]))); break;
        case 7: hintNotFound((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: connectedSlot(); break;
        case 9: encryptedSlot(); break;
        case 10: dataReceived(); break;
        case 11: readChannelFinishedSlot(); break;
        case 12: socketStateChangedSlot((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 13: disconnectedSlot(); break;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void PDS::ProtocolSegment::beforeConnecting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PDS::ProtocolSegment::socketConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PDS::ProtocolSegment::socketDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PDS::ProtocolSegment::hostFound()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void PDS::ProtocolSegment::connectionError(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PDS::ProtocolSegment::socketStateChanged(QAbstractSocket::SocketState _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PDS::ProtocolSegment::readChannelFinished(ProtocolSegment * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PDS::ProtocolSegment::hintNotFound(QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
