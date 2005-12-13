#ifndef _TSCommon_h_
#define _TSCommon_h_

#if defined(__WIN32__) || defined(_WIN32)
#    if defined(__MINGW32__)
#       define TS_EXPORT
#   else
#       pragma warning (disable: 4251)
#       pragma warning (disable: 4661)
#       if defined(TS_LIBRARY_BUILD)
#           define TS_EXPORT  __declspec(dllexport)
#       else
#           define TS_EXPORT  __declspec(dllimport)
#       endif
#    endif
#else
#   define TS_EXPORT
#endif

#endif
