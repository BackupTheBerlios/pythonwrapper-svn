#ifndef _PWDict_h_
#define _PWDict_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWObject.h"
#include "PWSequenceEntry.h"

namespace pw
{
    class PW_EXPORT Dict : public Object
    {
    public:
        typedef SequenceEntry<Dict, Object> DictEntry;

    public:
        Dict();
        Dict(const Object &obj);
        virtual ~Dict();

        virtual Dict copy() const;

        virtual bool contains(const Object &key) const;

        virtual void setItem(const String &key, const Object &value);
        virtual void setItem(const Object &key, const Object &value);

        virtual Object getItem(const Object &key) const;
        virtual Object getItem(const String &key) const;

        virtual void delItem(const Object &key);
        virtual void delItem(const String &key);

        virtual inline int length() const
        { return PyDict_Size(mPtr); }

        virtual List items() const;
        virtual List keys() const;
        virtual List values() const;

        virtual DictEntry operator[](const Object &key);
        virtual DictEntry operator[](const String &key);

        Dict copy();
    };
}

#endif
