#ifndef _System_h_
#define _System_h_

#include "PWCommon.h"

namespace pw
{
    /** The wrapper for the basic Python/C functions.
     *  @remarks
     *      The System class hides most of the Python/C API from you to
     *      abstract away most of the gritty details of embedding Python.
     *      Note that each instance of the System class is within its own
     *      Python context.  This means that modifying the state of the
     *      System class in one instance will not affect any other instance.
     *      If you wish to have a shared interpreter state between multiple
     *      instances, use pointers and references, or use the copy
     *      constructor or the = operator.
     */
    class _PW_EXPORT System
    {
    public:
        /** Constructor.
         *  @remarks
         *      The base System class does all instance counting and it
         *      ensures the Python interpreter is intialized properly.  Calls
         *      init.
         */
        System();


        /** Deep copy constructor.
         *  @remarks
         *      This does NOT call init.  Equivilant to operator=.
         *  @see operator=
         */
        System(const System &pw);


        /** Performs a deep copy of the given System.
         *  @remarks
         *      This performs a deep copy of the given System.  When this is
         *      called, all variables in the two objects set to be equal,
         *      and any changes to one instance of the System class affects
         *      the other.
         */
        virtual const System &operator=(const System &);


        /** Destructor.
         *  @remarks
         *      This takes care of finalizing the python interpreter if no
         *      instances of System are left.  Calls deinit.
         */
        virtual ~System();


        /** Runs the Python code contained in str.
         *  @remarks
         *      This function runs whatever code is set in str.  No attempt is
         *      made to return the result of the execution.  If you need to
         *      retrieve the value of a variable, use the evaluate function.
         *  @throws PythonException
         *      Throws a PythonException if there is a parse error when trying to
         *      execute the Python string.
         *  @param str
         *      The string containing the python code to run.
         *  @see runFile
         *  @see evaluate
        */
        virtual void runString(const std::string &str);


        /** Runs the file specified by file_name.
         *  @remarks
         *      This works in the same mannor as if you called runString with the
         *      contents of the file.  The only major difference is that this can
         *      handle python compiled files.  If possible, you should point the
         *      file_name variable to be the .pyc or .pyo file to save compilation
         *      times.
         *  @throws PythonException
         *      Throws a PythonException if there is a parse error when trying to
         *      execute the specified file.
         *  @throws FileException
         *      Throws a FileException if the specified file was not found.
         *  @param fileName
         *      The path to the file you wish to execute.
         *  @see runString
        */
        virtual void runFile(const std::string &fileName);


        /** Evaluates a python expression and returns the result.
         *  @remarks
         *      The runString and runFile methods do not evaluate any of the
         *      expressions they are given.  They only execute code.  In order
         *      to determine the result of a function call, internal variable,
         *      etc, you need to call evaluate.
         *  @note
         *      This can be used to return any Python construct, including class
         *      definitions, objects, functions, and variables.
         *  @throws PythonException
         *      Throws a PythonException if there is a parse error while trying to
         *      execute the expression.
         *  @param expression
         *      The python expression to evaluate.
         *  @return
         *      The Boost.Python object which contains the result of the
         *      expression.
        */
        virtual Object evaluate(const std::string &expression);


        /** Returns a python object that's in the namespace.  (Including
         *  variables, functions, classes, and so on.)
         *  @param object
         *      The name of the object to retrieve.
         *  @throws PythonException
         *      Throws a python exception if there is no object in the namespace
         *      that matches that.
         *  @return
         *      Returns the Python object in the local namespace.
         */
        virtual Object getObject(const std::string &object);


        /** Resets the interpreter back to its initial state.
         *  @remarks
         *      All variables are cleared and reset to their initial value.
        */
        virtual void reset();


        // Static methods.
        /** Loads a user defined module into the interpreter.  YOU MUST CALL THIS
          * BEFORE CREATING ANY System OBJECTS!
          * @remarks
          *     This is not for importing modules; if you wish to import a module,
          *     call runString("import ModuleName").  This method is for loading
          *     modules that are constructed using either the Python/C API or
          *     Boost.Python's BOOST_PYTHON_MODULE.  This is static, and you may
          *     call it before ever creating a System object.  Calling this
          *     function loads the module for ALL instances of System.
          * @note
          *     If you use BOOST_PYTHON_MODULE, the init_function will be
          *     init[modulename] where [modulename] is the name of the module you
          *     specified to BOOST_PYTHON_MODULE.
          * @throws ImportException
          *     Throws PythonException if there was an error while loading the
          *     module.
          * @param moduleName
          *     An arbitrary name for the module.  You can later import it using
          *     "import moduleName".
          * @param initFunction
          *     The initialization function for the module.
          */
        static void loadModule(const std::string &moduleName, void (*initFunction)(void));
    protected:
        /** Intializes the System.
            @remarks
                This function is called by the System constructor.  This
                sets up the mNamespace dictionary.  If you subclass this function
                you need to either call this init function, or setup the mNamespace
                dictionary yourself.
        */
        virtual void init();


        /** Clears the System class.
            @remarks
                This function is called by the System destructor.
        */
        virtual void deinit();


        /** Returns a const char * for the given Python object.
            @remarks
                This is an internal function.
            @param pyo
                The python object to convert, can be NULL.
            @return
                A string object containing the string representation of pyo.
         */
        static const char *getStr(const Object &obj);


        /** The python namespace (ie the instance) of the object.
            @remarks
                This object IS the interpreter's variable set.  Since each
                System has their own dictionary, every System
                is like its own self contained interpreter.
        */
        Dict mNamespace;


        // Static members
        /** The __main__ module, used to create all System namespaces.
        */
        static Object *sModule;
    private:
        /** The number of instances of System (and its subclasses).
            @remarks
                Before any Python code can be run, the interpreter must be
                initialized.  When the sInstanceCount varaible goes from 0 to 1,
                the interpreter is started.  When it goes from 1 to 0, it is
                finalized.  The interpreter must be finalized in order to avoid
                memory leaks.  If you do not want to incur a penalty for the
                initialization and finalization of the Python interpreter, either
                keep at least one System running or none.
        */
        static unsigned int sInstanceCount;
    }; // class System
} // namespace OP
#endif
