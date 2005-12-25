#ifndef _PWTuple_h_
#define _PWTuple_h_

#include "PWObject.h"

namespace pw
{
    class PW_EXPORT Tuple : public Object
    {
    public:
        static Tuple build(const Object &obj0);
        static Tuple build(const Object &obj0, const Object &obj1);
        static Tuple build(const Object &obj0, const Object &obj1, const Object &obj2);
        static Tuple build(const Object &obj0, const Object &obj1, const Object &obj2, const Object &obj3);

    public:
        Tuple(int length);
        Tuple(ReferenceHandler &ref);
        Tuple(const Tuple &copy);

        virtual ~Tuple();

        /**
         * Repeats the tuple count times.  This is equivalent to the python
         * code:
         *  t * count
         * @param count
         *      The number of times to repeat this object.
         * @returns
         *      This tuple object repeated count times.
         * @throws PythonException
         *      If this object 
         */
        virtual Tuple operator*(int count) const;
        

        /**
         * Checks to see of obj is in the tuple.
         * @remarks
         *      Equivalent to obj in tuple.
         * @param obj
         *      The object to check for.
         * @returns
         *      True if the tuple contains obj, false otherwise.
         * @throws PythonException
         *      If an error occurred.
         */
        virtual bool contains(const Object &obj) const;


        /**
         * Returns the index of obj, or -1 if it is not found.
         * @param obj
         *      The object to find in the tuple.
         * @returns
         *      The index of obj or -1 if it is not found.
         */
        virtual int index(const Object &obj) const;


        /**
         * Counts the number of times obj appears in the tuple.
         * @param obj
         *      The object to search for.
         * @returns
         *      The number of times obj appears in the tuple.
         */
        virtual int count(const Object &obj) const;

        virtual void setItem(int index, const Object &obj);
        virtual Object getItem(int index) const;
        virtual Tuple getSlice(int start, int stop) const;

        virtual int length() const;
        virtual bool exact() const;

        virtual List asList() const;
    };
}

#endif
