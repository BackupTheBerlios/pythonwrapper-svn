#ifndef _OPException_h_
#define _OPException_h_

#include "OPCommon.h"

#include <string>

namespace OP
{
    /** The base exception class for OP.
        @remarks
            This class is the base for all exceptions thrown by OP.
     */
    class _OP_DLL_EXPORT Exception
    {
    public:
        /** Constructor.
            @remarks
                Every OP exception must have a description, and inform the user which file
                the exception occured in.
            @param description
                A short description of what went wrong.
            @param file
                The file in which the exception was thrown.
         */
        Exception( const std::string &description, const std::string &file );
        virtual ~Exception( );


        /** Gets the description of the Exception.
         */
        virtual const std::string &getDescription( );


        /** Gets the file in which the Exception was raised occured.
         */
        virtual const std::string &getFile( );
    protected:
        /** The description of the error.
         */
        std::string mDescription;


        /** The file the error occured in.
         */
        std::string mFile;
    }; // class Exception
} // namespace OP

#endif
