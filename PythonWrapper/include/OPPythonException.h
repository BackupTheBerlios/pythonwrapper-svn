#ifndef _OPPythonException_h_
#define _OPPythonException_h_

#include "OPCommon.h"
#include "OPException.h"

#include <string>

namespace OP
{
    /** This exception is thrown whenever the python interpreter throws an exception.
     */
    class _OP_DLL_EXPORT PythonException : public OP::Exception
    {
    public:
        /** Constructor
            @remarks
                Since Python exceptions can cover all kinds of problems, this class makes a
                "Best Guess" as to how to set the error message.  The error type will contain
                the string representation of the Python type the exception is.
            @param pyExceptionType
                The string representation of the Python exception Type.
            @param pyErrorMessage
                The error message that Python reports.
            @param sourceFile
                The file in which the exception occurs.
         */
        PythonException( const std::string &pyErrorMessage, const std::string &pyExceptionType, const std::string &sourceFile );
        virtual ~PythonException( );


        /** Returns the Python exception Type.
            @remarks
                This is equivilant to PyObject->ob_type->tp_name.
         */
        virtual const std::string &getExceptionType( );
    protected:
        /** The string ExceptionType (Python type).
         */
        std::string mExceptionType;
    };
}

#endif
