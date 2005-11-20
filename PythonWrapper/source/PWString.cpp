#include "PWString.h"
#include "PWHandler.h"
#include "PWExceptions.h"

using namespace pw;

String::String(const char *str)
: Object(NewReference(PyString_FromString(str)))
{
}


String::String(const Object &obj)
: Object(obj)
{
    if (! PyString_Check(mPtr))
    {
        Py_DECREF(mPtr);
        PYTHON_EXCEPTION_THROW;
    } // if
}


String::~String()
{
}
