%{
#ifdef PW_Embedded

#ifdef __cplusplus
extern "C"
{
#endif

#include "PWEmbedded.h"

SWIGEXPORT PyTypeObject *PW_GetType()
{ return _PySwigObject_type(); }


SWIGEXPORT PyObject *PW_ToPyObject(void *obj, void *typeInfo, int disown)
{
	return SWIG_Python_NewPointerObj(obj, (swig_type_info*)typeInfo, disown ? SWIG_POINTER_OWN : 0);
}


SWIGEXPORT void *PW_ToPointer(PyObject *obj, int disown)
{
	PySwigObject *sobj = (PySwigObject *)obj;
	void *toReturn = 0;
	SWIG_Python_ConvertPtrAndOwn(obj, &toReturn, sobj->ty, disown ? SWIG_POINTER_DISOWN : 0, 0);
	return toReturn;
}


SWIGEXPORT void PW_RegisterConverters(const char *module)
{
	swig_module_info *mi = SWIG_Python_GetModule();
	size_t i;
	for (i = 0; i < mi->size; ++i)
		PW_addType(mi->types[i]->str, module, mi->types[i]);
	
	PW_addPyType(PySwigObject_type(), module);
}

#ifdef __cplusplus
}
#endif

#endif
%}