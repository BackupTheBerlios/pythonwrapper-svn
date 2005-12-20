#ifndef _PWExceptions_h_
#define _PWExceptions_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWObject.h"

/**
 * Used to throw an Exception.
 */
#define PW_Except(msg, funct) throw pw::Exception(msg, funct, __FILE__, __LINE__);


/**
 * Used to create a warning.
 */
#define PW_Warn(msg, funct) throw pw::Exception(msg, funct, __FILE__, __LINE__);


/**
 * Used to throw a PythonException.
 */
#define PW_PyExcept(funct) throw pw::PythonException(funct, __FILE__, __LINE__);


/**
 * Throws a PythonException if an error occurred.
 */
#define PW_PyExcept_Check(funct) if (PyErr_Occurred()) throw pw::PythonException(funct, __FILE__, __LINE__);


/**
 * Throws a NullObjectException.
 */
#define PW_NullExcept(msg, funct) throw pw::NullObjectException(msg, funct, __FILE__, __LINE__)


namespace pw
{
    /**
     * The basic exception class.
     */
    class PW_EXPORT Exception
    {
    public:
        /**
         * Constructor.
         * @param msg the detailed error message
         * @param funct the function in which the exception occurs
         * @param file the file in which the exception occurs
         * @param line the line in which the error occurred
         */
        Exception(const String &msg, const String &funct, const String &file,
                  unsigned int line);


        /**
         * Destructor.
         */
        virtual inline ~Exception() {}

        /**
         * Returns the message this object was created with.
         */
        virtual const String &getMessage() const;


        /**
         * Returns the function the exception occurred in.
         */
        virtual const String &getFunction() const;


        /**
         * Returns the file the exception occurred in.
         */
        virtual const String &getFile() const;


        /**
         * Returns the line on which the error occurred.
         */
        virtual unsigned int getLine() const;

    protected:
        String mMsg;
        String mFunct;
        String mFile;
        unsigned int mLine;
    };


    /**
     * The Exception class which is thrown when a python error occurs.  Note
     * that this should only be thrown when PyErr_Occurred() returns non null.
     */
    class PW_EXPORT PythonException : public Exception
    {
    public:
        /**
         * Constructor.
         * @param funct the function in which the exception occurs
         * @param file the file in which the exception occurs
         * @param line the line in which the error occurred
         */
        PythonException(const String &funct, const String &file,
                        unsigned int line);


        /**
         * Destructor.
         */
        virtual inline ~PythonException() {}
        

        /**
         * Returns the python exception type.
         */
        virtual const Object &getType() const;


        /**
         * Returns the stack trace object.
         */
        virtual const Object &getStackTrace() const;


        /**
         * Returns the value of the exception.  For most uses you should
         * probably call __str__ on this return value to obtain a string
         * value.
         */
        virtual const Object &getValue() const;

    protected:
        Object mType;
        Object mStackTrace;
        Object mValue;
    };


    /**
     * Thrown when a null object is passed into an object.
     */
    class PW_EXPORT NullObjectException : public Exception
    {
    public:
        /**
         * Constructor.
         * @param msg the detailed error message
         * @param funct the function in which the exception occurs
         * @param file the file in which the exception occurs
         * @param line the line in which the error occurred
         */
        inline NullObjectException(const String &msg, const String &funct,
                                   const String &file, unsigned int line);

        /**
         * Destructor.
         */
        virtual inline ~NullObjectException() {}
    };
}

#endif
