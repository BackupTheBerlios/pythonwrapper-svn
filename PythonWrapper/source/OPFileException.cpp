#include "OPFileException.h"

using namespace OP;

FileException::FileException( const std::string &fileName, const std::string &sourceFile )
: Exception( "File error: " + fileName, sourceFile )
{
    mFileName = fileName;
} // FileException( const std::string &, const std::string & )


FileException::~FileException( )
{
} // ~FileException( )


const std::string &FileException::getFileName( )
{
    return mFileName;
} // getFileName( )
