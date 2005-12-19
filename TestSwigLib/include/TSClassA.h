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

        virtual void setValue(int v);
        virtual int getValue() const;

        int val;
    };
}

#endif
