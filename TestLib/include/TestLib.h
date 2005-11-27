#ifndef _TestLib_h_
#define _TestLib_h_

#if defined(__WIN32__) || defined(_WIN32)
#	if defined(__MINGW32__)
#       define LIB_EXPORT
#   else
#       if defined(_PW_LIBRARY_BUILD)
#           define LIB_EXPORT  __declspec(dllexport)
#       else
#           define LIB_EXPORT  __declspec(dllimport)
#       endif
#	endif
#else
#   define LIB_EXPORT
#endif

#define ModuleName "_module"

#include <string>
typedef std::string String;

int test();

extern "C" LIB_EXPORT void PW_Init();
extern "C" LIB_EXPORT void PW_Deinit();
extern "C" LIB_EXPORT int  PW_GetCount();
extern "C" LIB_EXPORT const String &PW_GetName();

#endif
