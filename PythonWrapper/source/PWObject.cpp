#include "PWObject.h"
#include "PWHandler.h"
#include "PWExceptions.h"
#include "PWDict.h"
#include "PWExtract.h"

namespace pw
{
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
    } // Object()


    Object &Object::operator=(const Object &rhs)
    {
        assert(rhs.borrowReference());

        // this if takes care of the case when the pointer is the same; if we
        // did not do this check the following code below would bomb if
        // mPtr == rhs.mPtr and the refcount was at 1
        if (mPtr != rhs.borrowReference())
        {
            Py_DECREF(mPtr);
            mPtr = rhs.borrowReference();
            Py_INCREF(mPtr);
        } // if

        return *this;
    } // operator=


    
    Object::operator void *() const
    {
        int toReturn = PyObject_IsTrue(mPtr);
        PW_PyExcept_Check("Object::operator void *()");
        return toReturn ? (void *)1 : (void *)0;
    }


    bool Object::operator!() const
    {
        int toReturn = PyObject_Not(mPtr);
        PW_PyExcept_Check("Object::operator void *()");
        return toReturn ? true : false;
    }

    int Object::length() const
    {
        int toReturn = PyObject_Size(mPtr);
        PyErr_Clear();
        return toReturn;
    } // length()


    Object Object::getAttr(const Object &attr) const
    {
        return Object(NewReference(PyObject_GetAttr(mPtr, attr.borrowReference())));
    } // getAttr(const Object &)


    void Object::setAttr(const Object &attr, const Object &value)
    {
        PyObject_SetAttr(mPtr, attr.borrowReference(), value.borrowReference());
        PW_PyExcept_Check("Object::setAttr");
    } // setAttr(const Object &, const Object &)


    void Object::delAttr(const Object &attr)
    {
        bool toReturn = PyObject_DelAttr(mPtr, attr.borrowReference()) != -1;
        PW_PyExcept_Check("Object::delAttr");
    } // delAttr(const Object &)


    Object Object::getAttr(const String &attr) const
    {
        return Object(NewReference(PyObject_GetAttrString(mPtr, (char *)attr.c_str())));
    } // getAttr(const String &)


    void Object::setAttr(const String &attr, const Object &value)
    {
        PyObject_SetAttrString(mPtr, (char *)attr.c_str(), value.borrowReference());
    } // setAttr(const String &, const Object &)


    void Object::delAttr(const String &attr)
    {
        PyObject_DelAttrString(mPtr, (char *)attr.c_str());
    } // delAttr(const String &)


    Object Object::operator()()
    {
        return Object(NewReference(PyObject_CallObject(mPtr, 0)));
    } // operator()


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
        } // else

        return NewReference(toReturn);
    } // operator(const Object &)


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
        } // else

        return NewReference(toReturn);
    } // operator(const Object &, const Dict &)
} // namespace pw
