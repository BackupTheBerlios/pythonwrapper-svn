#include "PWExceptions.h"
#include "PWHandler.h"
#include "PWLogManager.h"
#include "PWString.h"
#include "PWExtract.h"

namespace pw
{
    Exception::Exception(const String &msg, const String &funct,
                         const String &file, unsigned int line)
    : mMsg(msg), mFunct(funct), mFile(file), mLine(line)
    {
        LogManager::log(mMsg, mFunct, mFile, mLine, LogManager::Low);
    } // Exception


    
    Exception::Exception(const String &funct, const String &file,
                         unsigned int line)
    : mFunct(funct), mFile(file), mLine(line)
    {
    }


    const String &Exception::getMessage() const
    {
        return mMsg;
    } // getMessage


    const String &Exception::getFunction() const
    {
        return mFunct;
    } // getFunction


    const String &Exception::getFile() const
    {
        return mFile;
    } // getFile


    unsigned int Exception::getLine() const
    {
        return mLine;
    } // getLine


    PythonException::PythonException(const String &funct, const String &file,
                                     unsigned int line)
    : Exception(funct, file, line)
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

        LogManager::log("Python Exception", mFunct, mFile, mLine, LogManager::Medium);
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

    NullObjectException::NullObjectException(const String &msg,
                  const String &funct, const String &file, unsigned int line)
    : Exception(msg, funct, file, line)
    {
    }
} // namespace pw
