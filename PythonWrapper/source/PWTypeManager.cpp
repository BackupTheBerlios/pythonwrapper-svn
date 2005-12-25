#include "PWTypeManager.h"
#include "PWExceptions.h"
#include "PWLogManager.h"

namespace pw
{
    TypeManager *Singleton<TypeManager>::sInstance = 0;

    TypeManager &TypeManager::getSingleton()
    {
        assert(sInstance);
        return *sInstance;
    } // getSingleton()


    TypeManager *TypeManager::getSingletonPtr()
    {
        return sInstance;
    } // getSingletonPtr()


    TypeManager::TypeManager()
    {
        PW_LOG("TypeManager created.", "TypeManager::TypeManager", LogManager::High);
    }


    TypeManager::~TypeManager()
    {
        PyTypeModuleMap::iterator itr;
        for (itr = mPyTypes.begin(); itr != mPyTypes.end(); ++itr)
            Py_DECREF(itr->first);

        mPyTypes.clear();

        PW_LOG("TypeManager destroyed.", "TypeManager::~TypeManager", LogManager::High);
    }


    void TypeManager::addDelimitedType(const String &type, const String &delim, ConverterInterface *module, void *typeInfo)
    {
        String tmp;                // temporary value to test for empty strings
        size_t offset = 0;         // the offset we are working at
        size_t index = type.find(delim, offset);  // the most recent index
        
        // while we have found more delimiters
        while (index != String::npos)
        {
            // get the substring
            tmp = type.substr(offset, index - offset);

            // if the substring is not empty, add the type
            if (tmp.length())
                addType(tmp, module, typeInfo);

            // update the offset value, recalculate next index
            offset = index + delim.length();
            index = type.find(delim, offset);
        } // while

        // calculate this one last time, since we have one left over
        tmp = type.substr(offset, index - offset);
        if (tmp.length())
            addType(tmp, module, typeInfo);
    }

    void TypeManager::addType(const String &type, ConverterInterface *module, void *typeInfo)
    {
        TypeModuleMap::iterator itr = mTypes.find(type);
        if (itr != mTypes.end())
            PW_Warn(type + " already added to TypeManager.", "TypeManager::addType");

        mTypes[type] = TypeInfoPair(module, typeInfo);
    }

    void TypeManager::addType(PyTypeObject *obj, ConverterInterface *module)
    {
        PyTypeModuleMap::iterator itr = mPyTypes.find(obj);
        if (itr != mPyTypes.end())
            PW_Warn("This PyTypeObject is already registered with TypeManager.", "TypeManager::addType");

        Py_INCREF(obj);
        mPyTypes[obj] = module;
    }

    const TypeManager::TypeInfoPair &TypeManager::findConverter(const String &type)
    {
        TypeModuleMap::iterator itr = mTypes.find(type);
        if (itr == mTypes.end())
            PW_Except(type + " converter not found.", "TypeManager::findConverter");

        return itr->second;
    }

    ConverterInterface *TypeManager::findConverter(PyTypeObject *type)
    {
        PyTypeModuleMap::iterator itr = mPyTypes.find(type);
        if (itr == mPyTypes.end())
            PW_Except("Could not find a converter for specified PyTypeObject.", "TypeManager::findConverter");

        return itr->second;
    }
} // namespace pw
