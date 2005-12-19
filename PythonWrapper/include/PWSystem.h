#ifndef _PWSystem_h_
#define _PWSystem_h_

#include "PWCommon.h"
#include "PWTypeManager.h"
#include "PWModuleManager.h"

namespace pw
{
    class PW_EXPORT System : public Singleton<System>
    {
    public:
        static System &getSingleton();
        static System *getSingletonPtr();

    public:
        System();
        ~System();

        void loadModule(const String &dllName);
        void loadSwigModule(const String &dllName);

        void initialize();
        void finalize();

    private:
        TypeManager *mTM;
        ModuleManager *mMM;
    };
}

#endif
