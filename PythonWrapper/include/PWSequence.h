#ifndef _PWSequence_h_
#define _PWSequence_h_

#include "PWCommon.h"
#include "PWObject.h"

namespace pw
{
    /**
     * Wrapper for any python sequence object.
     * @remarks
     *      This was made with a custom sequence object in mind, but this
     *      should work with any object which implements the sequence
     *      interface.
     */
    class PW_EXPORT Sequence : public Object
    {
    public:
        /**
         * Constructor.
         * @remarks
         *      The PyObject this class wraps must implement the sequence
         *      interface.
         * @param ref
         *      The ReferenceHandler for a sequence object.
         * @throws Exception
         *      If the object passed in is not a Sequence.
         */
        Sequence(ReferenceHandler &ref);


        /**
         * Destructor.
         */
        virtual ~Sequence();

        /**
         * Assignment operator.
         * @param rhs
         *      The object to assign to this object.  rhs must be a Python
         *      Sequence object.
         * @throws Exception
         *      If the object passed in is not a Sequence.
         */
        virtual Sequence &operator=(const Object &rhs);

        /**
         * Concatenation.
         * @remarks
         *      This should be equivalent to o1 + o2 in python.
         * @param rhs
         *      A sequence object.
         * @throws PythonException
         *      If an error occurred during the operation.
         */
        virtual Sequence operator+(const Sequence &rhs) const;


        /**
         * Repeats the sequence count times.  This is equivalent to the python
         * code:
         *  seq * count
         * @param count
         *      The number of times to repeat this object.
         * @returns
         *      This sequence object repeated count times.
         * @throws PythonException
         *      If this object 
         */
        virtual Sequence operator*(int count) const;


        /**
         * Returns true if this sequence object contains obj, false otherwise.
         * @param obj
         *      The object to check for.
         * @returns
         *      True if this sequence object contains obj, false otherwise.
         */
        virtual bool contains(const Object &obj) const;


        /**
         * Returns the index of obj, or -1 if it is not found.
         * @param obj
         *      The object to find in the sequence.
         * @returns
         *      The index of obj or -1 if it is not found.
         */
        virtual int index(const Object &obj) const;


        /**
         * Counts the number of times obj appears in the sequence.
         * @param obj
         *      The object to search for.
         * @returns
         *      The number of times obj appears in the sequence.
         */
        virtual int count(const Object &obj) const;


        /**
         * Returns the object at index.
         * @param index
         *      The index to retrieve.
         * @returns
         *      The object at index.
         * @throws PythonException
         *      If an exception was thrown while retrieving the index.  This
         *      would most likely be caused by the index being out of range.
         */
        virtual Object getItem(int index) const;


        /**
         * Sets the item at the specified index.
         * @param index
         *      The index to put obj at.
         * @param obj
         *      The object to assign.
         * @throws PythonException
         *      If an error occurred while setting the item.  This would likely
         *      be due to an index out of bounds or an immutable sequence.
         */
        virtual void setItem(int index, const Object &obj);


        /**
         * Deletes the object at the specified index.
         * @param index
         *      The location of the item to delete.
         * @throws PythonException
         *      If an error occurred while deleting the index.  This would most
         *      likely be caused by an index out of bounds or a sequence which
         *      does not implement the __delitem__ method.
         */
        virtual void delItem(int index);


        /**
         * Returns a portion of this list specified by the slice.
         * @remarks
         *      This works just like regular slicing in python does where start
         *      is the first portion of the slice and stop is the second
         *      portion.  For example:
         *        seq[start:stop]
         *      This is why it is ok to have negative values for start and
         *      stop as this would be analagous to having negative values in
         *      the slice.
         * @param start
         *      The beginning of the slice.
         * @param stop
         *      The end of the slice.
         * @returns
         *      The result of the slice operation.
         * @throws PythonException
         *      If there was an error while getting the slice.
         */
        virtual Sequence getSlice(int start, int stop) const;


        /**
         * Sets the slice to be obj.  Note that the object that is passed in
         * must be an interable.
         * @param start
         *      The beginning of the slice.
         * @param stop
         *      The end of the slice.
         * @param obj
         *      The sequence object to set the slice to.
         * @throws PythonException
         *      If an exception occurred.  This would more than likely be
         *      thrown if the sequence is immutable, does not implement the
         *      __setslice__ method, or if obj is not an iterable.
         */
        virtual void setSlice(int start, int stop, const Sequence &seq);


        /**
         * Deletes the objects specified by the slice.
         * @param start
         *      The start of the slice
         * @param stop
         *      The end of the slice
         * @throws PythonException
         *      If an error occurred while deleting the slice.  This would most
         *      likely be caused by an index out of bounds or a sequence which
         *      does not implement the __delslice__ method.
         */
        virtual void delSlice(int start, int stop);


        /**
         * Returns the length of the object or -1.
         * @returns
         *      The length of the object or -1 if the object does not implement
         *      __len__.
         */
        virtual int length() const;


        /**
         * Returns the sequence as a tuple.
         * @remarks
         *      This is basically equivalent to calling the tuple constructor
         *      with the python sequence:
         *        return tuple(seq)
         *      This should succeed for all Sequence objects (and not throw an
         *      exception) unless an unexpected exception occurrs during the
         *      iteration.
         * @returns
         *      A tuple object with each index corresponding to the indexes of
         *      this sequence.
         * @throws PythonException
         *      This should generally only occur if this sequence object throws
         *      an unexpected exception during iteration (IE something other
         *      than stop iteration).
         */
        virtual Tuple asTuple() const;

        /**
         * Returns the sequence as a list.
         * @remarks
         *      This is basically equivalent to calling the list constructor
         *      with the python sequence:
         *        return list(seq)
         *      This should succeed for all Sequence objects (and not throw an
         *      exception) unless an unexpected exception occurrs during the
         *      iteration.
         * @returns
         *      A list object with each index corresponding to the indexes of
         *      this sequence.
         * @throws PythonException
         *      This should generally only occur if this sequence object throws
         *      an unexpected exception during iteration (IE something other
         *      than stop iteration).
         */
        virtual List asList() const;
    };
}

#endif
