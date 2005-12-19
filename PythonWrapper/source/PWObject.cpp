#include "PWObject.h"
#include "PWHandler.h"
#include "PWExceptions.h"
#include "PWDict.h"

using namespace pw;

Object::Object(ReferenceHandler &ref)
: mPtr(ref.getPtr())
{
    assert(mPtr);
    ref.contained();
} // Object(ReferenceHandler &ref)


Object::Object(const Object &rhs)
: mPtr(rhs.borrowReference())
{
    assert(rhs.borrowReference());
    Py_INCREF(mPtr);
} // Object(const Object &)


Object::~Object()
{
    Py_DECREF(mPtr);
} // ~Object()


Object::Object()
: mPtr(Py_None)
{
    Py_INCREF(Py_None);
}


Object &Object::operator=(const Object &rhs)
{
    assert(rhs.borrowReference());

    // this if takes care of the case when the pointer is the same; if we
    // did not do this check the following code below would bomb if
    // mPtr == rhs.mPtr and the refcount was at 1
    if (mPtr != rhs.borrowReference())
    {
        // mPtr could be 0 if we called this from the copy constructor
        Py_DECREF(mPtr);

        mPtr = rhs.borrowReference();
        Py_INCREF(mPtr);
    } // if

    return *this;
} // operator=


int Object::length() const
{
    return PyObject_Size(mPtr);
} // length()


Object Object::getAttr(const Object &attr) const
{
    return Object(NewReference(PyObject_GetAttr(mPtr, attr.borrowReference())));
}


void Object::setAttr(const Object &attr, const Object &value)
{
    PyObject_SetAttr(mPtr, attr.borrowReference(), value.borrowReference());
    PW_PyExcept_Check("Object::setAttr");
}


void Object::delAttr(const Object &attr)
{
    bool toReturn = PyObject_DelAttr(mPtr, attr.borrowReference()) != -1;
    PW_PyExcept_Check("Object::delAttr");
}


Object Object::getAttr(const String &attr) const
{
    return Object(NewReference(PyObject_GetAttrString(mPtr, (char *)attr.c_str())));
}


void Object::setAttr(const String &attr, const Object &value)
{
    PyObject_SetAttrString(mPtr, (char *)attr.c_str(), value.borrowReference());
}


void Object::delAttr(const String &attr)
{
    PyObject_DelAttrString(mPtr, (char *)attr.c_str());
}


Object Object::operator()()
{
    return Object(NewReference(PyObject_CallObject(mPtr, 0)));
}


Object Object::operator()(const Object &args)
{
    PyObject *toReturn = 0;

    if (PyTuple_Check(args.borrowReference()))
        toReturn = PyObject_CallObject(mPtr, args.borrowReference());
    else
    {
        PyObject *targs = PyTuple_New(1);
        PyTuple_SET_ITEM(targs, 0, args.newReference());
        toReturn = PyObject_CallObject(mPtr, targs);
        Py_DECREF(targs);
    }

    return NewReference(toReturn);
}


Object Object::operator()(const Object &args, const Dict &namedArgs)
{
    PyObject *toReturn = 0;

    if (PyTuple_Check(args.borrowReference()))
        toReturn = PyObject_Call(mPtr, args.borrowReference(), namedArgs.borrowReference());
    else
    {
        PyObject *targs = PyTuple_New(1);
        PyTuple_SET_ITEM(targs, 0, args.newReference());
        toReturn = PyObject_Call(mPtr, targs, namedArgs.borrowReference());
        Py_DECREF(targs);
    }

    return NewReference(toReturn);
}
