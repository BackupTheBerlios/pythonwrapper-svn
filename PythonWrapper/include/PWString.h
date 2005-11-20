#ifndef _PWString_h_
#define _PWString_h_

#include "PWCommon.h"
#include "PWObject.h"

namespace pw
{
    class _PW_EXPORT String : public Object
    {
    public:
        String(const char *str);
        String(const Object &obj);
        virtual ~String();

        virtual inline const char *c_str()
        { return PyString_AS_STRING(mPtr); }
    };
}

#endif
