#include "PWEmbedded.h"
#include "PWTypeManager.h"

using namespace pw;

void PW_addType(const char *str, void *module)
{
    static TypeManager *tm = TypeManager::getSingletonPtr();
    assert(tm);

    tm->addDelimitedType(str, "|", (ConverterInterface *)module);
}

void PW_addPyType(PyTypeObject *type, void *module)
{
    TypeManager &tm = TypeManager::getSingleton();
    tm.addType(type, (ConverterInterface *)module);
}
