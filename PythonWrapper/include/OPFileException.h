#ifndef _OPFileException_h_
#define _OPFileException_h_

#include "OPCommon.h"
#include "OPException.h"

#include <string>

namespace OP
{
    /** Exception for when there is an error reading or writing to a file.
     */
    class _OP_DLL_EXPORT FileException : public OP::Exception
    {
    public:
        /** Constructor.
            @param fileName
                The file which could not be read or written to.
            @param sourceFile
                The source file which the exception was thrown in.
            @param line
                The line on which the exception was thrown.
         */
        FileException( const std::string &fileName, const std::string &sourceFile, unsigned int line );
        virtual ~FileException();

        /** Retrieves the name of the file that could not be read or written.
            @return
                The name of the file which could not be read or written.
         */
        virtual const std::string &getFileName( ) const;
    protected:
        /** The file which could not be read or written.
         */
        std::string mFileName;
    };
} // namespace OP

#endif
