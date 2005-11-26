#include "PWModuleManager.h"
#include "PWDLib.h"
#include "PWExceptions.h"

using namespace pw;

ModuleManager *Singleton<ModuleManager>::sInstance = 0;

ModuleManager &ModuleManager::getSingleton()
{
    return *Singleton<ModuleManager>::sInstance;
}

ModuleManager *ModuleManager::getSingletonPtr()
{
    return Singleton<ModuleManager>::sInstance;
}

ModuleManager::ModuleManager()
{
}


ModuleManager::~ModuleManager()
{
    unloadAll();
}

Module *ModuleManager::loadModule(const String &dllName)
{
    ModuleMap::iterator itr;

    itr = mModules.find(dllName);
    if (itr == mModules.end())
        EXCEPTION_THROW;

    Module *toReturn = 0;

    try
    {
        toReturn = new Module(dllName);
        toReturn->load();
    } // try
    catch (...)
    {
        if (toReturn)
            delete toReturn;

        throw;
    } // catch

    mModules[dllName] = toReturn;
    return toReturn;
}


void ModuleManager::unloadModule(Module *module)
{
    assert(module);

    ModuleMap::iterator itr = mModules.find(module->getName());
    if (itr == mModules.end())
        EXCEPTION_THROW;

    itr->second->unload();
    delete itr->second;
    mModules.erase(itr);
}

void ModuleManager::unloadAll()
{
    for (ModuleMap::iterator itr = mModules.begin(); itr != mModules.end(); ++itr)
    {
        itr->second->unload();
        delete itr->second;
    } // if

    mModules.clear();
}
