#include "OPException.h"

using namespace OP;


Exception::Exception( const std::string &description, const std::string &file )
{
    mDescription = description;
    mFile = file;
} // Exception( const std::string &, const std::string & )


Exception::~Exception( )
{
} // ~Exception( )


const std::string &Exception::getDescription( )
{
    return mDescription;
} // getDescription( )


const std::string &Exception::getFile( )
{
    return mFile;
} // getFile( )
