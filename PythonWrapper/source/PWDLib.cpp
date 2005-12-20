#include "PWDLib.h"

namespace pw
{
    DLib::DLib(const String &libraryName)
    : mLibraryName(libraryName)
    {
    }

    DLib::~DLib()
    {
    }

    const String &DLib::getLibraryName() const
    {
        return mLibraryName;
    }
} // namespace pw