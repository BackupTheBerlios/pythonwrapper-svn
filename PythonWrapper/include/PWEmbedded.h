#ifndef _PWEmbedded_h_
#define _PWEmbedded_h_

#include "PWCommon.h"

extern "C"
PW_EXPORT void PW_addType(const char *str, void *module);

extern "C"
PW_EXPORT void PW_addPyType(PyTypeObject *type, void *module);

#endif
