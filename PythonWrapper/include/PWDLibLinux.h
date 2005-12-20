#ifndef _PWDLibLinux_h_
#define _PWDLibLinux_h_

#include "PWCommon.h"
#include "PWDLib.h"
#include "PWString.h"

namespace pw
{
    /**
     * DLib implementation for Linux.
     */
    class DLibLinux : public DLib
    {
    public:
        /**
         * Constructs this with the specified library name.  Note that under
         * linux you should not include the extension (.so).
         * @param libraryName the library to load
         */
        DLibLinux(const String &libraryName);


        /**
         * Destructor.
         */
        virtual ~DLibLinux();

        /**
         * Loads the dynamic library.  After the library is loaded symbols
         * can be obtained by calling getSymbol.
         */
        virtual void load();


        /**
         * Unload the dynamic library.  After this is done you cannot call
         * getSymbol or use the symbols that are obtained from the library.
         */
        virtual void unload();


        /**
         * Returns true if the library is loaded, false otherwise.
         * @returns whether the library is loaded or not
         */
        virtual bool isLoaded();


        /**
         * Returns the symbol specified, or 0 if it does not exist.
         * @returns the symbol specified or null
         */
        virtual void *getSymbol(const String &symbol) const;
    protected:
        void *mLib;
    };
}

#endif
