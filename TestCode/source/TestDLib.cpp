#include "TestDLib.h"
#include "PWDLib.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestDLib);

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef void (*vvfp)();
typedef int (*ivfp)();
typedef const String &(*svfp)();

void TestDLib::testLoad()
{
    PW_DLIB dlib("TestLib.dll");
    dlib.load();

    vvfp init = (vvfp)dlib.getSymbol("PW_Init");
    CPPUNIT_ASSERT(init);

    vvfp deinit = (vvfp)dlib.getSymbol("PW_Deinit");
    CPPUNIT_ASSERT(deinit);

    ivfp getCount = (ivfp)dlib.getSymbol("PW_GetCount");
    CPPUNIT_ASSERT(getCount);

    svfp getName = (svfp)dlib.getSymbol("PW_GetName");
    CPPUNIT_ASSERT(getName);

    dlib.unload();
}


void TestDLib::testBaseLoad()
{
    hInstance lib = LoadLibrary("TestLib.dll");
    CPPUNIT_ASSERT(lib);
    
    vvfp init = (vvfp)GetProcAddress(lib, "PW_Init");
    CPPUNIT_ASSERT(init);
    
    BOOL rval = FreeLibrary(lib);
    CPPUNIT_ASSERT(rval);
}
