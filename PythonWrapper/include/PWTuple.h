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

        virtual void     setItem(int index, const Object &obj);
        virtual Object   getItem(int index) const;
        virtual Tuple    getSlice(int start, int stop) const;

        virtual int length() const;
        virtual bool exact() const;

        virtual List  asList() const;
    };
}

#endif
