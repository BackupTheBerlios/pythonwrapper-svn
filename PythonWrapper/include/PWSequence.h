#ifndef _PWSequence_h_
#define _PWSequence_h_

#include "PWCommon.h"
#include "PWObject.h"

namespace pw
{
    /**
     * Wrapper for any python sequence object.
     */
    class PW_EXPORT Sequence : public Object
    {
    public:
        Sequence(ReferenceHandler &ref);
        virtual ~Sequence();

        virtual Sequence operator+(const Sequence &rhs) const;
        virtual Sequence repeat(int count) const;

        virtual bool contains(const Object &obj) const;
        virtual int  index(const Object &obj) const;
        virtual int  count(const Object &obj) const;
        
        virtual Object getItem(int index) const;
        virtual void   setItem(int index, const Object &obj);
        virtual void   delItem(int index);

        virtual Sequence getSlice(int start, int stop) const;
        virtual void     setSlice(int start, int stop, const Object &obj);
        virtual void     delSlice(int start, int stop);

        virtual int size() const;

        virtual Tuple asTuple() const;
        virtual List  asList() const;
    };
}

#endif
