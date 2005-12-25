#include "PWLogManager.h"
#include "PWExceptions.h"

namespace pw
{
    LogManager *Singleton<LogManager>::sInstance = 0;

    
    void LogManager::log(const String &message, const String &function, const String &file,
                         unsigned int line, LogLevel level)
    {
        LogManager *lm = LogManager::getSingletonPtr();

        if (lm)
            lm->appendLog(message, function, file, line, level);
    } // log(const String &, const String &, const String &, unsigned int, LogLevel)


    LogManager::LogManager(const String &filename, LogLevel level)
        : mLevel(level), mFile(filename.c_str())
    {
        if (!mFile)
            PW_Except("Could not create log file: " + filename, "LogManager::LogManager");

        mFile << "--- Log for PythonWrapper ---" << std::endl;
        
        PW_LOG("LogManager created.", "LogManager::LogManager", LogManager::High);
    } // LogManager(const String &, LogLevel)


    LogManager::~LogManager()
    {
        PW_LOG("LogManager destroyed.", "LogManager::~LogManager", LogManager::High);

        mFile.close();
    } // ~LogManager()


    void LogManager::appendLog(const String &message, const String &function,
                   const String &file, unsigned int line, LogLevel level)
    {
        if (level <= mLevel)
            mFile << function << " : " << message << std::endl;
    } // appendLog
} // namespace pw
