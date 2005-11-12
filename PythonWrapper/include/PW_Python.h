#ifndef _PW_Python_h_
#define _PW_Python_h_

#ifdef  _DEBUG

#define NDEBUG
#undef  _DEBUG
#include <Python.h>
#undef  NDEBUG
#define _DEBUG

#else

#include <Python.h>

#endif

#endif
