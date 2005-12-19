#include "PWModule.h"
#include "PWExceptions.h"
#include "PWInterpreter.h"

using namespace pw;

Module::Module(const String &library)
: mDLib(library), mInit(0)
{
    size_t pos = library.find(".");

    if (pos != std::string::npos)
        mName = library.substr(0, pos);
    else
        mName = library;
}


Module::Module(const String &library, const String &name)
: mDLib(library), mInit(0), mName(name)
{
}


Module::~Module()
{
    if (mDLib.isLoaded())
        mDLib.unload();
}


void Module::load()
{
    if (! mDLib.isLoaded())
        mDLib.load();

    mInit = (InitFunction)mDLib.getSymbol("init" + mName);
    
    if (!mInit)
        PW_Except(mDLib.getLibraryName() + " does not contain the function: init" + mName, "Module::load");

    Interpreter::loadModule(mName, mInit);
}


void Module::unload()
{
    mDLib.unload();
    mInit = 0;
}


const String &Module::getName() const
{
    return mName;
}


Module::InitFunction Module::getInit() const
{
    return mInit;
}

void Module::initialize()
{
    mInit();
}

void *Module::convert(PyObject *obj, bool disown)
{
    PW_Except("No converter available for basic Module.", "Module::convert");
    return 0;
}

PyObject *Module::convert(void *obj, void *type, bool disown)
{
    PW_Except("No converter available for basic Module.", "Module::convert");
    return 0;
}