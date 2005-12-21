#ifndef _PWModuleManager_h_
#define _PWModuleManager_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWSingleton.h"
#include "PWModule.h"

#include <map>

namespace pw
{
    /**
     * The module manager class handles modules at a very high level.  It
     * allows the user to load and unload swig modules by specifying the
     * file name of the module.
     * @remarks
     *      This is a singleton, so you must create it somewhere before
     *      actually using it.  Generally this is done by the System class,
     *      which handles singleton creation for the ModuleManager and the
     *      System class.
     * @see System
     */
    class PW_EXPORT ModuleManager : public Singleton<ModuleManager>
    {
    public:
        /**
         * Returns a reference to the ModuleManager singleton.
         * @remarks
         *      You are responsible for ensuring that the singleton has been
         *      created before using this method.  If you are unsure if in a
         *      section of code if it has been created you should use the
         *      getSingletonPtr function instead.
         * @note
         *      This will cause an access violation if the ModuleManager has
         *      not been created.
         * @returns
         *      A reference to the singleton.
         */
        static ModuleManager &getSingleton();


        /**
         * Returns a pointer to the ModuleManager singleton.
         * @remarks
         *      This returns 0 if the singleton has not been created.
         * @returns
         *      A pointer to the ModuleManager singleton, or 0 if it has not
         *      been created.
         */
        static ModuleManager *getSingletonPtr();

    public:
        /**
         * Constructor.
         */
        ModuleManager();


        /**
         * Destructor.
         * @remarks
         *      This unloads all modules if it has not been done already.
         */
        ~ModuleManager();


        /**
         * Loads the shared library specified by dllName.
         * @remarks
         *      Under windows you must include the file extension (.dll or
         *      .pyd), but under linux you should not add it (.so).  This
         *      loads the module and names it whatever file name you specified
         *      minus the extension.
         * @param dllName
         *      The filename of the library.
         * @throws Exception
         *      If the lib could not be found, or if a module with the same
         *      name is already in the ModuleManager
         */
        void loadModule(const String &dllName);


        /**
         * Loads a swig module specified by dllName.  
         * @remarks
         *      Note that this module must have included the PWEmbedded.i
         *      module (included with this library), and build with PW_Embedded
         *      defined during compilation.  See the loadModule function for
         *      a note on the file extensions.
         * @param dllName
         *      The name of the library to load.
         * @throws Exception
         *      If the lib could not be found, or if a module with the same
         *      name is already in the ModuleManager
         * @see ModuleManager::loadModule
         */
        void loadSwigModule(const String &dllName);


        /**
         * Unloads the module specified by name.
         * @remarks
         *      Unloads the module specified by name.  Note that the name is
         *      not the filename passed into the loadModule functions, it is
         *      the name of the module (which is the name of the library
         *      without any directory slashes or file extension).
         * @param name
         *      The module to unload.
         * @throws Exception
         *      If a module of that name could not be found.
         */
        void unloadModule(const String &name);


        /**
         * Returns the module specified by name.
         * @remarks
         *      Note that the name parameter is the name of the module, not the
         *      filename.  Do not delete the pointer that is returned by this
         *      function.
         * @param name
         *      The name of the module.
         * @returns
         *      The module specified by name.  ModuleManager owns the pointer.
         */
        Module *findModule(const String &name);


        /**
         * Initializes all modules in the ModuleManager.
         * @see Module::initialize
         */
        void initializeModules();


        /**
         * Unloads all modules in the ModuleManager.
         * @remarks
         *      This may cause a crash if you unload the modules while still
         *      using parts of the module.  This should be called after the
         *      Python interpreter has been finalized.
         */
        void unloadAll();

    private:
        void addModule(Module *module);

    private:
        typedef std::map<String, Module *> ModuleMap;
        ModuleMap mModules;
    };
}

#endif
