#include "OPException.h"

using namespace OP;


Exception::Exception( const std::string &description, const std::string &sourceFile, unsigned int line )
{
    mDescription = description;
    mFile = sourceFile;
    mLine = line;
} // Exception( const std::string &, const std::string & )


Exception::~Exception( )
{
} // ~Exception( )


const std::string &Exception::getDescription( ) const
{
    return mDescription;
} // getDescription( )


const std::string &Exception::getFile( ) const
{
    return mFile;
} // getFile( )

unsigned int Exception::getLine( ) const
{
    return mLine;
}
