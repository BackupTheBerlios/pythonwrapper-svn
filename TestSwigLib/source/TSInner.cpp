#include "TSInner.h"

namespace ts
{
    Inner::Inner() {}
    Inner::~Inner() {}

    int Inner::getValue(A *a) const
    {
        if (a)
            return a->getValue();

        return 0;
    }
}
