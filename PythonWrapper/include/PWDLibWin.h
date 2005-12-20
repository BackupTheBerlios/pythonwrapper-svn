#ifndef _PWDLibWin_h_
#define _PWDLibWin_h_

#include "PWCommon.h"
#include "PWDLib.h"
#include "PWString.h"

// predefine the structs we use later to avoid including windows.h
struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

namespace pw
{
    /**
     * DLib implementation for Windows.
     */
    class PW_EXPORT DLibWin : public DLib
    {
    public:
        /**
         * Constructs this with the specified library name.  Note that you
         * must include the file extension (.dll) in the library name.
         * @param libraryName the library to load
         */
        DLibWin(const String &libraryName);


        /**
         * Destructor.
         */
        virtual ~DLibWin();


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
        hInstance mLib;
    };
}

#endif
