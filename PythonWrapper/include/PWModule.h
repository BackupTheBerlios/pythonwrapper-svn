#ifndef _PWModule_h_
#define _PWModule_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWDLib.h"
#include "PWConverterInterface.h"

namespace pw
{
    /**
     * An implementation of a basic Python module.
     * @remarks
     *      This implements the ConverterInterface because this makes some
     *      things easier to deal with.  You cannot actually use the base
     *      Module as a converter.  Note that this class also handles shared
     *      library loading by containing an instance of DLib.
     *      Lastly, note you should probably be using the ModuleManager or the
     *      System classes to deal with modules instead of using this class
     *      directly.
     */
    class Module : public ConverterInterface
    {
    public:
        typedef void (*InitFunction)();
        
    public:
        /**
         * Constructor.
         * @remarks
         *      This function creates a module and uses the library filename
         *      (without the extension) as the name of the module.
         * @param library
         *      The filename of the library to load
         */
        Module(const String &library);


        /**
         * Constructor.
         * @remarks
         *      This function creates a module and allows you to specify a
         *      name for the module instead of using the library name.
         * @param library
         *      The filename of the library to load.
         * @param name
         *      The name of the module.
         */
        Module(const String &library, const String &name);


        /**
         * Destructor.
         * @remarks
         *      This will unload the library if it hasn't been done already.
         */
        virtual ~Module();


        /**
         * Loads the module.
         * @remarks
         *      You must call intialize after calling this function when you
         *      want to use the module in Python.
         * @throws Exception
         *      If the library could not be found, if the library could not
         *      be loaded, or if the library did not contain an initalization
         *      function.
         */
        virtual void load();


        /**
         * Unloads the module.
         * @remarks
         *      This should probably not be called until after
         *      Interpreter::Finalize.
         */
        virtual void unload();

        
        /**
         * Returns the name of the module.
         * @returns the name of the module
         */
        virtual const String &getName() const;


        /**
         * Initializes the module for use with the Python interpreter.
         * @remarks
         *      This calls the init function.
         */
        virtual void initialize();


        /**
         * Empty converter function.
         * @remarks
         *      This always throws an exception, since the default module
         *      cannot be used as a converter.
         * @throws Exception
         *      Always.
         */
        virtual void *convert(PyObject *obj, void *type, bool disown);


        /**
         * Empty converter function.
         * @remarks
         *      This always throws an exception, since the default module
         *      cannot be used as a converter.
         * @throws Exception
         *      Always.
         */
        virtual PyObject *convert(void *obj, void *type, bool disown);
    protected:
        PW_DLIB mDLib;
        String mName;
        InitFunction mInit;
    };
}

#endif
