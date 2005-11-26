#ifndef _PWBuild_h_
#define _PWBuild_h_

#include "PWCommon.h"
#include "PWHandler.h"

namespace pw
{
    inline NewReference build(unsigned short val)
    { return NewReference(PyLong_FromUnsignedLong((unsigned long)val)); }


    inline NewReference build(unsigned long val)
    { return NewReference(PyLong_FromUnsignedLong(val)); }


    inline NewReference build(unsigned long long val)
    { return NewReference(PyLong_FromUnsignedLongLong(val)); }


    inline NewReference build(short val)
    { return NewReference(PyInt_FromLong((long)val)); }


    inline NewReference build(long val)
    { return NewReference(PyInt_FromLong(val)); }


    inline NewReference build(long long val)
    { return NewReference(PyLong_FromLongLong(val)); }


    inline NewReference build(double val)
    { return NewReference(PyFloat_FromDouble(val)); }


    inline NewReference build(const char *str)
    { return NewReference(PyString_FromString(str)); }

    inline BorrowedReference build(bool val)
    { return BorrowedReference(val ? Py_True : Py_False); }
}

#endif
