/****************************************************************************
** Meta object code from reading C++ file 'protocolcomponent.h'
**
** Created: Sat Apr 11 22:56:32 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../protocolcomponent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocolcomponent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PDS__ProtocolComponent[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      60,   23,   23,   23, 0x05,
      78,   23,   23,   23, 0x05,
      89,   23,   23,   23, 0x05,
     118,   23,   23,   23, 0x05,
     129,   23,   23,   23, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PDS__ProtocolComponent[] = {
    "PDS::ProtocolComponent\0\0"
    "beforeExecution(ProtocolComponent*)\0"
    "beforeExecution()\0executed()\0"
    "executed(ProtocolComponent*)\0finished()\0"
    "finished(ProtocolComponent*)\0"
};

const QMetaObject PDS::ProtocolComponent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PDS__ProtocolComponent,
      qt_meta_data_PDS__ProtocolComponent, 0 }
};

const QMetaObject *PDS::ProtocolComponent::metaObject() const
{
    return &staticMetaObject;
}

void *PDS::ProtocolComponent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PDS__ProtocolComponent))
        return static_cast<void*>(const_cast< ProtocolComponent*>(this));
    return QObject::qt_metacast(_clname);
}

int PDS::ProtocolComponent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: beforeExecution((*reinterpret_cast< ProtocolComponent*(*)>(_a[1]))); break;
        case 1: beforeExecution(); break;
        case 2: executed(); break;
        case 3: executed((*reinterpret_cast< ProtocolComponent*(*)>(_a[1]))); break;
        case 4: finished(); break;
        case 5: finished((*reinterpret_cast< ProtocolComponent*(*)>(_a[1]))); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PDS::ProtocolComponent::beforeExecution(ProtocolComponent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PDS::ProtocolComponent::beforeExecution()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PDS::ProtocolComponent::executed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PDS::ProtocolComponent::executed(ProtocolComponent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PDS::ProtocolComponent::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void PDS::ProtocolComponent::finished(ProtocolComponent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
