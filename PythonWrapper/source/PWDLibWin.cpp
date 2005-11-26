#include "PWDLibWin.h"
#include "PWExceptions.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace pw;

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
    mLib = (hInstance)LoadLibrary(mLibraryName.c_str());

    if (!mLib)
        EXCEPTION_THROW;
}


void DLibWin::unload()
{
    if (mLib)
    {
        BOOL rval = FreeLibrary(mLib);
        mLib = 0;

        if (! rval)
            EXCEPTION_THROW;
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
