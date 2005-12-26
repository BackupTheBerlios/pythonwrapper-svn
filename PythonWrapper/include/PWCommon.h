#ifndef _PWCommon_h_
#define _PWCommon_h_

#if defined(__WIN32__) || defined(_WIN32)
#    if defined(__MINGW32__)
#       define PW_EXPORT
#   else
#       pragma warning (disable: 4251)
#       pragma warning (disable: 4661)
#       if defined(_PW_LIBRARY_BUILD)
#           define PW_EXPORT  __declspec(dllexport)
#       else
#           define PW_EXPORT  __declspec(dllimport)
#       endif
#    endif
#else
#   define PW_EXPORT
#endif

#include <Python.h>

#ifdef PW_PyThreads
#   define PW_PyAllowThreads Py_BEGIN_ALLOW_THREADS
#   define PW_PyDisallowThreads Py_END_ALLOW_THREADS
#else
#   define PW_PyAllowThreads
#   define PW_PyDisallowThreads
#endif

// Forward declarations
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
