#ifndef _PWTypeManager_h_
#define _PWTypeManager_h_

#include "PWCommon.h"
#include "PWString.h"
#include "PWSingleton.h"
#include "PWConverterInterface.h"

#include <map>

namespace pw
{
    class PW_EXPORT TypeManager : public Singleton<TypeManager>
    {
    public:
        static TypeManager &getSingleton();
        static TypeManager *getSingletonPtr();

    public:
        TypeManager();
        ~TypeManager();

        void addDelimitedType(const String &type, const String &delim, ConverterInterface *module);
        void addType(const String &type, ConverterInterface *module);

        ConverterInterface *findConverter(const String &type);

    private:
        typedef std::map<String, ConverterInterface *> TypeModuleMap;
        TypeModuleMap mTypes;
    };
}

#endif
