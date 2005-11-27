#include "PWTuple.h"
#include "PWList.h"
#include "PWHandler.h"
#include "PWSequence.h"
#include "PWExceptions.h"
using namespace pw;

Tuple::Tuple(int length)
: Object(NewReference(PyTuple_New(length)))
{
} // Tuple(int)


Tuple::Tuple(ReferenceHandler &ref)
: Object(ref)
{
    if (! PyTuple_Check(mPtr))
        PW_Except("Non-tuple object passed into Tuple.",
                  "Tuple::Tuple(ReferenceHandler &)");
}


Tuple::Tuple(const Tuple &copy)
: Object(NewReference(PySequence_Tuple(copy.newReference())))
{
}


Tuple::~Tuple()
{
}


void Tuple::setItem(int index, const Object &obj)
{
    PyTuple_SetItem(mPtr, index, obj.newReference());
    PW_PyExcept_Check("Tuple::setItem");
}


Object Tuple::getItem(int index) const
{
    return Object(BorrowedReference(PyTuple_GetItem(mPtr, index)));
}


Tuple Tuple::getSlice(int start, int stop) const
{
    return Tuple(NewReference(PyTuple_GetSlice(mPtr, start, stop)));
}


int Tuple::length() const
{
    return PyTuple_Size(mPtr);
}


List Tuple::asList() const
{
    return List(NewReference(PySequence_List(newReference())));
}


bool Tuple::exact() const
{
    return PyTuple_CheckExact(mPtr) ? true : false;
}
