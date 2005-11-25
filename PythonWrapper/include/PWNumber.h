#ifndef _PWNumber_h_
#define _PWNumber_h_

#include "PythonWrapper.h"

namespace pw
{
    class PW_EXPORT Number : public Object
    {
    public:
        Number();
        Number(unsigned short val);
        Number(unsigned long val);
        Number(unsigned long long val);
        Number(short val);
        Number(long val);
        Number(long long val);
        Number(double val);
        Number(char *str, int base);
        virtual ~Number();
    };
}

#endif
