#include "PWDict.h"
#include "PWHandler.h"
#include "PWList.h"
#include "PWExceptions.h"
#include "PWBuild.h"

using namespace pw;

Dict::Dict()
: Object(NewReference(PyDict_New()))
{
    if (! PyDict_Check(mPtr))
    {
        Py_DECREF(mPtr);
        PW_PyExcept("Dict::Dict()");
    }
}


Dict::Dict(const Object &obj)
: Object(BorrowedReference(obj.borrowReference()))
{
    if (! PyDict_Check(mPtr))
    {
        Py_DECREF(mPtr);
        PW_PyExcept("Dict::Dict(const Object &)");
    }
}


Dict::~Dict()
{
}


Dict Dict::copy() const
{
    return Dict(BorrowedReference(borrowReference()));
}


bool Dict::contains(const Object &key) const
{
    bool toReturn = PyDict_Contains(mPtr, key.borrowReference()) == 1;
    
    PW_PyExcept_Check("Dict::contains");
    return toReturn;
}


void Dict::setItem(const Object &key, const Object &value)
{
    PyDict_SetItem(mPtr, key.borrowReference(), value.borrowReference());
    PW_PyExcept_Check("Dict::setItem");
}


Object Dict::getItem(const Object &key) const
{
    PyObject *toReturn = PyDict_GetItem(mPtr, key.borrowReference());
    if (! toReturn)
        PW_PyExcept("Dict::getItem");

    return Object(BorrowedReference(toReturn));
}


void Dict::delItem(const Object &key)
{
    PyObject_DelItem(mPtr, key.borrowReference());
    PW_PyExcept_Check("Dict::delItem");
}


List Dict::items() const
{
    return List(NewReference(PyDict_Items(mPtr)));
}


List Dict::keys() const
{
    return List(NewReference(PyDict_Keys(mPtr)));
}


List Dict::values() const
{
    return List(NewReference(PyDict_Values(mPtr)));
}


Dict::DictEntry Dict::operator[](const Object &key)
{
    PyObject *toReturn = PyDict_GetItem(mPtr, key.borrowReference());
    if (toReturn)
        return SequenceEntry<Dict, Object>(BorrowedReference(toReturn), *this, key);

    PyErr_Clear();
    return SequenceEntry<Dict, Object>(BorrowedReference(Py_None), *this, key);
}

Dict::DictEntry Dict::operator[](const String &key)
{
    PyObject *toReturn = PyDict_GetItemString(mPtr, key.c_str());
    if (toReturn)
        return SequenceEntry<Dict, Object>(BorrowedReference(toReturn), *this, build(key.c_str()));

    PyErr_Clear();
    return SequenceEntry<Dict, Object>(BorrowedReference(Py_None), *this, build(key.c_str()));
}


void Dict::setItem(const String &key, const Object &value)
{
    PyDict_SetItemString(mPtr, key.c_str(), value.borrowReference());
    PW_PyExcept_Check("Dict::setItem");
}


Object Dict::getItem(const String &key) const
{
    PyObject *toReturn = PyDict_GetItemString(mPtr, key.c_str());
    if (! toReturn)
        PW_Except("Key " + key + " not found.", "Dict::getItem");

    return Object(BorrowedReference(toReturn));
}

void Dict::delItem(const String &key)
{
    PyObject_DelItemString(mPtr, (char *)key.c_str());
    PW_PyExcept_Check("Dict::delItem");
}


Dict Dict::copy()
{
    return Dict(NewReference(PyDict_Copy(mPtr)));
}
