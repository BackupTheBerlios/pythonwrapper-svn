#ifndef _PWExtract_h_
#define _PWExtract_h_

#include "PWCommon.h"
#include "PWExceptions.h"
#include "PWString.h"
#include "PWTypeManager.h"

namespace pw
{
    namespace inner
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
        void PW_EXPORT _extract(PyObject *obj, String &val);
    }

    template <class T>
    T extract(const Object &object)
    {
        T val;
        inner::_extract(object.borrowReference(), val);
        PW_PyExcept_Check("extract<T>(const Object &)");
        return val;
    } // extract

    template <class T>
    T *extract(const Object &object, bool disown)
    {
        ConverterInterface *converter = TypeManager::getSingleton().findConverter(typeid(T).name());
        return converter->convert<T>(object.borrowReference(), disown);
    }
}

#endif
