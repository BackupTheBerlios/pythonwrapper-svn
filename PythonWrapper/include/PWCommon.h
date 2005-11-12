#ifndef _PWCommon_h_
#define _PWCommon_h_

#if defined( __WIN32__ ) || defined( _WIN32 )
#	if defined( __MINGW32__ )
#       define _PW_EXPORT
#   else
#       if defined(_PW_LIBRARY_BUILD)
#           define _PW_EXPORT  __declspec(dllexport)
#       else
#           define _PW_EXPORT  __declspec(dllimport)
#       endif
#	endif
#else
#   define _PW_EXPORT
#endif

#include <PW_Python.h>

#endif
