#include "TestObject.h"
#include "PWString.h"
#include "PWHandler.h"
#include "PWExtract.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestObject);

void TestObject::testCallFunction()
{
    String str("test");
    CPPUNIT_ASSERT_EQUAL(4, extract<int>(str.call("__len__")));
}
