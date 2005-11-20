#include "PWSequence.h"
#include "PWHandler.h"
#include "PWTuple.h"
#include "PWObject.h"
#include "PWList.h"
#include "PWExceptions.h"

using namespace pw;

Sequence::Sequence(ReferenceHandler &ref)
: Object(ref)
{
    if (! PySequence_Check(mPtr))
        PYTHON_EXCEPTION_THROW;
}

Sequence::~Sequence()
{
}

Sequence Sequence::operator+(const Sequence &rhs) const
{
    return Sequence(NewReference(PySequence_Concat(mPtr, rhs.borrowReference())));
}

Sequence Sequence::repeat(int count) const
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
    PYTHON_EXCEPTION_CHECK;
}


void Sequence::delItem(int index)
{
    PySequence_DelItem(mPtr, index);
    PYTHON_EXCEPTION_CHECK;
}


Sequence Sequence::getSlice(int start, int stop) const
{
    return Sequence(NewReference(PySequence_GetSlice(mPtr, start, stop)));
}


void Sequence::setSlice(int start, int stop, const Object &obj)
{
    PySequence_SetSlice(mPtr, start, stop, obj.borrowReference());
    PYTHON_EXCEPTION_CHECK;
}

void Sequence::delSlice(int start, int stop)
{
    PySequence_DelSlice(mPtr, start, stop);
    PYTHON_EXCEPTION_CHECK;
}

int Sequence::size() const
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
