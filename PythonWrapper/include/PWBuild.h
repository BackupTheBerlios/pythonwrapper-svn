#ifndef _PWBuild_h_
#define _PWBuild_h_

#include "PWCommon.h"
#include "PWHandler.h"
#include "PWString.h"
#include "PWConverterInterface.h"
#include "PWTypeManager.h"

namespace pw
{
    inline Object build(unsigned short val)
    { return Object(NewReference(PyLong_FromUnsignedLong((unsigned long)val))); }

    inline Object build(unsigned long val)
    { return Object(NewReference(PyLong_FromUnsignedLong(val))); }

    inline Object build(unsigned long long val)
    { return Object(NewReference(PyLong_FromUnsignedLongLong(val))); }

    inline Object build(short val)
    { return Object(NewReference(PyInt_FromLong((long)val))); }

    inline Object build(long val)
    { return Object(NewReference(PyInt_FromLong(val))); }

    inline Object build(long long val)
    { return Object(NewReference(PyLong_FromLongLong(val))); }

    inline Object build(double val)
    { return Object(NewReference(PyFloat_FromDouble(val))); }

    inline Object build(const char *str)
    { return Object(NewReference(PyString_FromString(str))); }

    inline Object build(const String &str)
    { return Object(NewReference(PyString_FromString(str.c_str()))); }

    inline Object build(bool val)
    { return Object(BorrowedReference(val ? Py_True : Py_False)); }

    template <class T>
    inline Object build(T *val, bool disown)
    {
        ConverterInterface *converter = TypeManager::getSingleton().findConverter(typeid(T).name());
        return NewReference(converter->convert<T>(val, disown));
    }

}

#endif
