/****************************************************************************
** Meta object code from reading C++ file 'componentcontainer.h'
**
** Created: Sat Apr 11 23:57:19 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../componentcontainer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'componentcontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PDS__ComponentContainer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,
      46,   24,   24,   24, 0x05,
      60,   24,   24,   24, 0x05,
      74,   24,   24,   24, 0x05,
      95,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
     116,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PDS__ComponentContainer[] = {
    "PDS::ComponentContainer\0\0beforeExecution(int)\0"
    "executed(int)\0finished(int)\0"
    "positionChanged(int)\0progressChanged(int)\0"
    "somethingFinishedSlot()\0"
};

const QMetaObject PDS::ComponentContainer::staticMetaObject = {
    { &ProtocolComponent::staticMetaObject, qt_meta_stringdata_PDS__ComponentContainer,
      qt_meta_data_PDS__ComponentContainer, 0 }
};

const QMetaObject *PDS::ComponentContainer::metaObject() const
{
    return &staticMetaObject;
}

void *PDS::ComponentContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PDS__ComponentContainer))
        return static_cast<void*>(const_cast< ComponentContainer*>(this));
    return ProtocolComponent::qt_metacast(_clname);
}

int PDS::ComponentContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProtocolComponent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: beforeExecution((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: executed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: positionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: progressChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: somethingFinishedSlot(); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PDS::ComponentContainer::beforeExecution(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PDS::ComponentContainer::executed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PDS::ComponentContainer::finished(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PDS::ComponentContainer::positionChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PDS::ComponentContainer::progressChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
