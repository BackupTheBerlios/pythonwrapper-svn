#include "OPFileException.h"

using namespace OP;

FileException::FileException( const std::string &fileName, const std::string &sourceFile, unsigned int line )
: Exception( "File error: " + fileName, sourceFile, line )
{
    mFileName = fileName;
} // FileException( const std::string &, const std::string & )


FileException::~FileException( )
{
} // ~FileException( )


const std::string &FileException::getFileName( ) const
{
    return mFileName;
} // getFileName( )
