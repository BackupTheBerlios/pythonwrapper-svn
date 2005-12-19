#ifndef _PWModuleManager_h_
#define _PWModuleManager_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWSingleton.h"
#include "PWModule.h"

#include <map>

namespace pw
{
    class PW_EXPORT ModuleManager : public Singleton<ModuleManager>
    {
    public:
        static ModuleManager &getSingleton();
        static ModuleManager *getSingletonPtr();

    public:
        ModuleManager();
        ~ModuleManager();

        void loadModule(const String &dllName);
        void loadSwigModule(const String &dllName);
        void unloadModule(const String &dllName);

        Module *findModule(const String &name);

        void initializeModules();

        void unloadAll();

    private:
        void addModule(Module *module);

    private:
        typedef std::map<String, Module *> ModuleMap;
        ModuleMap mModules;
    };
}

#endif
