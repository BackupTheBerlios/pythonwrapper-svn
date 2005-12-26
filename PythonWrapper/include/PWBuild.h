#ifndef _PWBuild_h_
#define _PWBuild_h_

#include "PWCommon.h"
#include "PWHandler.h"
#include "PWString.h"
#include "PWConverterInterface.h"
#include "PWTypeManager.h"

namespace pw
{
    namespace inner
    {
        inline NewReference build(unsigned short val)
        { return NewReference(PyLong_FromUnsignedLong((unsigned long)val)); }

        inline NewReference build(unsigned long val)
        { return NewReference(PyLong_FromUnsignedLong(val)); }

        inline NewReference build(unsigned long long val)
        { return NewReference(PyLong_FromUnsignedLongLong(val)); }

        inline NewReference build(short val)
        { return NewReference(PyInt_FromLong((long)val)); }
        
        inline NewReference build(int val)
        { return NewReference(PyInt_FromLong(val)); }

        inline NewReference build(long val)
        { return NewReference(PyInt_FromLong(val)); }

        inline NewReference build(long long val)
        { return NewReference(PyLong_FromLongLong(val)); }

        inline NewReference build(double val)
        { return NewReference(PyFloat_FromDouble(val)); }

        inline NewReference build(const char *str)
        { return NewReference(PyString_FromString(str)); }

        inline NewReference build(const String &str)
        { return NewReference(PyString_FromString(str.c_str())); }

        inline BorrowedReference build(bool val)
        { return BorrowedReference(val ? Py_True : Py_False); }
    } // namespace inner


    /**
     * Builds a python object out of val.
     * @remarks
     *      You generally should not have to specify the template parameter for
     *      this function.  Your compiler should be able to figure it out based
     *      on the parameter you provide it:
     *          build(7);
     *          build("hello world");
     *      Note that you may only use primitive data types to this function
     *      (bools, floats, ints, const char *, and so on).
     * @param val
     *      The value to build the Object from.
     * @returns
     *      A new Python object containing val.
     */
    template <class T>
    inline Object build(T val)
    { return inner::build(val); }


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
