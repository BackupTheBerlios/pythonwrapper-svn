#include "OPImportException.h"

using namespace OP;

ImportException::ImportException( const std::string &moduleName, const std::string &sourceFile, unsigned int line )
    : Exception( moduleName, sourceFile, line )
{
} // ImportException( )


ImportException::~ImportException( )
{
} // ~ImportException( )
