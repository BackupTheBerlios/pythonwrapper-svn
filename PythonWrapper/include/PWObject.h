#ifndef _PWObject_h_
#define _PWObject_h_

#include "PWCommon.h"
#include "PWString.h"

namespace pw
{
    /**
     * Wrapper for the basic PyObject struct.
     */
    class PW_EXPORT Object
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


        /**
         * Returns a borrowed reference to the object that this contains.
         * You must not call Py_DECREF on the return value of this function.
         * If you wish to pass the return value into a function which
         * steals a reference, you should call the getNewReference function
         * instead.
         * @returns a pointer to the PyObject that this Object contains,
         *          garunteed to be a valid pointer
         * @remarks The return value of this function is garunteed to remain
         *          valid until this Object is destroyed or it is reassigned
         *          with a call to operator=.
         */
        virtual inline PyObject *borrowReference() const
        { return mPtr; }


        /**
         * Returns a new reference to the PyObject that this contains.  You
         * MUST call Py_DECREF on the return value of this function or pass
         * it to a Python/C function which "steals a reference" or you will
         * create a memory leak.
         */
        virtual inline PyObject *newReference() const
        {
            Py_INCREF(mPtr);
            return mPtr;
        } // getNewReference


        /**
         * Returns the length of this object, like calling len(obj).  Returns
         * -1 if the object does not have a length (that is, does not define
         * an __len__ function to call).
         * @returns the length of the object or -1 if the object does not have
         *          a length
         */
        virtual int length() const;


        /**
         * Returns true if this object has the attribute "attr", false otherwise.
         * Does not throw an exception.
         * @returns true if the object has attr, false otherwise
         */
        virtual inline bool hasAttr(const Object &attr)
        { return PyObject_HasAttr(mPtr, attr.borrowReference()) != 0; }


        /**
         * Obtains the attribute from this Object and returns it, same as
         * return Object.__dict__[str(attr)]
         */
        virtual Object getAttr(const Object &attr) const;


        /**
         * Sets the attribute, same as:
         * Object.__dict__[str(attr)] = value;
         */
        virtual void setAttr(const Object &attr, const Object &value);

        
        /**
         * Deletes the attribute, same as:
         * del Object.__dict__[str(attr)]
         */
        virtual void delAttr(const Object &attr);


        /**
         * Returns the attribute.
         */
        virtual Object getAttr(const String &attr) const;


        /**
         * Sets the attribute.
         */
        virtual void setAttr(const String &attr, const Object &value);


        /**
         * Deletes the attribute.
         */
        virtual void delAttr(const String &attr);


        /**
         * Calls the object with no parameters.
         * Equivalent to obj()
         * @returns the return value of the function call
         * @throws PythonException if an error occurred during the call
         */
        virtual Object operator()();


        /**
         * Calls the object with parameters.
         * Equivalent to obj(*args)
         * @returns the return value of the function call
         * @throws PythonException if an error occurred during the call
         */
        virtual Object operator()(const Tuple &args);

        
        /**
         * Calls the object with parameters, and named parameters, such as
         * calling the object as obj(param1, param2, named1=val1, named2=val2)
         * Equivalent to obj(*args)
         * @returns the return value of the function call
         * @throws PythonException if an error occurred during the call
         */
        virtual Object operator()(const Tuple &args, const Dict &namedArgs);


        /**
         * Calls function in the object with no parameters.  Equivalent to:
         * object.function()
         */
        virtual inline Object call(const String &function)
        { return getAttr(function)(); }


        /**
         * Calls the function specified with args.  Equivalent to:
         * object.function(*args)
         */
        virtual inline Object call(const String &function, const Tuple &args)
        { return getAttr(function)(args); }

        /**
         * Calls the function specified with args and named arguments.
         * Equivalent to:
         * object.function(*args, key1=value1, key2=value2, ...)
         */
        virtual inline Object call(const String &function, const Tuple &args,
                                   const Dict &namedArgs)
        { return getAttr(function)(args, namedArgs); }

    protected:
        /**
         * Garunteed to be valid at all times.
         */
        PyObject *mPtr;
    }; // class Object
}

#endif
