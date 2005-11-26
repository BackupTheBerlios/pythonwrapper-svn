#ifndef _PWModule_h_
#define _PWModule_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWDLib.h"

namespace pw
{
    class Module
    {
    public:
        typedef void (*InitFunction)();
        typedef const char *(*GetModuleName)();
        
    public:
        Module(const String &library);
        ~Module();

        void load();
        void unload();

        const String &getName() const;
    protected:
        PW_DLIB mDLib;
        String mName;
    };
}

#endif
