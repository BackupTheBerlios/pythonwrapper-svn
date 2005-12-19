#include "PWSwigModule.h"

using namespace pw;

SwigModule::SwigModule(const String &library)
: Module(library), mLoaded(false), mSwigType(0), mToPyObject(0), mToPointer(0), mRegister(0)
{

}


SwigModule::SwigModule(const String &library, const String &name)
: Module(library, name), mLoaded(false), mSwigType(0), mToPyObject(0), mToPointer(0), mRegister(0)
{
}


SwigModule::~SwigModule()
{
}


void SwigModule::load()
{
    Module::load();

    F_GetType getType = (F_GetType)mDLib.getSymbol("PW_GetType");

    if (getType)
        mSwigType = getType();

    if (!getType || !mSwigType)
        PW_Except("Could not obtain the PyTypeObject for the module.", "SwigModule::load");

    mRegister = (F_RegisterConverters)mDLib.getSymbol("PW_RegisterConverters");
    mToPyObject = (F_ToPyObject)mDLib.getSymbol("PW_ToPyObject");
    mToPointer = (F_ToPointer)mDLib.getSymbol("PW_ToPointer");
    
    if (!mRegister)
        PW_Except("Module is missing symbol PW_RegisterConverters.", "SwigModule::load");
    
    if (!mToPyObject)
        PW_Except("Module is missing symbol PW_ToPyObject.", "SwigModule::load");

    if (!mToPointer)
        PW_Except("Module is missing symbol PW_ToPointer.", "SwigModule::load");

    mLoaded = true;
}


void SwigModule::unload()
{
    Module::unload();

    mSwigType = 0;
    mToPyObject = 0;
    mToPointer = 0;
    mLoaded = false;
}


void SwigModule::initialize()
{
    if (!mLoaded)
        PW_Except("You must load the module beofre initializing it.", "SwigModule::initialize");

    assert(mInit);
    assert(mRegister);

    mInit();
    mRegister(this);
}
