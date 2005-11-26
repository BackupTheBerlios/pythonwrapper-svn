#ifndef _SWSingleton_h_
#define _SWSingleton_h_

#include "PWCommon.h"
#include <cassert>

namespace pw
{
    template <class T>
    class Singleton
    {
    public:
        Singleton();
        virtual ~Singleton();
    protected:
        static T *sInstance;
    };


    template <class T>
    Singleton<T>::Singleton()
    {
        assert(!sInstance);
        sInstance = static_cast<T *>(this);
    }

    template <class T>
    Singleton<T>::~Singleton()
    {
        assert(sInstance);
        sInstance = 0;
    }
}

#endif
