%{
#ifdef PW_Embedded

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*F_addType)(const char *, const char *, void *);
typedef void (*F_addPyType)(PyTypeObject *, const char *);

SWIGEXPORT PyTypeObject *PW_GetType()
{ return _PySwigObject_type(); }


SWIGEXPORT PyObject *PW_ToPyObject(void *obj, void *typeInfo, int disown)
{
	return SWIG_Python_NewPointerObj(obj, (swig_type_info*)typeInfo, disown ? SWIG_POINTER_OWN : 0);
}


SWIGEXPORT void *PW_ToPointer(PyObject *obj, void *, int disown)
{
	PySwigObject *sobj = (PySwigObject *)obj;
	void *toReturn = 0;
	SWIG_Python_ConvertPtrAndOwn(obj, &toReturn, sobj->ty, disown ? SWIG_POINTER_DISOWN : 0, 0);
	return toReturn;
}


SWIGEXPORT void PW_RegisterConverters(const char *module, F_addType addType, F_addPyType addPyType)
{
	swig_module_info *mi = SWIG_Python_GetModule();
	size_t i;
	for (i = 0; i < mi->size; ++i)
		addType(mi->types[i]->str, module, mi->types[i]);
	
	addPyType(PySwigObject_type(), module);
}

#ifdef __cplusplus
}
#endif

#endif
%}
