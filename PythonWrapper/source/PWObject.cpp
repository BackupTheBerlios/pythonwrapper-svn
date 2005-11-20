#include "PWObject.h"
#include "PWHandler.h"
#include "PWExceptions.h"
#include "PWTuple.h"
#include "PWDict.h"

using namespace pw;

Object::Object(ReferenceHandler &ref)
: mPtr(ref.getPtr())
{
    assert(mPtr);
    ref.contained();
} // Object(ReferenceHandler &ref)


Object::Object(const Object &rhs)
: mPtr(rhs.mPtr)
{
    assert(rhs.mPtr);
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
    assert(rhs.mPtr);

    // this if takes care of the case when the pointer is the same; if we
    // did not do this check the following code below would bomb if
    // mPtr == rhs.mPtr and the refcount was at 1
    if (mPtr != rhs.mPtr)
    {
        // mPtr could be 0 if we called this from the copy constructor
        Py_DECREF(mPtr);

        mPtr = rhs.mPtr;
        Py_INCREF(mPtr);
    } // if

    return *this;
} // operator=


void Object::check(PyObject *ptr)
{
    if (!ptr)
    {
        PYTHON_EXCEPTION_CHECK;
        NULL_OBJECT_EXCEPTION_THROW;
    } // if
} // check(PyObject *)


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
    PYTHON_EXCEPTION_CHECK;
}


void Object::delAttr(const Object &attr)
{
    bool toReturn = PyObject_DelAttr(mPtr, attr.borrowReference()) != -1;
    PYTHON_EXCEPTION_CHECK;
}


Object Object::getAttr(char *attr) const
{
    return Object(NewReference(PyObject_GetAttrString(mPtr, attr)));
}


void Object::setAttr(char *attr, const Object &value)
{
    PyObject_SetAttrString(mPtr, attr, value.borrowReference());
}


void Object::delAttr(char *attr)
{
    PyObject_DelAttrString(mPtr, attr);
}


Object Object::operator()()
{
    return Object(NewReference(PyObject_CallObject(mPtr, 0)));
}


Object Object::operator()(const Tuple &args)
{
    return Object(NewReference(PyObject_CallObject(mPtr, args.borrowReference())));
}


Object Object::operator()(const Tuple &args, const Dict &namedArgs)
{
    return Object(NewReference(PyObject_Call(mPtr, args.borrowReference(), namedArgs.borrowReference())));
}
