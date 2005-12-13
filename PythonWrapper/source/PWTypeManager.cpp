#include "PWTypeManager.h"
#include "PWExceptions.h"

using namespace pw;

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
}


TypeManager::~TypeManager()
{
}


void TypeManager::addDelimitedType(const String &type, const String &delim, ConverterInterface *module)
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
            addType(tmp, module);

        // update the offset value, recalculate next index
        offset = index + delim.length();
        index = type.find(delim, offset);
    } // while

    // calculate this one last time, since we have one left over
    tmp = type.substr(offset, index - offset);
    if (tmp.length())
        addType(tmp, module);
}

void TypeManager::addType(const String &type, ConverterInterface *module)
{
    TypeModuleMap::iterator itr = mTypes.find(type);
    if (itr != mTypes.end())
        PW_Warn(type + " already added to TypeManager.", "TypeManager::addType");

    mTypes[type] = module;
}

ConverterInterface *TypeManager::findConverter(const String &type)
{
    TypeModuleMap::iterator itr = mTypes.find(type);
    if (itr == mTypes.end())
        PW_Except(type + " converter not found.", "TypeManager::findConverter");

    return itr->second;
}
