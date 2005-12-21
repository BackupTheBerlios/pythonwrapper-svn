#include "PWModuleManager.h"
#include "PWDLib.h"
#include "PWExceptions.h"
#include "PWSwigModule.h"

namespace pw
{
    ModuleManager *Singleton<ModuleManager>::sInstance = 0;


    ModuleManager &ModuleManager::getSingleton()
    {
        return *Singleton<ModuleManager>::sInstance;
    } // getSingleton()


    ModuleManager *ModuleManager::getSingletonPtr()
    {
        return Singleton<ModuleManager>::sInstance;
    } // getSingletonPtr()


    ModuleManager::ModuleManager()
    {
    } // ModuleManager()


    ModuleManager::~ModuleManager()
    {
        unloadAll();
    } // ~ModuleManager()


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
    } // loadSwigModule(const String &)


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
    } // unloadModule(const String &)


    void ModuleManager::unloadAll()
    {
        ModuleMap::iterator itr;
        for (itr = mModules.begin(); itr != mModules.end(); ++itr)
        {
            itr->second->unload();
            delete itr->second;
        } // for

        mModules.clear();
    } // unloadAll()


    void ModuleManager::initializeModules()
    {
        ModuleMap::iterator itr;
        for (itr = mModules.begin(); itr != mModules.end(); ++itr)
            itr->second->initialize();
    } // initializeModules()


    Module *ModuleManager::findModule(const String &name)
    {
        ModuleMap::iterator itr;
        itr = mModules.find(name);
        if (itr == mModules.end())
            PW_Except("Could not find module " + name + ".", "ModuleManager::findModule");

        return itr->second;
    } // findModule(const String &)
} // namespace pw