#ifndef _PWDLibLinux_h_
#define _PWDLibLinux_h_

#include "PWCommon.h"
#include "PWDLib.h"
#include "PWString.h"

namespace pw
{
    class DLibLinux : public DLib
    {
    public:
        DLibLinux(const String &libraryName);
        virtual ~DLibLinux();

        virtual void load();
        virtual void unload();

        virtual bool isLoaded();

        virtual void *getSymbol(const String &symbol) const;
    protected:
        void *mLib;
    };
}

#endif
