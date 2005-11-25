#ifndef _PWExceptions_h_
#define _PWExceptions_h_

#include "PWCommon.h"
#include "PWObject.h"

#define EXCEPTION_THROW throw pw::Exception()
#define PYTHON_EXCEPTION_THROW throw pw::PythonException()
#define PYTHON_EXCEPTION_CHECK if (PyErr_Occurred()) PYTHON_EXCEPTION_THROW
#define PYTHON_NULL_RETURN_CHECK(x) if (!x) throw pw::PythonException()
#define NULL_OBJECT_EXCEPTION_THROW throw pw::NullObjectException()

namespace pw
{
    class PW_EXPORT Exception
    {
    public:
        inline Exception() {}
        virtual inline ~Exception() {}
    };

    class PW_EXPORT PythonException : public Exception
    {
    public:
        PythonException();
        virtual ~PythonException();
        
        virtual const Object &getType() const;
        virtual const Object &getStackTrace() const;
        virtual const Object &getValue() const;
    protected:
        Object mType;
        Object mStackTrace;
        Object mValue;
    };

    class PW_EXPORT NullObjectException : public Exception
    {
    public:
        inline NullObjectException() {}
        virtual inline ~NullObjectException() {}
    };
}

#endif
