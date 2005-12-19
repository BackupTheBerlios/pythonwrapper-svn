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

        virtual void *convert(PyObject *obj, bool disown) = 0;
        virtual PyObject *convert(void *obj, void *typeInfo, bool disown) = 0;
    };
}

#endif
