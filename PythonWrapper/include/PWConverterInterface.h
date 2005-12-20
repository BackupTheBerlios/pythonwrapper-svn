#ifndef _PWConverterInterface_h_
#define _PWConverterInterface_h_

#include "PWCommon.h"

namespace pw
{
    /**
     * The converter interface defines conversion methods to convert
     * to and from C++ classes/Python objects.  This is currently designed
     * with SWIG conversion in mind.  This may need to be revised later to
     * handle other library conversions.
     */
    class PW_EXPORT ConverterInterface
    {
    public:
        inline ConverterInterface() {}
        virtual inline ~ConverterInterface() {}

        /**
         * Converts from a Python object to a C++ object.  The disown
         * parameter tells the PyObject to "disown" the C++ object.  If you
         * set disown to true, it means that you are responsible for deleting
         * the returned C++ object, though doing so while valid python objects
         * are pointing at it may result in a crash.
         * @param obj the Python object that contains the object
         * @param disown whether the python object should disown the object it
         *        contains
         */
        virtual void *convert(PyObject *obj, bool disown) = 0;

        /**
         * Converts from a C++ object to a Python object.  The disown
         * parameter specifies whether or not the PyObject owns the C++
         * pointer.  If you set disown to true, the python object will
         * automatically delete the C++ object when the reference count drops
         * to zero.
         * @param obj the C++ object that will be stored
         * @param typeInfo the type info to use to convert the object
         * @param disown whether the returned object should be responcible for
         *        the object's deletion
         */
        virtual PyObject *convert(void *obj, void *typeInfo, bool disown) = 0;
    };
}

#endif
