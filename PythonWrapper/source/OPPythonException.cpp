#include "OPPythonException.h"

using namespace OP;

PythonException::PythonException( const std::string &pyErrorMessage, const std::string &pyExceptionType, const std::string &sourceFile )
: Exception( pyErrorMessage, sourceFile )
{
    mExceptionType = pyExceptionType;
} // PythonException( const std::string &, const std::string &, const std::string & )


PythonException::~PythonException( )
{
} // ~PythonException( )


const std::string &PythonException::getExceptionType( )
{
    return mExceptionType;
} // getExceptionType( )
