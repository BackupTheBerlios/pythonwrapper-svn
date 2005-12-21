#ifndef _PWSwigModule_h_
#define _PWSwigModule_h_

#include "PWCommon.h"
#include "PWModule.h"
#include "PWExceptions.h"

namespace pw
{
    class SwigModule : public Module
    {
    public:
        typedef void (*F_addType)(const char *, const char *, void *);
        typedef void (*F_addPyType)(PyTypeObject *, const char *);

        typedef PyTypeObject *(*F_GetType)();
        typedef void          (*F_RegisterConverters)(const char *, F_addType, F_addPyType);
        typedef PyObject *    (*F_ToPyObject)(void *, void *, int);
        typedef void *        (*F_ToPointer)(PyObject *, void *, int);

    public:
        SwigModule(const String &library);
        SwigModule(const String &library, const String &name);
        virtual ~SwigModule();

        virtual void load();
        virtual void unload();
        
        virtual void initialize();

        void *convert(PyObject *obj, void *typeInfo, bool disown)
        {
            if (! (mLoaded && mToPointer))
                PW_Except("Module not loaded.", "SwigModule::convert");

            //if (obj->ob_type != mSwigType)
            //    PW_Except("This module did not create the given object.", "SwigModule::convert");

            return mToPointer(obj, typeInfo, disown ? 1 : 0);
        }

        PyObject *convert(void *obj, void *type, bool disown)
        {
            if (! (mLoaded && mToPyObject))
                PW_Except("Module not loaded.", "SwigModule::convert");

            return mToPyObject(obj, type, disown ? 1 : 0);
        }

    protected:
        bool          mLoaded;
        PyTypeObject *mSwigType;
        F_ToPyObject  mToPyObject;
        F_ToPointer   mToPointer;
        F_RegisterConverters mRegister;
    };
}

#endif
