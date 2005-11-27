#ifndef _PWCommon_h_
#define _PWCommon_h_

#if defined(__WIN32__) || defined(_WIN32)
#	if defined(__MINGW32__)
#       define PW_EXPORT
#   else
#       pragma warning (disable : 4251)
#       if defined(_PW_LIBRARY_BUILD)
#           define PW_EXPORT  __declspec(dllexport)
#       else
#           define PW_EXPORT  __declspec(dllimport)
#       endif
#	endif
#else
#   define PW_EXPORT
#endif

#include <Python.h>

// Forward definitions
namespace pw
{
    class Object;
    class Dict;
    class List;
    class Tuple;
    class Sequence;
    class ReferenceHandler;
}

#endif
