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
            @param sourceFile
                The file in which the exception was thrown.
            @param line
                The line on which the exception was thrown.
         */
        Exception( const std::string &description, const std::string &sourceFile, unsigned int line );
        virtual ~Exception( );


        /** Gets the description of the Exception.
         */
        virtual const std::string &getDescription( ) const;


        /** Gets the file in which the Exception occured.
         */
        virtual const std::string &getFile( ) const;


        /** Gets the line on which the Exception occured.
         */
        virtual unsigned int getLine( ) const;
    protected:
        /** The description of the error.
         */
        std::string mDescription;


        /** The file the error occured in.
         */
        std::string mFile;


        /** The line on which the error occured.
         */
        unsigned int mLine;
    }; // class Exception
} // namespace OP

#endif
