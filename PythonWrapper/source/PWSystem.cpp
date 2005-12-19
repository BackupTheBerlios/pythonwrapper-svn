#include "PWSystem.h"
#include "PWInterpreter.h"
using namespace pw;

System *Singleton<System>::sInstance = 0;

System &System::getSingleton()
{
    assert(sInstance);
    return *sInstance;
}


System *System::getSingletonPtr()
{
    return sInstance;
}


System::System()
: mTM(0), mMM(0)
{
    if (! TypeManager::getSingletonPtr())
        mTM = new TypeManager();

    if (! ModuleManager::getSingletonPtr())
        mMM = new ModuleManager();
}


System::~System()
{
    if (mTM)
        delete mTM;

    if (mMM)
        delete mMM;
}


void System::loadModule(const String &dllName)
{
    ModuleManager::getSingletonPtr()->loadModule(dllName);
}


void System::loadSwigModule(const String &dllName)
{
    ModuleManager::getSingletonPtr()->loadSwigModule(dllName);
}


void System::initialize()
{
    Interpreter::Initialize();
}


void System::finalize()
{
    Interpreter::Finalize();
}
