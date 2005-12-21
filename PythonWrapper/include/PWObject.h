#ifndef _PWObject_h_
#define _PWObject_h_

#include "PWCommon.h"
#include "PWString.h"

namespace pw
{
    /**
     * Wrapper for the basic PyObject struct.
     * @remarks
     *      A pw::Object is always garunteed to point to a valid Python object.
     *      The ReferenceHandler classes will throw exceptions when you try to
     *      feed them a null PyObjects.  Since every Object class (and
     *      subclass) holds a reference to the PyObject it holds, once a
     *      pw::Object is constructed you are garunteed that it points to
     *      something valid.
     */
    class PW_EXPORT Object
    {
    public:
        /**
         * The basic constructor.
         * @remarks
         *      You cannot pass in a PyObject pointer directly into this class.
         *      You have to specify whether the pointer contains a borrowed
         *      reference or a new reference.  You must do that by passing a
         *      PyObject pointer to the NewReference or BorrowedReference
         *      class.
         * @see NewReference
         * @see BorrowedReference
         * @param ref
         *      The reference handler for the PyObject pointer.
         */
        Object(ReferenceHandler &ref);


        /**
         * Empty constructor.
         * @remarks
         *      This creates a None object.
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
         * @param rhs
         *      The Object to copy.
         */
        virtual Object &operator=(const Object &rhs);


        /**
         * Returns a borrowed reference to the object that this contains.
         * @remarks
         *      You must NOT call Py_DECREF on the return value of this
         *      function.  If you wish to pass a PyObject into a
         *      function which steals a reference, you should call the
         *      getNewReference function instead.  The return value is
         *      garaunteed to be valid for at least the lifetime of this
         *      Object (or when it is reassigned with operator=).
         * @returns
         *      A pointer to the PyObject that this Object contains, garunteed
         *      to be a valid pointer.
         */
        virtual inline PyObject *borrowReference() const
        { return mPtr; }


        /**
         * Returns a new reference to the PyObject that this contains.
         * @remarks
         *      You MUST call Py_DECREF on the return value of this function or
         *      pass it to a Python/C function which "steals a reference" or
         *      you will create a memory leak.
         * @returns
         *      A pointer to the PyObject this Object contains, which is
         *      increfed before returning.
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
         * @param attr
         *      The attribute to check for.
         * @returns
         *      True if the object has attr, false otherwise.
         */
        virtual inline bool hasAttr(const Object &attr)
        { return PyObject_HasAttr(mPtr, attr.borrowReference()) != 0; }


        /**
         * Obtains the attribute from this Object and returns it, same as
         * return Object.__dict__[str(attr)]
         * @param attr
         *      The name of the attribute to retrieve.
         * @returns
         *      The attribute specified by attr.
         * @throws PythonException
         *      If an error occurs duing the function call.  This would most
         *      likely be caused by the attribute not existing.
         */
        virtual Object getAttr(const Object &attr) const;


        /**
         * Sets the attribute, same as:
         * Object.__dict__[str(attr)] = value;
         * @param attr
         *      The name of the attribute to set.
         * @throws PythonException
         *      If an error occurs duing the function call.
         */
        virtual void setAttr(const Object &attr, const Object &value);

        
        /**
         * Deletes the attribute, same as:
         * del Object.__dict__[str(attr)]
         * @param attr
         *      The name of the attribute to delete.
         * @throws PythonException
         *      If an error occurs duing the function call, this would
         *      more than likely be caused by the attribute not existing.
         */
        virtual void delAttr(const Object &attr);


        /**
         * Returns the attribute.
         * @throws PythonException
         *      If a python error occurred during the call.  This
         *      would most likely be called by attr not being a member of the
         *      object.
         */
        virtual Object getAttr(const String &attr) const;


        /**
         * Sets the attribute.
         * @throws PythonException
         *      If a python error occurred during the call.
         */
        virtual void setAttr(const String &attr, const Object &value);


        /**
         * Deletes the attribute.
         * @throws PythonException
         *      If a python error occurred during the call.  This would most
         *      likely be caused by attr not being a member of the Object.
         */
        virtual void delAttr(const String &attr);


        /**
         * Calls the object with no parameters.
         * Equivalent to obj()
         * @returns
         *      The return value of the function call.  If the function does
         *      not return a value, None is returned.
         * @throws PythonException
         *      If an error occurred during the call.
         */
        virtual Object operator()();


        /**
         * Calls the object with parameters in the tuple args.
         * If args is a tuple then the function expands it.  As a convenience,
         * if args is not a tuple then this function assumes that you want to
         * call the function with a single parameter.
         * @remarks
         *      If you are calling a function with multiple parameters you
         *      should use the Tuple::build function to pack the arguments,
         *      then pass this Tuple into operator().  If you only have one
         *      parameter, you may pass it into operator() directly and not
         *      build a tuple around it.
         * @returns
         *      The return value of the function call.  If the function does
         *      not return a value, None is returned.
         * @throws PythonException
         *      If an error occurred during the call.
         * @see Tuple::build
         */
        virtual Object operator()(const Object &args);

        
        /**
         * Calls the object with parameters, and named parameters, such as
         * calling the object as obj(param1, param2, named1=val1, named2=val2)
         * Equivalent to obj(*args, named1=val1, named2=val2).
         * @remarks
         *      If you are calling a function with multiple parameters you
         *      should use the Tuple::build function to pack the arguments,
         *      then pass this Tuple into operator().  If you only have one
         *      parameter, you may pass it into operator() directly and not
         *      build a tuple around it.
         * @returns
         *      The return value of the function call.  If the function does
         *      not return a value, None is returned.
         * @throws PythonException
         *      If an error occurred during the call.
         */
        virtual Object operator()(const Object &args, const Dict &namedArgs);


        /**
         * Calls function in the object with no parameters.  Equivalent to:
         * object.function()
         * @returns
         *      The return value of the function call.  If the function does
         *      not return a value, None is returned.
         * @throws PythonException
         *      If an error occurred during the call.
         */
        virtual inline Object call(const String &function)
        { return getAttr(function)(); }


        /**
         * Calls the function specified with args.  Equivalent to:
         * object.function(*args)
         * @remarks
         *      If you are calling a function with multiple parameters you
         *      should use the Tuple::build function to pack the arguments,
         *      then pass this Tuple into operator().  If you only have one
         *      parameter, you may pass it into operator() directly and not
         *      build a tuple around it.
         * @returns
         *      The return value of the function call.  If the function does
         *      not return a value, None is returned.
         * @throws PythonException
         *      If an error occurred during the call.
         */
        virtual inline Object call(const String &function, const Object &args)
        { return getAttr(function)(args); }


        /**
         * Calls the function specified with args and named arguments.
         * Equivalent to:
         * object.function(*args, key1=value1, key2=value2, ...)
         * @remarks
         *      If you are calling a function with multiple parameters you
         *      should use the Tuple::build function to pack the arguments,
         *      then pass this Tuple into operator().  If you only have one
         *      parameter, you may pass it into operator() directly and not
         *      build a tuple around it.
         * @returns
         *      The return value of the function call.  If the function does
         *      not return a value, None is returned.
         * @throws PythonException
         *      If an error occurred during the call.
         */
        virtual inline Object call(const String &function, const Object &args,
                                   const Dict &namedArgs)
        { return getAttr(function)(args, namedArgs); }


        /**
         * Returns the reference count of the Python object.
         */
        virtual inline int getRefCount() const
        { return mPtr->ob_refcnt; }
    protected:
        /**
         * Garunteed to be valid at all times.
         */
        PyObject *mPtr;
    }; // class Object
}

#endif
