#include "PWSystem.h"
#include "PWInterpreter.h"
#include "PWExceptions.h"

namespace pw
{
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


    System::System(bool log, const String &logFile, LogManager::LogLevel level)
    : mTM(0), mMM(0), mLM(0)
    {
        if (log && ! LogManager::getSingletonPtr())
            mLM = new LogManager(logFile, level);

        if (! TypeManager::getSingletonPtr())
            mTM = new TypeManager();

        if (! ModuleManager::getSingletonPtr())
            mMM = new ModuleManager();

        PW_LOG("System created.", "System::System", LogManager::High);
    }


    System::~System()
    {
        if (mTM)
            delete mTM;

        if (mMM)
            delete mMM;

        PW_LOG("System destroyed.", "System::~System", LogManager::High);

        if (mLM)
            delete mLM;
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
} // namespace pw
