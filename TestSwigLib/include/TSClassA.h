#ifndef _TSClassA_h_
#define _TSClassA_h_

#include "TSCommon.h"

namespace ts
{
    class TS_EXPORT A
    {
    public:
        A();
        virtual ~A();

        virtual int getValue() const;
    };
}

#endif
