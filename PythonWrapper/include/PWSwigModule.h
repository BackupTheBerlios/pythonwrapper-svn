#ifndef _PWSwigModule_h_
#define _PWSwigModule_h_

#include "PWCommon.h"
#include "PWModule.h"
#include "PWConverterInterface.h"
#include "PWExceptions.h"

namespace pw
{
    class SwigModule : public Module, public ConverterInterface
    {
    public:
        typedef PyTypeObject *(*F_GetType)();
        typedef void          (*F_RegisterConverters)(void*);
        typedef PyObject *    (*F_ToPyObject)(void *, int);
        typedef void *        (*F_ToPointer)(PyObject *, int);

    public:
        SwigModule(const String &library);
        SwigModule(const String &library, const String &name);
        virtual ~SwigModule();

        virtual void load();
        virtual void unload();
        
        virtual void initialize();

        template <class T>
        T *convert(PyObject *obj, bool disown)
        {
            if (! (mLoaded && mToPointer))
                PW_Except("Module not loaded.", "SwigModule<" + typeid(T).name() + ">::convert");

            if (obj->ob_type != mSwigType)
                PW_Except("This module did not create the given object.", "SwigModule<" + typeid(T).name() + ">::convert");

            return (T *)mToPointer(obj, disown ? 1 : 0);
        }

        template <class T>
        PyObject *convert(T *obj, bool disown)
        {
            if (! (mLoaded && mToPyObject))
                PW_Except("Module not loaded.", "SwigModule<" + typeid(T).name() + ">::convert");

            return mToPyObject((void *)obj, disown ? 1 : 0);
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
