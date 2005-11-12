#ifndef _PWExceptions_h_
#define _PWExceptions_h_

#define PYTHON_EXCEPTION_THROW throw PythonException()
#define NULL_OBJECT_EXCEPTION_THROW throw NullObjectException()

class PythonException {};
class NullObjectException {};

#endif
