#include "OPPythonWrapper.h"
#include "OPPythonException.h"
#include "OPFileException.h"
#include "OPImportException.h"

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


PythonWrapper::PythonWrapper( const PythonWrapper &pw )
{
    *this = pw;
} // PythonWrapper( const PythonWrapper & )


const PythonWrapper &PythonWrapper::operator=( const PythonWrapper &pw )
{
    assert( sInstanceCount > 0 );
    mNamespace = python::dict(pw.mNamespace).copy();
    sInstanceCount++;

    return *this;
}


PythonWrapper::~PythonWrapper( )
{
    deinit( );

    if ( --sInstanceCount == 0 )
    {
        assert( sModule != 0 );
        delete sModule;
        sModule = 0;

        Py_Finalize();
    }
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


std::string PythonWrapper::getStr( PyObject *pyo )
{
    PyObject *str;
    std::string toReturn;
    
    if (pyo)
    {
        str = PyObject_Str( pyo );

        if ( str && PyString_Check( str ) )
            toReturn = PyString_AsString( str );

        Py_XDECREF( str );
    } // if

    return toReturn;
} // getStr( PyObject * )


void PythonWrapper::runString( const std::string &str )
{
    try
    {
        python::handle<> result(PyRun_String(str.c_str( ), Py_file_input, mNamespace.ptr(), mNamespace.ptr()));
    } // try
    catch (python::error_already_set)
    {
        std::string eType, eValue, eStackTrace;
        PyObject *type, *value, *stackTrace;

        // Fetch the python error.
        PyErr_Fetch( &type, &value, &stackTrace );


        eType = getStr( type );
        eValue = getStr( value );
        eStackTrace = getStr( stackTrace );

        Py_XDECREF( type );
        Py_XDECREF( value );
        Py_XDECREF( stackTrace );

        PyErr_Clear( );
        throw PythonException( eValue, eType, eStackTrace, __FILE__, __LINE__ );
    } // catch
} // runString( const std::string & )


void PythonWrapper::reset( )
{
    // This is a workaround.  The dict constructor does not make a deep copy
    // as it is supposed to.  This ensures that we retrieve a copy of the dict,
    // not the original.
    mNamespace = python::dict(sModule->attr("__dict__")).copy();
}


python::object PythonWrapper::evaluate( const std::string &expression )
{
    try
    {
        python::object toReturn( python::handle<>(PyRun_String(expression.c_str( ), Py_eval_input, mNamespace.ptr(), mNamespace.ptr())));
        return toReturn;
    } // try
    catch ( python::error_already_set )
    {
        std::string eType, eValue, eStackTrace;
        PyObject *type, *value, *stackTrace;

        // Fetch the python error.
        PyErr_Fetch( &type, &value, &stackTrace );

        eType = getStr( type );
        eValue = getStr( value );
        eStackTrace = getStr( stackTrace );

        Py_XDECREF( type );
        Py_XDECREF( value );
        Py_XDECREF( stackTrace );

        PyErr_Clear( );
        throw PythonException( eValue, eType, eStackTrace, __FILE__, __LINE__ );
    } // catch

    // Cannot happen.
    return python::object();
} // evaluate( const std::string & )


void PythonWrapper::runFile( const std::string &fileName )
{
    FILE *fp;
    
    fp = fopen( fileName.c_str(), "r" );
    if (!fp)
        throw FileException( fileName, __FILE__, __LINE__ );

    try
    {
        python::handle<> result( PyRun_File( fp, fileName.c_str(), Py_file_input, mNamespace.ptr(), mNamespace.ptr() ) );
        fclose( fp );
    } // try
    catch (python::error_already_set)
    {
        fclose( fp );  // Close the file

        std::string eType, eValue, eStackTrace;
        PyObject *type, *value, *stackTrace;

        // Fetch the python error.
        PyErr_Fetch( &type, &value, &stackTrace );


        eType = getStr( type );
        eValue = getStr( value );
        eStackTrace = getStr( stackTrace );

        Py_XDECREF( type );
        Py_XDECREF( value );
        Py_XDECREF( stackTrace );

        PyErr_Clear( );
        throw PythonException( eValue, eType, eStackTrace, __FILE__, __LINE__ );
    } // catch
} // runFile( const std::string & )


void PythonWrapper::loadModule( const std::string &moduleName, void (*initFunction)(void) )
{
    // PyImport_AppendInittab takes a char*.  To be safe I don't cast, I give it a throw-away char *.
    char *name = new char[moduleName.length()+1];
    strncpy( name, moduleName.c_str(), moduleName.length() );

    if (PyImport_AppendInittab(name, initFunction) == -1)
    {
        delete name;
        throw ImportException( moduleName, __FILE__, __LINE__ );
    } // if

    delete name;
} // loadModule( const std::string &, void (*)(void) )


boost::python::object PythonWrapper::getObject( const std::string &object )
{
    if (! mNamespace.has_key( object ) )
    {
        throw PythonException( "No object " + object + " in namespace.", "NoneType", "", __FILE__, __LINE__ );
    } // if

    return mNamespace[object];
} // getObject( const std::string & )
