#include "PWList.h"
#include "PWHandler.h"
#include "PWExceptions.h"
#include "PWTuple.h"
using namespace pw;

List::List()
: Object(NewReference(PyList_New(0)))
{
    if (! PyList_Check(mPtr))
        PYTHON_EXCEPTION_THROW;
}


List::List(ReferenceHandler &ref)
: Object(ref)
{
}


List::~List()
{
}


Object List::getItem(int index) const
{
    return Object(BorrowedReference(PyList_GetItem(mPtr, index)));
}


void List::setItem(int index, const Object &obj)
{
     PyList_SetItem(mPtr, index, obj.newReference());
     PYTHON_EXCEPTION_CHECK;
}

List List::getSlice(int start, int stop) const
{
    return List(BorrowedReference(PyList_GetSlice(mPtr, start, stop)));
}


void List::setSlice(int start, int stop, const Object &obj)
{
    PyList_SetSlice(mPtr, start, stop, obj.borrowReference());
    PYTHON_EXCEPTION_CHECK;
}


void List::insert(int index, const Object &obj)
{
    PyList_Insert(mPtr, index, obj.borrowReference());
    PYTHON_EXCEPTION_CHECK;
}


void List::append(const Object &obj)
{
    PyList_Append(mPtr, obj.borrowReference());
    PYTHON_EXCEPTION_CHECK;
}

int List::size() const
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
    PYTHON_EXCEPTION_CHECK;
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
    PYTHON_EXCEPTION_CHECK;
}

void List::delSlice(int start, int stop)
{
    PySequence_DelSlice(mPtr, start, stop);
    PYTHON_EXCEPTION_CHECK;
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
    PYTHON_EXCEPTION_CHECK;
    return toReturn;
}

List::ListEntry List::operator[](int index)
{
    return SequenceEntry<List, int>(BorrowedReference(PyList_GetItem(mPtr, index)),
                                    *this, index);
}
