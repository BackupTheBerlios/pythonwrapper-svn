#include "PWList.h"
#include "PWHandler.h"
#include "PWExceptions.h"
#include "PWTuple.h"

namespace pw
{
    List::List()
    : Object(NewReference(PyList_New(0)))
    {
    }


    List::List(ReferenceHandler &ref)
    : Object(ref)
    {
        if (! PyList_Check(mPtr))
            PW_Except("The List object may only be constructed with a Python list.",
                      "List::List()");
    }


    List::~List()
    {
    }


    List &List::operator=(const Object &rhs)
    {
        assert(rhs.borrowReference());

        if (! PyList_Check(rhs.borrowReference()))
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


    List List::operator*(int count) const
    {
        return NewReference(PySequence_Repeat(mPtr, count));
    }

    int List::count(const Object &obj) const
    {
        return PySequence_Count(mPtr, obj.borrowReference());
    }

    int List::index(const Object &obj) const
    {
        return PySequence_Index(mPtr, obj.borrowReference());
    }

    Object List::getItem(int index) const
    {
        return Object(BorrowedReference(PyList_GetItem(mPtr, index)));
    }


    void List::setItem(int index, const Object &obj)
    {
         PyList_SetItem(mPtr, index, obj.newReference());
         PW_PyExcept_Check("List::setItem");
    }

    List List::getSlice(int start, int stop) const
    {
        return List(BorrowedReference(PyList_GetSlice(mPtr, start, stop)));
    }


    void List::setSlice(int start, int stop, const Object &iterable)
    {
        PyList_SetSlice(mPtr, start, stop, iterable.borrowReference());
        PW_PyExcept_Check("List::setSlice");
    }


    void List::insert(int index, const Object &obj)
    {
        PyList_Insert(mPtr, index, obj.borrowReference());
        PW_PyExcept_Check("List::insert");
    }


    void List::append(const Object &obj)
    {
        PyList_Append(mPtr, obj.borrowReference());
        PW_PyExcept_Check("List::append");
    }

    int List::length() const
    {
        return PyList_Size(mPtr);
    }

    Tuple List::asTuple() const
    {
        return Tuple(NewReference(PySequence_Tuple(mPtr)));
    }

    bool List::exact() const
    {
        return PyList_CheckExact(mPtr) ? true : false;
    }


    List &List::operator+=(const List &rhs)
    {
        PyObject *obj = PySequence_InPlaceConcat(mPtr, rhs.borrowReference());
        PW_PyExcept_Check("List::operator+=");
        Py_DECREF(obj);

        return *this;
    }


    List List::operator+(const List &rhs)
    {
        return List(NewReference(PySequence_Concat(mPtr, rhs.borrowReference())));
    }

    void List::delItem(int index)
    {
        PySequence_DelItem(mPtr, index);
        PW_PyExcept_Check("List::delItem");;
    }

    void List::delSlice(int start, int stop)
    {
        PySequence_DelSlice(mPtr, start, stop);
        PW_PyExcept_Check("List::delSlice");;
    }

    void List::reverse()
    {
        PyList_Reverse(mPtr);
    }

    void List::sort()
    {
        PyList_Sort(mPtr);
    }


    bool List::contains(const Object &obj)
    {
        bool toReturn = PySequence_Contains(mPtr, obj.borrowReference()) == 1;
        PW_PyExcept_Check("List::contains");;
        return toReturn;
    }

    List::ListEntry List::operator[](int index)
    {
        return SequenceEntry<List, int>(BorrowedReference(PyList_GetItem(mPtr, index)),
                                        *this, index);
    }
} // namespace pw