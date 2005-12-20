#include "TestTypeManager.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestTypeManager);

void TestTypeManager::testFindConverter()
{
    TypeManager &tm = TypeManager::getSingleton();
    tm.findConverter("char *");
    tm.findConverter("ts::A *");
    tm.findConverter("ts::B *");
    tm.findConverter("ts::Inner *");
}

void TestTypeManager::testFindThrow()
{
    TypeManager &tm = TypeManager::getSingleton();
    tm.findConverter("Not a Type.");
}
