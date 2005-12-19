#ifndef _PWEmbedded_h_
#define _PWEmbedded_h_

#include "PWCommon.h"

extern "C"
PW_EXPORT void PW_addType(const char *type, const char *moduleName, void *typeInfo);

extern "C"
PW_EXPORT void PW_addPyType(PyTypeObject *type, const char *moduleName);

#endif
