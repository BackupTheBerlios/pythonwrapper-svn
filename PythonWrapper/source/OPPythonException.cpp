#include "OPPythonException.h"

using namespace OP;

PythonException::PythonException( const std::string &pyErrorMessage, const std::string &pyExceptionType, const std::string &pyStackTrace, const std::string &sourceFile, unsigned int line )
: Exception( pyErrorMessage, sourceFile, line ), mExceptionType( pyExceptionType ), mStackTrace( pyStackTrace )
{
} // PythonException( const std::string &, const std::string &, const std::string & )


PythonException::~PythonException( )
{
} // ~PythonException( )


const std::string &PythonException::getExceptionType( ) const
{
    return mExceptionType;
} // getExceptionType( )

const std::string &PythonException::getStackTrace( ) const
{
    return mStackTrace;
} // getStackTrace( )
