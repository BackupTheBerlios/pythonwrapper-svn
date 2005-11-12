#include "PWObject.h"
#include "PWHandler.h"
#include "PWExceptions.h"

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
        if (PyErr_Occurred())
            PYTHON_EXCEPTION_THROW;

        NULL_OBJECT_EXCEPTION_THROW;
    } // if
} // check(PyObject *)
