#include "PWSequence.h"
#include "PWHandler.h"
#include "PWTuple.h"
#include "PWObject.h"
#include "PWList.h"
#include "PWExceptions.h"

namespace pw
{
    Sequence::Sequence(ReferenceHandler &ref)
    : Object(ref)
    {
        if (! PySequence_Check(mPtr))
            PW_Except("Non-Sequence object passed into Sequence.",
                      "Sequence::Sequence(ReferenceHandler &)");
    }

    Sequence::~Sequence()
    {
    }

    Sequence &Sequence::operator=(const Object &rhs)
    {
        assert(rhs.borrowReference());

        if (! PySequence_Check(rhs.borrowReference()))
            PW_Except("The List object may only be assigned a Python list.",
                      "List::operator=");

        // this if takes care of the case when the pointer is the same; if we
        // did not do this check the following code below would bomb if
        // mPtr == rhs.mPtr and the refcount was at 1
        if (mPtr != rhs.borrowReference())
        {
            Py_DECREF(mPtr);
            mPtr = rhs.borrowReference();
            Py_INCREF(mPtr);
        } // if

        return *this;
    } // operator=

    Sequence Sequence::operator+(const Sequence &rhs) const
    {
        return Sequence(NewReference(PySequence_Concat(mPtr, rhs.borrowReference())));
    }

    Sequence Sequence::operator*(int count) const
    {
        return Sequence(NewReference(PySequence_Repeat(mPtr, count)));
    }

    bool Sequence::contains(const Object &obj) const
    {
        return PySequence_Contains(mPtr, obj.borrowReference()) ? true : false;
    }

    int Sequence::index(const Object &obj) const
    {
        return PySequence_Index(mPtr, obj.borrowReference());
    }


    int Sequence::count(const Object &obj) const
    {
        return PySequence_Count(mPtr, obj.borrowReference());
    }


    Object Sequence::getItem(int index) const
    {
        return Object(NewReference(PySequence_GetItem(mPtr, index)));
    }


    void Sequence::setItem(int index, const Object &obj)
    {
        PySequence_SetItem(mPtr, index, obj.borrowReference());
        PW_PyExcept_Check("Sequence::setItem");
    }


    void Sequence::delItem(int index)
    {
        PySequence_DelItem(mPtr, index);
        PW_PyExcept_Check("Sequence::delItem");
    }


    Sequence Sequence::getSlice(int start, int stop) const
    {
        return Sequence(NewReference(PySequence_GetSlice(mPtr, start, stop)));
    }


    void Sequence::setSlice(int start, int stop, const Sequence &seq)
    {
        PySequence_SetSlice(mPtr, start, stop, seq.borrowReference());
        PW_PyExcept_Check("Sequence::setSlice");
    }

    void Sequence::delSlice(int start, int stop)
    {
        PySequence_DelSlice(mPtr, start, stop);
        PW_PyExcept_Check("Sequence::delSlice");
    }

    int Sequence::length() const
    {
        return PySequence_Size(mPtr);
    }

    Tuple Sequence::asTuple() const
    {
        return Tuple(NewReference(PySequence_Tuple(mPtr)));
    }


    List Sequence::asList() const
    {
        return List(NewReference(PySequence_List(mPtr)));
    }
} // namespace pw
