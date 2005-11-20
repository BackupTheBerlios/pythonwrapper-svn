#ifndef _PWList_h_
#define _PWList_h_

#include "PWCommon.h"
#include "PWObject.h"
#include "PWSequenceEntry.h"

namespace pw
{
    class _PW_EXPORT List : public Object
    {
    public:
        typedef SequenceEntry<List, int> ListEntry;

    public:
        List();
        List(ReferenceHandler &ref);

        virtual ~List();

        virtual List &operator+=(const List &rhs);
        virtual List  operator+(const List &rhs);

        virtual Object getItem(int index) const;
        virtual void   delItem(int index);
        virtual void   setItem(int index, const Object &obj);

        virtual List getSlice(int start, int stop) const;
        virtual void delSlice(int start, int stop);
        virtual void setSlice(int start, int stop, const Object &obj);

        virtual void insert(int index, const Object &obj);
        virtual void append(const Object &obj);
        virtual void reverse();
        virtual void sort();

        virtual bool contains(const Object &obj);

        virtual bool exact() const;
        virtual int size() const;
        virtual Tuple asTuple() const;

        virtual ListEntry operator[](int index);
    };
}

#endif
