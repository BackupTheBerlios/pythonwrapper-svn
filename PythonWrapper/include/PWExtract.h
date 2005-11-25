#ifndef _PWExtract_h_
#define _PWExtract_h_

#include "PWCommon.h"
#include "PWExceptions.h"

namespace pw
{
    void PW_EXPORT _extract(PyObject *obj, bool &val);
    void PW_EXPORT _extract(PyObject *obj, double &val);
    void PW_EXPORT _extract(PyObject *obj, unsigned short &val);
    void PW_EXPORT _extract(PyObject *obj, unsigned int &val);
    void PW_EXPORT _extract(PyObject *obj, unsigned long &val);
    void PW_EXPORT _extract(PyObject *obj, unsigned long long &val);
    void PW_EXPORT _extract(PyObject *obj, short &val);
    void PW_EXPORT _extract(PyObject *obj, int &val);
    void PW_EXPORT _extract(PyObject *obj, long &val);
    void PW_EXPORT _extract(PyObject *obj, long long &val);
    void PW_EXPORT _extract(PyObject *obj, float &val);
    void PW_EXPORT _extract(PyObject *obj, const char *&val);

    template <class T>
    T extract(const Object &object)
    {
        T val;
        _extract(object.borrowReference(), val);
        PYTHON_EXCEPTION_CHECK;
        return val;
    } // extract
}

#endif
