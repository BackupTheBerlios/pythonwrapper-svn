#include "PythonWrapper.h"
#include <boost/python.hpp>

using namespace OP;
namespace python = boost::python;

python::object *PythonWrapper::sModule = 0;
unsigned int PythonWrapper::sInstanceCount = 0;

PythonWrapper::PythonWrapper( )
{
    if ( sInstanceCount++ == 0 )
    {
        Py_Initialize();

        assert( sModule == 0 );
        sModule = new python::object(python::handle<>(python::borrowed(PyImport_AddModule("__main__"))));
    }

    init( );
} // PythonWrapper


PythonWrapper::~PythonWrapper( )
{
    if ( --sInstanceCount == 0 )
    {
        assert( sModule != 0 );
        delete sModule;
        sModule = 0;

        Py_Finalize();
    }

    deinit( );
} // ~PythonWrapper


void PythonWrapper::init( )
{
    // This is a workaround.  The dict constructor does not make a deep copy
    // as it is supposed to.  This ensures that we retrieve a copy of the dict,
    // not the original.
    mNamespace = python::dict(sModule->attr("__dict__")).copy();
} // init


void PythonWrapper::deinit()
{
    // Clear namespace so we don't have a reference to it.
    mNamespace = python::dict( );
} // deinit


void PythonWrapper::runString( const char *str )
{
    try
    {
        python::handle<> result(PyRun_String(str, Py_file_input, mNamespace.ptr(), mNamespace.ptr()));
    }
    catch (python::error_already_set)
    {
        // todo: Throw exception on error, query for error message/type.
        PyErr_Clear( );
    }
}
