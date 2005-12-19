#include "TSClassA.h"

namespace ts
{
    A::A() : val(7) {}
    A::~A() {}

    void A::setValue(int v)
    {
        val = v;
    }
    int A::getValue() const
    {
        return val;
    }
}
