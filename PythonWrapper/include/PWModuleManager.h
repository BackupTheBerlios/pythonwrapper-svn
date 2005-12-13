#ifndef _PWModuleManager_h_
#define _PWModuleManager_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWSingleton.h"
#include "PWModule.h"

#include <map>

namespace pw
{
    class ModuleManager : public Singleton<ModuleManager>
    {
    public:
        static ModuleManager &getSingleton();
        static ModuleManager *getSingletonPtr();

    public:
        ModuleManager();
        ~ModuleManager();

        void loadModule(const String &dllName);
        void unloadModule(const String &dllName);

        void unloadAll();

    private:
        typedef std::map<String, Module *> ModuleMap;
        ModuleMap mModules;
    };
}

#endif
