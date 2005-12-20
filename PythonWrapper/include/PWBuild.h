#ifndef _PWBuild_h_
#define _PWBuild_h_

#include "PWCommon.h"
#include "PWHandler.h"
#include "PWString.h"
#include "PWConverterInterface.h"
#include "PWTypeManager.h"

namespace pw
{
    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(unsigned short val)
    { return NewReference(PyLong_FromUnsignedLong((unsigned long)val)); }

    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(unsigned long val)
    { return NewReference(PyLong_FromUnsignedLong(val)); }

    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(unsigned long long val)
    { return NewReference(PyLong_FromUnsignedLongLong(val)); }

    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(short val)
    { return NewReference(PyInt_FromLong((long)val)); }

    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(long val)
    { return NewReference(PyInt_FromLong(val)); }

    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(long long val)
    { return NewReference(PyLong_FromLongLong(val)); }

    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(double val)
    { return NewReference(PyFloat_FromDouble(val)); }

    /**
     * Creates a Python object from val.
     * @param str the string to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(const char *str)
    { return NewReference(PyString_FromString(str)); }

    /**
     * Creates a Python object from val.
     * @param str the string to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(const String &str)
    { return NewReference(PyString_FromString(str.c_str())); }

    /**
     * Creates a Python object from val.
     * @param val the value to convert into a Python object
     * @returns a new Python object 
     */
    inline Object build(bool val)
    { return BorrowedReference(val ? Py_True : Py_False); }

    /**
     * Creates a Python object from a C++ class that has been wrapped with
     * SWIG.  Note that to use this function, T must be a pointer to the class,
     * and the class must be in one of the SWIG modules that you have loaded
     * using ModuleManager.  The disown parameter tells SWIG whether to take
     * ownership of the object.  If disown is set to true then you are
     * "disowning" the val parameter, meaning that when the returned Object's
     * reference count reaches 0 the Python object will call delete on val.
     * 
     * @param val the value to convert into a Python object, this must be a
     *        pointer
     * @param disown whether the C++ class is disowning the deletion duty;
     *        setting disown to true means the python object calls delete
     *        setting disown to false means the python object will not call
     *        delete
     * @returns a new Python object containing the class
     * @throws Exception if the type T is not registered with the TypeManager
     */
    template <class T>
    inline Object build(T val, bool disown)
    {
        String name = typeid(T).name();
        if (name.find("class ") == 0)
            name = name.substr(6);

        TypeManager::TypeInfoPair tip = TypeManager::getSingleton().findConverter(name);
        return NewReference(tip.first->convert((void *)val, tip.second, disown));
    }

}

#endif
