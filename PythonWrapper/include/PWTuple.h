#ifndef _PWTuple_h_
#define _PWTuple_h_

#include "PWObject.h"

namespace pw
{
    class PW_EXPORT Tuple : public Object
    {
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
