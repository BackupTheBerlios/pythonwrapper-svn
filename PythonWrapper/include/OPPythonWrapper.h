#ifndef _PythonWrapper_h_
#define _PythonWrapper_h_

#include "OPCommon.h"
#include <boost/python/object.hpp>
#include <boost/python/dict.hpp>

namespace OP
{
    /** The base Python wrapper.
        @remarks
            The PythonWrapper class hides most of the Python/C API from you to
            abstract away most of the gritty details of embedding Python.  In
            order to do some of the more advanced features of embedded Python,
            some knowledge of Boost.Python will be required.  Note that each
            instance of the PythonWrapper class is within its own Python context.
            This means that modifying the state of the interpreter in one instance
            will not affect any other instance.  If you wish to have a shared
            interpreter state between multiple instances, use pointers and
            references.
    */
    class _OP_DLL_EXPORT PythonWrapper
    {
    public:
        /** Constructor.
            @remarks
                The base PythonWrapper class does all instance counting and it
                ensures the Python interpreter is intialized properly.  Calls
                init.
        */
        PythonWrapper( );


        /** Deep copy constructor.
            @remarks
                This does NOT call init.  Equivilant to operator=.
            @see operator=
         */
        PythonWrapper( const PythonWrapper &pw );


        /** Performs a deep copy of the given PythonWrapper.
            @remarks
                This performs a deep copy of the given PythonWrapper.  When this is
                called, all variables in the two objects are equal but changes to
                one does not affect the other.
         */
        virtual const PythonWrapper &operator=( const PythonWrapper & );


        /** Destructor.
            @remarks
                This takes care of finalizing the python interpreter if no
                instances of PythonWrapper are left.  Calls deinit.
        */
        virtual ~PythonWrapper( );


        /** Runs the Python code contained in str.
            @remarks
                This function runs whatever code is set in str.  No attempt is
                made to return the result of the execution.  If you need to
                retrieve the value of a variable, use the evaluate function.
            @throws PythonException
                Throws a PythonException if there is a parse error when trying to
                execute the Python string.
            @param str
                The string containing the python code to run.
            @see runFile
            @see evaluate
        */
        virtual void runString( const std::string &str );


        /** Runs the file specified by file_name.
            @remarks
                This works in the same mannor as if you called runString with the
                contents of the file.  The only major difference is that this can
                handle python compiled files.  If possible, you should point the
                file_name variable to be the .pyc or .pyo file to save compilation
                times.
            @throws PythonException
                Throws a PythonException if there is a parse error when trying to
                execute the specified file.
            @throws FileException
                Throws a FileException if the specified file was not found.
            @param fileName
                The path to the file you wish to execute.
            @see runString
        */
        virtual void runFile( const std::string &fileName );


        /** Evaluates a python expression and returns the result.
            @remarks
                The runString and runFile methods do not evaluate any of the
                expressions they are given.  They only execute code.  In order
                to determine the result of a function call, internal variable,
                etc, you need to call evaluate.
            @note
                This can be used to return any Python construct, including class
                definitions, objects, functions, and variables.
            @throws PythonException
                Throws a PythonException if there is a parse error while trying to
                execute the expression.
            @param expression
                The python expression to evaluate.
            @return
                The Boost.Python object which contains the result of the
                expression.
        */
        virtual boost::python::object evaluate( const std::string &expression );


        /** Resets the interpreter back to its initial state.
            @remarks
                All variables are cleared and reset to their initial value.
        */
        virtual void reset( );


        // Static methods.
        /** Loads a user defined module into the interpreter.  YOU MUST CALL THIS
            BEFORE CREATING ANY PythonWrapper OBJECTS!
            @remarks
                This is not for importing modules; if you wish to import a module,
                call runString("import ModuleName").  This method is for loading
                modules that are constructed using either the Python/C API or
                Boost.Python's BOOST_PYTHON_MODULE.  This is static, and you may
                call it before ever creating a PythonWrapper object.  Calling this
                function loads the module for ALL instances of PythonWrapper.
            @note
                If you use BOOST_PYTHON_MODULE, the init_function will be
                init[modulename] where [modulename] is the name of the module you
                specified to BOOST_PYTHON_MODULE.
            @throws ImportException
                Throws PythonException if there was an error while loading the
                module.
            @param moduleName
                An arbitrary name for the module.  You can later import it using
                "import moduleName".
            @param initFunction
                The initialization function for the module.
        */
        static void loadModule( const std::string &moduleName, void (*initFunction)(void) );
    protected:
        /** Intializes the PythonWrapper.
            @remarks
                This function is called by the PythonWrapper constructor.  This
                sets up the mNamespace dictionary.  If you subclass this function
                you need to either call this init function, or setup the mNamespace
                dictionary yourself.
        */
        virtual void init( );


        /** Clears the PythonWrapper class.
            @remarks
                This function is called by the PythonWrapper destructor.
        */
        virtual void deinit( );


        /** Returns a const char * for the given Python object.
            @remarks
                This is an internal function.
            @param pyo
                The python object to convert, can be NULL.
            @return
                A string object containing the string representation of pyo.
         */
        static std::string getStr( PyObject *pyo );


        /** The python namespace (ie the instance) of the object.
            @remarks
                This object IS the interpreter's variable set.  Since each
                PythonWrapper has their own dictionary, every PythonWrapper
                is like its own self contained interpreter.
        */
        boost::python::dict mNamespace;


        // Static members
        /** The __main__ module, used to create all PythonWrapper namespaces.
        */
        static boost::python::object *sModule;
    private:
        /** The number of instances of PythonWrapper (and its subclasses).
            @remarks
                Before any Python code can be run, the interpreter must be
                initialized.  When the sInstanceCount varaible goes from 0 to 1,
                the interpreter is started.  When it goes from 1 to 0, it is
                finalized.  The interpreter must be finalized in order to avoid
                memory leaks.  If you do not want to incur a penalty for the
                initialization and finalization of the Python interpreter, either
                keep at least one PythonWrapper running or none.
        */
        static unsigned int sInstanceCount;
    }; // class PythonWrapper
} // namespace OP
#endif
