#include "PWEmbedded.h"
#include "PWTypeManager.h"
#include "PWModuleManager.h"

using namespace pw;

void PW_addType(const char *type, const char *name, void *typeInfo)
{
    static TypeManager &tm = TypeManager::getSingleton();
    static ModuleManager &mm = ModuleManager::getSingleton();

    Module *module = mm.findModule(name);
    tm.addDelimitedType(type, "|", module, typeInfo);
}

void PW_addPyType(PyTypeObject *type, const char *name)
{
    TypeManager &tm = TypeManager::getSingleton();
    ModuleManager &mm = ModuleManager::getSingleton();

    Module *module = mm.findModule(name);
    tm.addType(type, module);
}
