#ifndef _TSInner_h_
#define _TSInner_h_

#include "TSCommon.h"
#include "TSClassB.h"

namespace ts
{
    class TS_EXPORT Inner
    {
    public:
        Inner();
        ~Inner();

        int getValue(A *a) const;
    };
}

#endif
