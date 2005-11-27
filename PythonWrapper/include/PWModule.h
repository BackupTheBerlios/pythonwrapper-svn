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
        virtual ~Module();

        virtual void load();
        virtual void unload();

        virtual const String &getName() const;
    protected:
        PW_DLIB mDLib;
    };
}

#endif
