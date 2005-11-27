#include "PWExtract.h"

namespace pw
{
    void _extract(PyObject *obj, bool &val)
    {
        val = PyObject_IsTrue(obj) == 1;
    }


    void _extract(PyObject *obj, double &val)
    {
        if (PyInt_Check(obj))
            val = (double)PyInt_AS_LONG(obj);
        else if (PyLong_Check(obj))
            val = PyLong_AsDouble(obj);
        else
            val = PyFloat_AsDouble(obj);
    }

    void PW_EXPORT _extract(PyObject *obj, float &val)
    {
        if (PyInt_Check(obj))
            val = (float)PyInt_AS_LONG(obj);
        else if (PyLong_Check(obj))
            val = (float)PyLong_AsDouble(obj);
        else
            val = (float)PyFloat_AsDouble(obj);
    }

    
    void _extract(PyObject *obj, unsigned short &val)
    {
        if (PyFloat_Check(obj))
            val = (unsigned short)PyFloat_AS_DOUBLE(obj);
        else if (PyLong_Check(obj))
            val = (unsigned short)PyLong_AsLong(obj);
        else
            val = (unsigned short)PyInt_AsLong(obj);
    }


    void _extract(PyObject *obj, unsigned int &val)
    {
        if (PyFloat_Check(obj))
            val = (unsigned int)PyFloat_AS_DOUBLE(obj);
        else if (PyLong_Check(obj))
            val = (unsigned int)PyLong_AsLong(obj);
        else
            val = (unsigned int)PyInt_AsLong(obj);
    }

    
    void _extract(PyObject *obj, unsigned long &val)
    {
        if (PyInt_Check(obj))
            val = (unsigned long)PyInt_AsUnsignedLongMask(obj);
        else if (PyFloat_Check(obj))
            val = (unsigned long)PyFloat_AsDouble(obj);
        else
            val = PyLong_AsUnsignedLong(obj);
    }


    void _extract(PyObject *obj, unsigned long long &val)
    {
        if (PyInt_Check(obj))
            val = (unsigned long long)PyInt_AsUnsignedLongLongMask(obj);
        else if (PyFloat_Check(obj))
            val = (unsigned long long)PyFloat_AsDouble(obj);
        else
            val = (unsigned long long)PyLong_AsLongLong(obj);
    }

    void _extract(PyObject *obj, short &val)
    {
        if (PyFloat_Check(obj))
            val = (short)PyFloat_AsDouble(obj);
        else if (PyLong_Check(obj))
            val = (short)PyLong_AsLong(obj);
        else
            val = (short)PyInt_AsLong(obj);
    }

    void _extract(PyObject *obj, int &val)
    {
        if (PyFloat_Check(obj))
            val = (int)PyFloat_AsDouble(obj);
        else if (PyLong_Check(obj))
            val = (int)PyLong_AsLong(obj);
        else
            val = (int)PyInt_AsLong(obj);
    }

    void _extract(PyObject *obj, long &val)
    {
        if (PyInt_Check(obj))
            val = PyInt_AsLong(obj);
        else if (PyFloat_Check(obj))
            val = (long)PyFloat_AsDouble(obj);
        else
            val = PyLong_AsLong(obj);
    }

    void _extract(PyObject *obj, long long &val)
    {
        if (PyInt_Check(obj))
            val = (long long)PyInt_AsUnsignedLongLongMask(obj);
        else if (PyFloat_Check(obj))
            val = (long long)PyFloat_AsDouble(obj);
        else
            val = PyLong_AsLongLong(obj);
    }

    void _extract(PyObject *obj, const char *&val)
    {
        val = PyString_AsString(obj);
    }

    void _extract(PyObject *obj, String &val)
    {
        val = PyString_AsString(obj);
    }
}
