#ifndef _PWDict_h_
#define _PWDict_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWObject.h"
#include "PWSequenceEntry.h"

namespace pw
{
    /**
     * This is a wrapper for the Python dict class.  It supports both shallow
     * and deep copying, indexing based on strings and python objects, as well
     * as all of the basic dictionary functions.
     */
    class PW_EXPORT Dict : public Object
    {
    public:
        typedef SequenceEntry<Dict, Object> DictEntry;

    public:
        /**
         * Basic constructor.  Creates a dictionary object.
         */
        Dict();


        /**
         * Makes a shallow copy of the dictionary obj.  A change to obj will
         * result in a change to this object.
         * @param dict a python Dictionary object to make a shallow copy of
         * @throws Exception if dict is not a Python dictionary object
         */
        Dict(const Object &dict);


        /**
         * Basic destructor.
         */
        virtual ~Dict();


        /**
         * Makes a deep copy of this Dictionary and returns it.
         * @returns a deep copy of this object
         */
        virtual Dict copy() const;


        /**
         * Returns true if the dictionary contains key.  Equivalent to the
         * Python/C function PyDict_Contains.
         * @param key the key to check for
         * @returns true if key is in the dictionary, false if it is not
         * @throws PythonException if an error occurred while checking (most
         *         likely due to key being un-hashable)
         */
        virtual bool contains(const Object &key) const;


        /**
         * Sets the item based on key.  This is like setting:
         * dictionary["key"] = value
         * @param key the key to the dictionary
         * @param value the entry to
         * @throws PythonException if an error occurred while setting the
         *         entry (shouldn't happen)
         */
        virtual void setItem(const String &key, const Object &value);


        /**
         * Sets the item based on key.  This is like setting:
         * dictionary[key] = value
         * @param key the key to the dictionary
         * @param value the entry to
         * @throws PythonException if an error occurred while setting the
         *         entry (probably due to an unhashable key)
         */
        virtual void setItem(const Object &key, const Object &value);


        /**
         * Returns the value for the specified key.
         * @param key the key to look up
         * @returns the object corresponding to key
         * @throws PythonException if an error occurred while trying to get the
         *         attribute (most likely due to an unhashable key or the key
         *         is not in the dictionary)
         */
        virtual Object getItem(const Object &key) const;


        /**
         * Returns the value for the specified key.
         * @param key the key to look up
         * @returns the object corresponding to key
         * @throws PythonException if an error occurred while trying to get the
         *         attribute (most likely due to the key not being in the
         *         dictionary)
         */
        virtual Object getItem(const String &key) const;


        /**
         * Deletes the item indexed by key.  Equivalent to:
         * del dictionary[key]
         * @param key the key to delete
         * @throws PythonException if key is unhashable or not in the
         *         dictionary
         */
        virtual void delItem(const Object &key);


        /**
         * Deletes the item indexed by key.  Equivalent to:
         * del dictionary[key]
         * @param key the key to delete
         * @throws PythonException if key is unhashable or not in the
         *         dictionary
         */
        virtual void delItem(const String &key);


        /**
         * Returns the number of items in the dictionary.
         * @returns the number of keys in the dictionary
         */
        virtual int length() const;


        /**
         * Returns a list of tuples that correspond to key/value pairs.
         * Equivalent to the python code:
         * dictionary.items()
         * @returns a List of Tuples 
         */
        virtual List items() const;


        /**
         * Returns a list of python objects which correspond to keys in the
         * dictionary.
         * @returns a list of the keys in the dictionary
         */
        virtual List keys() const;


        /**
         * Returns a list of python objects which correspond to the values
         * that this Dictionary contains.
         * @returns a list of the values in the dictionary
         */
        virtual List values() const;


        /**
         * Returns an assignable dictionary entry corresponding to key.
         * This is similar to getItem except that it may be assigned:
         * dictionary[key] = someObject;
         * Note that this does not throw an exception like getItem does.  If
         * you access a key that does not exist in the dictionary, then it
         * returns a None value.  The however, dictionary is not actually
         * updated unless the return value is assigned to (meaning you will
         * not create a dictionary entry until you assign it).
         *
         * @param key the key to retrieve
         * @returns an assignable dictionary entry
         */
        virtual DictEntry operator[](const Object &key);


        /**
         * Returns an assignable dictionary entry corresponding to key.
         * This is similar to getItem except that it may be assigned:
         * dictionary["key"] = someObject;
         * Note that this does not throw an exception like getItem does.  If
         * you access a key that does not exist in the dictionary, then it
         * returns a None value.  The however, dictionary is not actually
         * updated unless the return value is assigned to (meaning you will
         * not create a dictionary entry until you assign it).
         *
         * @param key the key to retrieve
         * @returns an assignable dictionary entry
         */
        virtual DictEntry operator[](const String &key);
    };
}

#endif
