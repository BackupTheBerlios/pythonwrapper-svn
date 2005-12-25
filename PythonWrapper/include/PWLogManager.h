#ifndef _PWLogManager_h_
#define _PWLogManager_h_

#include "PWCommon.h"
#include "PWSingleton.h"
#include "PWString.h"

#include <iostream>
#include <fstream>

#define PW_LOG(msg, funct, level) if (pw::LogManager::isSafe(level)) pw::LogManager::unsafeLog(msg, funct, __FILE__, __LINE__)

namespace pw
{
    class PW_EXPORT LogManager : public Singleton<LogManager>
    {
    public:
        /**
         * The amount of information to log.  Low only logs errors, Medium
         * logs errors and warnings, High logs everything.
         */
        enum LogLevel {Low, Medium, High};

    public:
        static inline bool isSafe(LogLevel level)
        { return sInstance && level <= sInstance->mLevel; }

        static inline void unsafeLog(const String &message, const String &function,
                        const String &file, unsigned int line)
        { sInstance->mFile  << function << " : " << message << std::endl; }

        static void log(const String &message, const String &function,
                        const String &file, unsigned int line, LogLevel level);

        /**
         * Returns a reference to the LogManager singleton.
         * @remarks
         *      You are responsible for ensuring that the singleton has been
         *      created before using this method.  If you are unsure if in a
         *      section of code if it has been created you should use the
         *      getSingletonPtr function instead.
         * @note
         *      This will cause an access violation if the LogManager has
         *      not been created.
         * @returns
         *      A reference to the singleton.
         */
        static inline LogManager &getSingleton()
        {
            assert(sInstance);
            return *sInstance;
        } // getSingleton()


        /**
         * Returns a pointer to the LogManager singleton.
         * @remarks
         *      This returns 0 if the singleton has not been created.
         * @returns
         *      A pointer to the LogManager singleton, or 0 if it has not
         *      been created.
         */
        static inline LogManager *getSingletonPtr()
        {
            return sInstance;
        } // getSingletonPtr()

    public:
        /**
         * Constructor.
         * @remarks
         *      If the log file already exists, then it is overwritten.
         * @param filename
         *      The filename to place the information into.
         * 
         */
        LogManager(const String &filename = "PythonWrapper.txt", LogLevel level = Medium);
        ~LogManager();

        LogLevel getLoggingLevel() const;
        void setLoggingLevel(LogLevel level);
        
        void appendLog(const String &message, const String &function,
                       const String &file, unsigned int line, LogLevel level);

    private:
        LogLevel mLevel;
        std::ofstream mFile;
    }; // class PW_EXPORT LogManager
} // namespace pw

#endif
