#include "PWDLibLinux.h"
#include "PWExceptions.h"

using namespace pw;

DLibLinux::DLibLinux(const String &libraryName)
: DLib(libraryName), mLib(0)
{
}

DLibLinux::~DLibLinux()
{
    if (mLib)
        unload();
}


void DLibLinux::load()
{
    mLib = dlopen(mLibraryName.c_str(), RTLD_LAZY);

    if (!mLib)
        EXCEPTION_THROW;
}


void DLibLinux::unload()
{
    if (mLib)
    {
        if (dlclose(mLib))
        {
            mLib = 0;
            if (! rval)
                EXCEPTION_THROW;
        }

        mLib = 0;
    } // if
}

void *DLibLinux::getSymbol(const String &symbol) const
{
    return (void *)dlsym(mLib, symbol.c_str());
}


bool DLibLinux::isLoaded()
{
    return mLib != 0;
}
