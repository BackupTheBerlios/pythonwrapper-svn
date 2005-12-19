#ifndef _TSClassB_h_
#define _TSClassB_h_

#include "TSCommon.h"
#include "TSClassA.h"

namespace ts
{
    class TS_EXPORT B : public A
    {
    public:
        B();
        virtual ~B();
    };
}

#endif
