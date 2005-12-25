#ifndef _PWList_h_
#define _PWList_h_

#include "PWCommon.h"
#include "PWObject.h"
#include "PWSequenceEntry.h"

namespace pw
{
    /**
     * A wrapper for the Python list class.
     * @remarks
     *      This wraps most of the basic functionality of the list class.
     *      Two major things to note is the operator+ and operator+= perform
     *      list concatenation, and the operator[] returns an assignable
     *      object.
     */
    class PW_EXPORT List : public Object
    {
    public:
        typedef SequenceEntry<List, int> ListEntry;

    public:
        /**
         * Constructor.
         * @remarks
         *      This creates an empty list.  There is currently no way to
         *      create a list which contains a set of items (IE reserving
         *      space and then filling the list with PyList_SET_ITEM).  To do
         *      something like this you should probably create a PyList
         *      manually and then feed it into the ReferenceHandler ctor.
         */
        List();


        /**
         * Constructor.
         * @remarks
         *      This creates a List based off of a precreated PyObject *.
         *      See the documentation for ReferenceHandler for more information
         *      on how to feed a PyObject * into this constructor.
         * @see
         *      ReferenceHandler
         */
        List(ReferenceHandler &ref);


        /**
         * Destructor.
         */
        virtual ~List();


        /**
         * Assignment operator.
         * @remarks
         *      The Object parameter must be a Python list.
         * @param rhs
         *      A python List object.
         * @throws Exception
         *      If rhs is not a list.
         */
        virtual List &operator=(const Object &rhs);

        /**
         * Performs an in place concatenation.
         * @remarks
         *      This uses PySequence_InPlaceConcat.
         * @param rhs
         *      The list to concatenate.
         * @returns
         *      A reference to this list.
         * @throws PythonException
         *      If a python exception occured while performing the operation.
         */
        virtual List &operator+=(const List &rhs);


        /**
         * Performs a concatenation of this list and rhs.
         * @remarks
         *      This uses PySequence_Concat.
         * @param rhs
         *      The list to append.
         * @returns
         *      The new list object which is *this + rhs.
         * @throws PythonException
         *      If a python exception occured while performing the operation.
         */
        virtual List operator+(const List &rhs);

        /**
         * Repeats the list count times.  This is equivalent to the python
         * code:
         *  l * count
         * @param count
         *      The number of times to repeat this object.
         * @returns
         *      This list object repeated count times.
         * @throws PythonException
         *      If this object 
         */
        virtual List operator*(int count) const;


        /**
         * Returns the object at the specified index.
         * @remarks
         *      Note that this follows the rules of Python list indexing,
         *      meaning that passing in negative values will index the list
         *      in reverse.
         * @param index
         *      The index to return.
         * @returns
         *      The Object at the specified index.
         * @throws PythonException
         *      If an exception occured while retrieving the object.  This
         *      would most likely be due to an index out of bounds.
         */
        virtual Object getItem(int index) const;


        /**
         * Deletes the item at the specified index.
         * @remarks
         *      Note that this follows the rules of Python list indexing,
         *      meaning that passing in negative values will delete the index
         *      which would be retrieved by a negative index.
         * @param index
         *      The index to delete (may be negative).
         * @throws PythonException
         *      If an exception occured while deleting the object.  This
         *      would most likely be due to an index out of bounds.
         */
        virtual void delItem(int index);


        /**
         * Sets the item at index to be obj.
         * @remarks
         *      This uses PyList_SetItem.  The indexing rules are the same for
         *      this function as with that one.
         * @param index
         *      The index to set obj.
         * @param obj
         *      The object to set index to.
         * @throws Python
         */
        virtual void setItem(int index, const Object &obj);


        /**
         * Retrieves a slice of the List.
         * @remarks
         *      Note that this follows the rules of Python list slicing,
         *      meaning that passing in negative values will retrieve the
         *      slice in reverse.
         * @param start
         *      The start value for the slice
         * @param stop
         *      The stop value for the slice.
         * @throws PythonException
         *      If there was an error getting the slice.  This would most
         *      likely be caused by an index out of bounds.
         */
        virtual List getSlice(int start, int stop) const;


        /**
         * Deletes a slice of the List.
         * @remarks
         *      Note that this follows the rules of Python list slicing,
         *      meaning that passing in negative values will delete the
         *      slice in reverse.
         * @param start
         *      The start value for the slice
         * @param stop
         *      The stop value for the slice.
         * @throws PythonException
         *      If there was an error deleting the slice.  This would most
         *      likely be caused by an index out of bounds.
         */
        virtual void delSlice(int start, int stop);


        /**
         * Sets a slice of the List.
         * @remarks
         *      Note that this follows the rules of Python list slicing,
         *      meaning that passing in negative values will replace the
         *      slice in reverse.
         * @param start
         *      The start value for the slice
         * @param stop
         *      The stop value for the slice.
         * @param iterable
         *      The iterable object to replace the slice with.  Note that
         *      the object passed in must implement the iterator interface.
         * @throws PythonException
         *      If there was an error setting the slice.  This would most
         *      likely be caused by an index out of bounds or the object
         *      you are trying to set it to not being an interable.
         */
        virtual void setSlice(int start, int stop, const Object &iterable);


        /**
         * Inserts obj before index.
         * @remarks
         *      This is equivalent to the python List.insert method.
         * @param index
         *      The index to insert before.
         * @param obj
         *      The object to insert into the list.
         * @throws PythonException
         *      If an error occurred inserting the item.  This would most
         *      likely be caused by an index being out of bounds.
         */
        virtual void insert(int index, const Object &obj);

        /**
         * Appends obj to the end of the list.
         * @remarks
         *      This is equivalent to Python's list.append method.
         * @param obj
         *      The object to append to the end of the list.
         * @throws PythonException
         *      If an exception occured.
         */
        virtual void append(const Object &obj);


        /**
         * Reverses the list in place.
         */
        virtual void reverse();

        /**
         * Sorts the list.
         * @remarks
         *      This is equivalent to list.sort(), but it does not allow you
         *      to specify a sorting function.
         */
        virtual void sort();


        /**
         * Checks to see of obj is in the list.
         * @remarks
         *      Equivalent to obj in list.
         * @param obj
         *      The object to check for.
         * @returns
         *      True if the list contains obj, false otherwise.
         * @throws PythonException
         *      If an error occurred.
         */
        virtual bool contains(const Object &obj);


        /**
         * Returns the index of obj, or -1 if it is not found.
         * @param obj
         *      The object to find in the list.
         * @returns
         *      The index of obj or -1 if it is not found.
         */
        virtual int index(const Object &obj) const;


        /**
         * Counts the number of times obj appears in the list.
         * @param obj
         *      The object to search for.
         * @returns
         *      The number of times obj appears in the list.
         */
        virtual int count(const Object &obj) const;


        /**
         * Checks to see if this is exactly a list (and not a subtype).
         * @returns
         *      True if this object is exactly a list and not a subclass of
         *      list, false otherwise.
         */
        virtual bool exact() const;


        /**
         * Returns the length of the list.
         * @returns
         *      The length of the list.
         */
        virtual int length() const;


        /**
         * Converts the list to a tuple and returns the result.
         * @remarks
         *      This is equivalent to calling the tuple constructor with the
         *      list, tuple(list).
         * @returns
         *      The list converted to a tuple object.
         */
        virtual Tuple asTuple() const;


        /**
         * Obtains an assignable Object which corresponds to index.
         * @remarks
         *      The return value of this can be assigned to, and it will
         *      update the list.  For example:
         *      list[2] = someObject;
         *      Will set index 2 as someObject.  Note that the index must be
         *      valid or this will throw a python exception when you try to
         *      assign to it.
         * @param index
         *      The index to access.
         * @returns
         *      An assignable Object which can be used both to retrieve the
         *      value at the index and to set the value.
         */
        virtual ListEntry operator[](int index);
    }; // class List
} // namespace pw

#endif
