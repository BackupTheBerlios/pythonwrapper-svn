#ifndef _PWExtract_h_
#define _PWExtract_h_

#include "PWCommon.h"
#include "PWExceptions.h"
#include "PWString.h"
#include "PWTypeManager.h"

namespace pw
{
    namespace inner
    {
        void PW_EXPORT _extract(PyObject *obj, bool &val);
        void PW_EXPORT _extract(PyObject *obj, double &val);
        void PW_EXPORT _extract(PyObject *obj, unsigned short &val);
        void PW_EXPORT _extract(PyObject *obj, unsigned int &val);
        void PW_EXPORT _extract(PyObject *obj, unsigned long &val);
        void PW_EXPORT _extract(PyObject *obj, unsigned long long &val);
        void PW_EXPORT _extract(PyObject *obj, short &val);
        void PW_EXPORT _extract(PyObject *obj, int &val);
        void PW_EXPORT _extract(PyObject *obj, long &val);
        void PW_EXPORT _extract(PyObject *obj, long long &val);
        void PW_EXPORT _extract(PyObject *obj, float &val);
        void PW_EXPORT _extract(PyObject *obj, const char *&val);
        void PW_EXPORT _extract(PyObject *obj, String &val);
    }

    /**
     * Extracts a value from a Python object.  You can use this function to
     * obtain primitive data types from a Python Object.  This includes all
     * number related types (ints, floats), as well as strings (const char *,
     * String), and bools.  Note that this does not do any conversion.  This
     * function will throw an exception if the type is wrong.
     * @param object the object to convert
     * @returns the converted value of type T
     * @throws PythonException 
     */
    template <class T>
    T extract(const Object &object)
    {
        T val;
        inner::_extract(object.borrowReference(), val);
        PW_PyExcept_Check("extract<T>(const Object &)");
        return val;
    } // extract


    /**
     * Extracts a pointer from a SWIG object.  Note that T must be a pointer,
     * and that pointer must have been registered with the TypeManager for the
     * conversion to succeed.  The disown variable sets whether the python
     * object has ownership (that is, if the python object should delete the
     * C++ object when its refcount drops to 0).  If if disown is set to true,
     * then the python object no longer owns the pointer, and you are
     * responcible for deleting the returned pointer.
     * @param object the object that is to be converted
     * @param disown whether the python object is disowning the pointer
     * @returns the converted value
     * @throws Exception if the type T is not registered with the TypeManger.
     */
    template <class T>
    T extract(const Object &object, bool disown)
    {
        String name = typeid(T).name();
        if (name.find("class ") == 0)
            name = name.substr(6);

        TypeManager::TypeInfoPair tip = TypeManager::getSingleton().findConverter(name);
        return (T)tip.first->convert(object.borrowReference(), 0, disown);
    } // extract
} // namespace pw

#endif
