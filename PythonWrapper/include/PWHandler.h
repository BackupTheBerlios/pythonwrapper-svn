#ifndef _PWHandler_h_
#define _PWHandler_h_

#include "PWCommon.h"
#include "PWExceptions.h"

namespace pw
{
    /**
     * Base interface for the reference handler class.  See the NewReference
     * and BorrowedReference classes for details.
     * @see NewReference
     * @see BorrowedReference
     */
    class PW_EXPORT ReferenceHandler
    {
    public:
        inline ReferenceHandler() {}
        virtual ~ReferenceHandler() {};

        virtual inline PyObject *getPtr() const = 0;

        virtual inline void contained() = 0;
        virtual inline bool isContained() const = 0;
    };
    /**
     * This is the base "handling" class for the C PyObject struct.  No
     * pw class may ever take a raw pointer to a PyObject *.  Instead any
     * member function which needs a raw PyObject * pointer must instead
     * pass either a NewReference object or a BorrowedReference object, which
     * takes care of the INCREF portion of python's reference counting.
     * Any object in the Python/C API which specifies it returns a "New
     * Reference" should use the NewReference class (which does not call
     * Py_INCREF).  Any function in the Python/C API which specifies it
     * returns a "Borrowed Reference" should use the BorrowedReference
     * class (which does call Py_INCREF).
     * @see BorrowedReference
     */
    class PW_EXPORT NewReference : public ReferenceHandler
    {
    public:
        /**
         * Basic constructor, throws NullObjectException and PythonException
         * (plus its subclasses).
         * @param obj the PyObject pointer to wrap, will throw exception if
         *            null
         * @throws PythonException if obj is 0 and PyErr_Occurred returns
         *         true
         * @throws NullObjectException if obj is 0 and PyErrOccurred returns
         *         false
         */
        explicit inline NewReference(PyObject *obj)
            : mObj(obj), mContained(false), mOwn(false)
        {
            if (!obj)
            {
                PW_PyExcept_Check("NewReference::NewReference(PyObject *)");
                PW_NullExcept("NULL value passed into NewReference constructor.",
                              "Object::check");
            } // if
        } // NewReference(PyObject *)


        /**
         * Copy constructor.
         */
        inline NewReference(const NewReference &rhs)
            : mContained(false), mOwn(true)
        {
            mObj = rhs.mObj;

            assert(mObj);
            Py_INCREF(mObj);
        }


        /**
         * Destructor.
         */
        virtual inline ~NewReference()
        {
            if (!mContained || mOwn)
                Py_DECREF(mObj);
        } // ~NewReference()


        /**
         * Returns the pointer this containeds.
         * @returns the pointer this containeds
         */
        virtual inline PyObject *getPtr() const
        { return mObj; }


        /**
         * Returns if this object is already contained by an
         * Object class.  This is protected so that only the
         * friend class Object can call it (since all other
         * classes should use Object instead of a handler.
         */
        virtual inline bool isContained() const
        { return mContained; }


        /**
         * This function should be called when this is contained by an
         * Object class.
         */
        virtual inline void contained()
        {
            if (mContained)
                Py_INCREF(mObj);
            else
            {
                mContained = true;
                mOwn = false;
            }
        }

    protected:
        PyObject *mObj;
        bool mContained;
        bool mOwn;

    private:
        NewReference &operator=(const NewReference &);
    }; // class NewReference



    /**
     * This class represents a PyObject which is a "BorrowedReference",
     * meaning if the object is to persist, it needs to have Py_INCREF called
     * to ensure that the object is not inadvertantly destroyed while we are
     * holding a reference to it.  Any Python/C function which specifies that
     * it returns a "Borrowed Reference" should use this class.  When a
     * Python/C function specifies that it returns a new reference the
     * NewReference class should be used.
     * @see NewReference
     */
    class PW_EXPORT BorrowedReference : public NewReference
    {
    public:
        /**
         * This increments the reference count of obj (provided that obj
         * is non-null).
         * @param obj the PyObject pointer to wrap, will throw exception if
         *            null
         * @throws PythonException if obj is 0 and PyErr_Occurred returns
         *         true
         * @throws NullObjectException if obj is 0 and PyErrOccurred returns
         *         false
         */
        explicit inline BorrowedReference(PyObject *obj)
            : NewReference(obj)
        {
            Py_INCREF(mObj);
        } // NewReference

        /**
         * Copy constructor.
         */
        inline BorrowedReference(const BorrowedReference &rhs)
            : NewReference(rhs.mObj)
        {
            Py_INCREF(mObj);
        }

        /**
         * Destructor.
         */
        virtual inline ~BorrowedReference()
        {
        } // ~BorrowedReference()

    private:
        BorrowedReference &operator=(const BorrowedReference &);
    }; // class BorrowedReference
}

#endif
