#include "PWExceptions.h"
#include "PWHandler.h"
#include <cassert>

using namespace pw;

PythonException::PythonException()
{
    PyObject *type = 0,
             *value = 0,
             *stackTrace = 0;

    PyErr_Fetch(&type, &value, &stackTrace);
    
    if (type)
        mType = NewReference(type);

    if (value)
        mValue = NewReference(value);

    if (stackTrace)
        mStackTrace = NewReference(stackTrace);
}


PythonException::~PythonException()
{
}


const Object &PythonException::getType() const
{
    return mType;
}


const Object &PythonException::getStackTrace() const
{
    return mStackTrace;
}


const Object &PythonException::getValue() const
{
    return mValue;
}
