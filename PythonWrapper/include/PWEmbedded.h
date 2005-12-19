#ifndef _PWEmbedded_h_
#define _PWEmbedded_h_

#include "PWCommon.h"

extern "C"
PW_EXPORT void PW_addType(const char *type, const char *name, void *typeInfo);

extern "C"
PW_EXPORT void PW_addPyType(PyTypeObject *type, const char *name);

#endif
