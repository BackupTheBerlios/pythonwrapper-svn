#ifndef _PWExceptions_h_
#define _PWExceptions_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWObject.h"

#define PW_Except(msg, funct) throw pw::Exception(msg, funct, __FILE__, __LINE__);
#define PW_PyExcept(funct) throw pw::PythonException(funct, __FILE__, __LINE__);
#define PW_PyExcept_Check(funct) if (PyErr_Occurred()) throw pw::PythonException(funct, __FILE__, __LINE__);
#define PW_NullExcept(msg, funct) throw pw::NullObjectException(msg, funct, __FILE__, __LINE__)

/*
#define EXCEPTION_THROW throw pw::Exception()
#define PYTHON_EXCEPTION_THROW throw pw::PythonException()
#define PYTHON_EXCEPTION_CHECK if (PyErr_Occurred()) PYTHON_EXCEPTION_THROW
#define PYTHON_NULL_RETURN_CHECK(x) if (!x) throw pw::PythonException()
#define NULL_OBJECT_EXCEPTION_THROW throw pw::NullObjectException()
*/
namespace pw
{
    class PW_EXPORT Exception
    {
    public:
        Exception(const String &msg, const String &funct, const String &file,
                  unsigned int line);
        virtual inline ~Exception() {}

        virtual const String &getMessage() const;
        virtual const String &getFunction() const;
        virtual const String &getFile() const;
        virtual unsigned int getLine() const;

    protected:
        String mMsg;
        String mFunct;
        String mFile;
        unsigned int mLine;
    };

    class PW_EXPORT PythonException : public Exception
    {
    public:
        PythonException(const String &funct, const String &file,
                        unsigned int line);
        virtual inline ~PythonException() {}
        
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
        inline NullObjectException(const String &msg, const String &funct,
                                   const String &file, unsigned int line);
        virtual inline ~NullObjectException() {}
    };
}

#endif
