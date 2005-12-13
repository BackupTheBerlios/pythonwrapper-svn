#ifndef _PWConverterInterface_h_
#define _PWConverterInterface_h_

#include "PWCommon.h"

namespace pw
{
    class PW_EXPORT ConverterInterface
    {
    public:
        inline ConverterInterface() {}
        virtual inline ~ConverterInterface() {}

        template <class T>
        T *convert(PyObject *obj, bool disown) = 0;

        template <class T>
        PyObject *convert(T *obj, bool disown) = 0;
    };
}

#endif
