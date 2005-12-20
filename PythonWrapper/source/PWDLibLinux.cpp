#include "PWDLibLinux.h"
#include "PWExceptions.h"

namespace pw
{
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
            PW_Except("Could not load library " + mLibraryName + ".", "DLibLinux::load");
    }


    void DLibLinux::unload()
    {
        if (mLib)
        {
            if (dlclose(mLib))
            {
                mLib = 0;
                if (! rval)
                    PW_Except("Error unloading " + mLibraryName + ".", "DLibLinux::unload");
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
}
