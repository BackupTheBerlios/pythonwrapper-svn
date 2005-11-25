#include "PWNumber.h"

using namespace pw;

Number::Number()
: Object(NewReference(PyInt_FromLong(0)))
{
}


Number::Number(unsigned long val)
: Object(NewReference(PyLong_FromUnsignedLong(val)))
{
}


Number::Number(long long val)
: Object(NewReference(PyLong_FromLongLong(val)))
{
}

Number::Number(unsigned long long val)
: Object(NewReference(PyLong_FromUnsignedLongLong(val)))
{
}

Number::Number(unsigned short val)
: Object(NewReference(PyLong_FromUnsignedLong((unsigned long)val)))
{
}


Number::Number(short val)
: Object(NewReference(PyInt_FromLong((long)val)))
{
}


Number::Number(double val)
: Object(NewReference(PyFloat_FromDouble(val)))
{
}

Number::Number(long val)
: Object(NewReference(PyInt_FromLong(val)))
{
}

Number::Number(char *str, int base)
: Object(NewReference(PyLong_FromString(str, 0, base)))
{
}

Number::~Number()
{
}
