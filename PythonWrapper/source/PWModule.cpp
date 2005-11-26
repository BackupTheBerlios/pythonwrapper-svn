#include "PWModule.h"

using namespace pw;

Module::Module(const String &library)
: mDLib(library), mName(library)
{
}

Module::~Module()
{
    if (mDLib.isLoaded())
        mDLib.unload();
}

void Module::load()
{
    String init = "init"; 
    mDLib.load();

    // load module information
    GetModuleName getModuleName = (GetModuleName)mDLib.getSymbol("PW_getModuleName");
    InitFunction initFunction = (InitFunction)mDLib.getSymbol(init + getModuleName());
}

void Module::unload()
{
    mDLib.unload();
}


const String &Module::getName() const
{
    return mName;
}
