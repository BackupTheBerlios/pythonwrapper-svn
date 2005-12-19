#include "PWModuleManager.h"
#include "PWDLib.h"
#include "PWExceptions.h"
#include "PWSwigModule.h"

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


void ModuleManager::addModule(Module *module)
{
    assert(module);

    ModuleMap::iterator itr;
    String name = module->getName();

    itr = mModules.find(name);
    if (itr != mModules.end())
        PW_Except("Already loaded module with name " + name + ".",
                  "ModuleManager::loadModule");

    mModules[name] = module;
} // addModule(Module *)


void ModuleManager::loadSwigModule(const String &dllName)
{
    SwigModule *module = 0;

    try
    {
        module = new SwigModule(dllName);
        module->load();
        addModule(module);
    } // try
    catch (...)
    {
        if (module)
            delete module;

        throw;
    } // catch   
}

void ModuleManager::loadModule(const String &dllName)
{
    Module *module = 0;

    try
    {
        module = new Module(dllName);
        module->load();
        addModule(module);
    } // try
    catch (...)
    {
        if (module)
            delete module;

        throw;
    } // catch   
} // loadModule(const String &)


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
    ModuleMap::iterator itr;
    for (itr = mModules.begin(); itr != mModules.end(); ++itr)
    {
        itr->second->unload();
        delete itr->second;
    } // if

    mModules.clear();
}

void ModuleManager::initializeModules()
{
    ModuleMap::iterator itr;
    for (itr = mModules.begin(); itr != mModules.end(); ++itr)
        itr->second->initialize();
}
