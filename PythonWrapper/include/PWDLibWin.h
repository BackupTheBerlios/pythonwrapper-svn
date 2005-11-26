#ifndef _PWDLibWin_h_
#define _PWDLibWin_h_

#include "PWCommon.h"
#include "PWDLib.h"
#include "PWString.h"

// predefine the structs we use later to avoid including windows.h
struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

namespace pw
{
    class DLibWin : public DLib
    {
    public:
        DLibWin(const String &libraryName);
        virtual ~DLibWin();

        virtual void load();
        virtual void unload();

        virtual bool isLoaded();

        virtual void *getSymbol(const String &symbol) const;
    protected:
        hInstance mLib;
    };
}

#endif
