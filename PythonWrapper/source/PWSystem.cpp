#include "PWSystem.h"
#include "PWInterpreter.h"
#include "PWExceptions.h"
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
    ModuleManager *mm = ModuleManager::getSingletonPtr();
    if (! mm)
        PW_Except("Cannot load a module if the ModuleManager does not exist.",
                  "System::loadModule");
    mm->loadModule(dllName);
}


void System::loadSwigModule(const String &dllName)
{
    ModuleManager *mm = ModuleManager::getSingletonPtr();
    if (! mm)
        PW_Except("Cannot load a module if the ModuleManager does not exist.",
                  "System::loadSwigModule");
    mm->loadSwigModule(dllName);
}


void System::initialize()
{
    Interpreter::Initialize();
    
    ModuleManager *mm = ModuleManager::getSingletonPtr();
    if (mm)
        mm->initializeModules();
}


void System::finalize()
{
    Interpreter::Finalize();
}
