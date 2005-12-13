#ifndef _PWInterpreter_h_
#define _PWInterpreter_h_

#include "PWCommon.h"
#include "PWDict.h"
#include "PWModuleManager.h"

namespace pw
{
    /** The wrapper for the basic Python/C functions.
     *  @remarks
     *      The Interpreter class hides most of the Python/C API from you to
     *      abstract away most of the gritty details of embedding Python.
     *      Note that each instance of the Interpreter class is within its own
     *      Python context.  This means that modifying the state of the
     *      Interpreter class in one instance will not affect any other instance.
     *      If you wish to have a shared interpreter state between multiple
     *      instances, use pointers and references, or use the copy
     *      constructor or the = operator.
     */
    class PW_EXPORT Interpreter
    {
    public:
        /** Constructor.
         *  @remarks
         *      The base Interpreter class does all instance counting and it
         *      ensures the Python interpreter is intialized properly.  Calls
         *      init.
         */
        Interpreter();


        /** Deep copy constructor.
         *  @remarks
         *      This does NOT call init.  Equivilant to operator=.
         *  @see operator=
         */
        Interpreter(const Interpreter &pw);


        /** Performs a deep copy of the given Interpreter.
         *  @remarks
         *      This performs a deep copy of the given Interpreter.  When this is
         *      called, all variables in the two objects set to be equal,
         *      and any changes to one instance of the Interpreter class affects
         *      the other.
         */
        virtual const Interpreter &operator=(const Interpreter &);


        /** Destructor.
         *  @remarks
         *      This takes care of finalizing the python interpreter if no
         *      instances of Interpreter are left.  Calls deinit.
         */
        virtual ~Interpreter();


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
        virtual Object runString(const String &str);


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
        virtual Object runFile(const String &fileName);


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
        virtual Object evaluate(const String &expression);


        /** Returns a python object that's in the namespace.  (Including
         *  variables, functions, classes, and so on.)
         *  @param name
         *      The name of the object to retrieve.
         *  @throws PythonException
         *      Throws a python exception if there is no object in the namespace
         *      that matches that.
         *  @return
         *      Returns the Python object in the local namespace.
         */
        virtual Object getObject(const String &name);


        /** Resets the interpreter back to its initial state.
         *  @remarks
         *      All variables are cleared and reset to their initial value.
        */
        virtual void reset();


        /** Returns the namespace that this object uses.
         *  @returns the namespace (Dict) that this object uses
         */
        virtual const Dict &getNamespace() const;


        // Static methods.
        /** Loads a user defined module into the interpreter.  YOU MUST CALL THIS
          * BEFORE CALLING Interpreter::Initialize!
          * @remarks
          *     This is not for importing modules; if you wish to import a module,
          *     call runString("import ModuleName").  This method is for loading
          *     modules that are constructed using either the Python/C API or
          *     SWIG.  You must call this function before ever creating a Interpreter
          *     object if you want to use it.  Calling this function loads the
          *     module for ALL instances of Interpreter.
          * @note
          *     If you use SWIG, the init_function will be
          *     init_[modulename] where [modulename] is the name of the module
          *     you specified with %module.
          * @throws PythonException
          *     Throws PythonException if there was an error while loading the
          *     module.
          * @param moduleName
          *     An arbitrary name for the module.  You can later import it using
          *     "import [ModuleName]".
          * @param f
          *     The initialization function for the module.
          */
        static void loadModule(const String &moduleName, Module::InitFunction f);

        static void Initialize();
        static void Finalize();
    protected:
        /** The python namespace (ie the instance) of the object.
            @remarks
                This object IS the interpreter's variable set.  Since each
                Interpreter has their own dictionary, every Interpreter
                is like its own self contained interpreter.
        */
        Dict mNamespace;


        // Static members
        /** The __main__ module, used to create all Interpreter namespaces.
        */
        static Object *sModule;
    }; // class Interpreter
} // namespace OP
#endif
