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

void ModuleManager::loadModule(const String &dllName)
{
    ModuleMap::iterator itr;

    itr = mModules.find(dllName);
    if (itr != mModules.end())
        PW_Except("Already loaded module with name " + dllName + ".",
                  "ModuleManager::loadModule");

    Module *module = 0;

    try
    {
        module = new Module(dllName);
        module->load();
    } // try
    catch (...)
    {
        if (module)
            delete module;

        throw;
    } // catch

    mModules[dllName] = module;
}


void ModuleManager::unloadModule(const String &dllName)
{
    ModuleMap::iterator itr = mModules.find(dllName);
    if (itr == mModules.end())
        PW_Except("Module " + dllName + " is not registered in the ModuleManager.",
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
