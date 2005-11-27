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
    if (itr != mModules.end())
        PW_Except("Already loaded module with name " + dllName + ".",
                  "ModuleManager::loadModule");

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


void ModuleManager::unloadModule(const String &name)
{
    ModuleMap::iterator itr = mModules.find(name);
    if (itr == mModules.end())
        PW_Except("Module " + name + " is not registered in the ModuleManager.",
                  "ModuleManager::unloadModule");

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
