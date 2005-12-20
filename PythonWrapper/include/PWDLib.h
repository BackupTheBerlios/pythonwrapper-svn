#ifndef _PWDLib_h_
#define _PWDLib_h_

#include "PWCommon.h"
#include "PWString.h"

namespace pw
{
    /**
     * DLib is a dynamic library interface.  When a shared library needs to be
     * loaded, this class provides the interface which is used to load the
     * library and retrieve symbols.  This class is subclassed to actually
     * implement this for various platforms.
     */
    class PW_EXPORT DLib
    {
    public:
        /**
         * Constructs this with the specified library name.  Note that under
         * windows you must include the extension (.dll) but under linux, you
         * do not include the extention (.so).
         * @param libraryName the library to load
         */
        DLib(const String &libraryName);

        
        /**
         * Destructor.
         */
        virtual ~DLib();


        /**
         * Returns the library name.
         * @return the library name
         */
        virtual const String &getLibraryName() const;


        /**
         * Loads the dynamic library.  After the library is loaded symbols
         * can be obtained by calling getSymbol.
         */
        virtual void load() = 0;


        /**
         * Unload the dynamic library.  After this is done you cannot call
         * getSymbol or use the symbols that are obtained from the library.
         */
        virtual void unload() = 0;


        /**
         * Returns true if the library is loaded, false otherwise.
         * @returns whether the library is loaded or not
         */
        virtual bool isLoaded() = 0;


        /**
         * Returns the symbol specified, or 0 if it does not exist.
         * @returns the symbol specified or null
         */
        virtual void *getSymbol(const String &symbol) const = 0;

    protected:
        String mLibraryName;
    };
}


/* We will select the proper dynamic library based on the compiler.  If we are
 * under a unix platform, use the Linux DLib implementation...otherwise use the
 * windows version.
 */
#if defined(__WIN32__) || defined(_WIN32)
#    if defined(__MINGW32__)
#       define PW_EXPORT
#       define PW_DLIB DLibLinux
#       include "PWDLibLinux.h"
#   else
#       define PW_DLIB DLibWin
#       include "PWDLibWin.h"
#    endif
#else
#   define PW_EXPORT
#   define PW_DLIB DLibLinux
#   include "PWDLibLinux.h"
#endif

#endif
