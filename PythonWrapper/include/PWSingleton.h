#ifndef _PWSingleton_h_
#define _PWSingleton_h_

#include "PWCommon.h"
#include <cassert>

namespace pw
{
    /**
     * Singleton base class.
     */
    template <class T>
    class Singleton
    {
    public:
        static T &getSingleton(void)
		{
            assert(sInstance);
            return *sInstance;
        }

        static T* getSingletonPtr(void)
		{
            return sInstance;
        }

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
