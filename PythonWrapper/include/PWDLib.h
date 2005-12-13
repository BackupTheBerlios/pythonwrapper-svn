#ifndef _PWDLib_h_
#define _PWDLib_h_

#include "PWCommon.h"
#include "PWString.h"

namespace pw
{
    class PW_EXPORT DLib
    {
    public:
        DLib(const String &libraryName);
        virtual ~DLib();

        virtual const String &getLibraryName() const;

        virtual void load() = 0;
        virtual void unload() = 0;

        virtual bool isLoaded() = 0;

        virtual void *getSymbol(const String &symbol) const = 0;

    protected:
        String mLibraryName;
    };
}

#if defined(__WIN32__) || defined(_WIN32)
#    if defined(__MINGW32__)
#       define PW_EXPORT
#       define PW_DLIB DLibLinux
#       include "PWDLibLinux.h"
#   else
#       define PW_DLIB DLibWin
#       include "PWDLibWin.h"
#    endif
#else
#   define PW_EXPORT
#   define PW_DLIB DLibLinux
#   include "PWDLibLinux.h"
#endif

#endif
