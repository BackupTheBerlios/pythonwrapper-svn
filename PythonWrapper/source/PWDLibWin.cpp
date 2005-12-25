#include "PWDLibWin.h"
#include "PWExceptions.h"
#include "PWLogManager.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace pw
{
    DLibWin::DLibWin(const String &libraryName)
    : DLib(libraryName), mLib(0)
    {
    }

    DLibWin::~DLibWin()
    {
        if (mLib)
            unload();
    }


    void DLibWin::load()
    {
        if (!mLib)
        {
            PW_LOG("Loading library " + mLibraryName, "DLibWin::load", LogManager::High);
            mLib = (hInstance)LoadLibrary(mLibraryName.c_str());

            if (!mLib)
                PW_Except("An error occurred while loading " + mLibraryName + ".",
                          "DLibWin::load");
        } // if
    } // DLibWin::load


    void DLibWin::unload()
    {
        if (mLib)
        {
            PW_LOG("Unloading library " + mLibraryName, "DLibWin::unload", LogManager::High);

            BOOL rval = FreeLibrary(mLib);
            mLib = 0;

            if (! rval)
                PW_Except("An error occurred while unloading " + mLibraryName + ".",
                          "DLibWin::unload");
        } // if
    }

    void *DLibWin::getSymbol(const String &symbol) const
    {
        return (void *)GetProcAddress(mLib, symbol.c_str());
    }


    bool DLibWin::isLoaded()
    {
        return mLib != 0;
    }
} // namespace pw
