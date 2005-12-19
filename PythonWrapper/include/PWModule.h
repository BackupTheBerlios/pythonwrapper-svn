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
        
    public:
        Module(const String &library);
        Module(const String &library, const String &name);
        virtual ~Module();

        virtual void load();
        virtual void unload();

        virtual const String &getName() const;
        virtual InitFunction getInit() const;

        virtual void initialize();
    protected:
        PW_DLIB mDLib;
        String mName;
        InitFunction mInit;
    };
}

#endif
