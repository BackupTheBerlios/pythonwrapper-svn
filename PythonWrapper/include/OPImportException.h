#ifndef _OPIMPORTEXCEPTION_H_
#define _OPIMPORTEXCEPTION_H_

#include "OPException.h"

#include <string>

namespace OP
{
    /** This exception is thrown when there is an error loading a module.
     */
    class _OP_DLL_EXPORT ImportException : public Exception
    {
    public:
        ImportException( const std::string &moduleName, const std::string &sourceFile, unsigned int line );
        virtual ~ImportException( );
    }; // class ImportException

} // namespace OP

#endif
