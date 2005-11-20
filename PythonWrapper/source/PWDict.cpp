#include "PWDict.h"
#include "PWHandler.h"
#include "PWList.h"
#include "PWExceptions.h"
#include "PWString.h"

using namespace pw;

Dict::Dict()
: Object(NewReference(PyDict_New()))
{
}

Dict::Dict(const Dict &copy)
: Object(BorrowedReference(copy.borrowReference()))
{
}


Dict::Dict(const Object &obj)
: Object(BorrowedReference(obj.borrowReference()))
{
    if (! PyDict_Check(mPtr))
    {
        Py_DECREF(mPtr);
        PYTHON_EXCEPTION_THROW;
    }
}


Dict::~Dict()
{
}


Dict &Dict::operator=(const Dict &rhs)
{
    Py_DECREF(mPtr);
    mPtr = PyDict_Copy(rhs.borrowReference());

    return *this;
}


bool Dict::contains(const Object &key) const
{
    bool toReturn = PyDict_Contains(mPtr, key.borrowReference()) == 1;
    
    PYTHON_EXCEPTION_CHECK;
    return toReturn;
}


void Dict::setItem(const Object &key, const Object &value)
{
    PyDict_SetItem(mPtr, key.borrowReference(), value.borrowReference());
    PYTHON_EXCEPTION_CHECK;
}


Object Dict::getItem(const Object &key) const
{
    PyObject *toReturn = PyDict_GetItem(mPtr, key.borrowReference());
    if (! toReturn)
        PYTHON_EXCEPTION_THROW;

    return Object(BorrowedReference(toReturn));
}


void Dict::delItem(const Object &key)
{
    PyObject_DelItem(mPtr, key.borrowReference());
    PYTHON_EXCEPTION_CHECK;
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
    if (! toReturn)
        PYTHON_EXCEPTION_THROW;

    return SequenceEntry<Dict, Object>(BorrowedReference(toReturn), *this, key);
}

Dict::DictEntry Dict::operator[](char *key)
{
    PyObject *toReturn = PyDict_GetItemString(mPtr, key);
    if (! toReturn)
        PYTHON_EXCEPTION_THROW;

    return SequenceEntry<Dict, Object>(BorrowedReference(toReturn), *this, String(key));
}


void Dict::setItem(char *key, const Object &value)
{
    PyDict_SetItemString(mPtr, key, value.borrowReference());
    PYTHON_EXCEPTION_CHECK;
}


Object Dict::getItem(char *key) const
{
    PyObject *toReturn = PyDict_GetItemString(mPtr, key);
    if (! toReturn)
        PYTHON_EXCEPTION_THROW;

    return Object(BorrowedReference(toReturn));
}

void Dict::delItem(char *key)
{
    PyObject_DelItemString(mPtr, key);
    PYTHON_EXCEPTION_CHECK;
}
