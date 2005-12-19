#include "PWEmbedded.h"
#include "PWTypeManager.h"

using namespace pw;

void PW_addType(const char *str, void *module)
{
    static TypeManager *tm = TypeManager::getSingletonPtr();
    assert(tm);

    tm->addDelimitedType(str, "|", (ConverterInterface *)module);
}
