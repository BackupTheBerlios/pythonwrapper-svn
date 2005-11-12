#ifndef _PWObject_h_
#define _PWObject_h_

#include "PWCommon.h"

namespace pw
{
    class ReferenceHandler;  // forward reference

    /**
     * Wrapper for the basic PyObject struct.
     */
    class _PW_EXPORT Object
    {
    public:
        /**
         * The basic constructor.  You cannot pass in a PyObject pointer
         * directly into this class.  You have to specify whether the pointer
         * contains a borrowed reference or a new reference.  You must do that
         * by passing a PyObject pointer to the NewReference or
         * BorrowedReference class.
         * @see NewReference
         * @see BorrowedReference
         * @param ref the reference handler for the PyObject pointer
         */
        Object(ReferenceHandler &ref);


        /**
         * Py_None object.
         */
        Object();


        /**
         * Copy constructor.
         * This is a shallow copy.
         */
        Object(const Object &rhs);


        /**
         * Destructor, always calls Py_DECREF.
         */
        virtual ~Object();


        /**
         * Assignment operator.
         * @param rhs the Object to copy
         */
        virtual Object &operator=(const Object &rhs);

    public:
        static void check(PyObject *ptr);

    protected:
        /**
         * Garunteed to be valid at all times.
         */
        PyObject *mPtr;
    }; // class Object
}

#endif
