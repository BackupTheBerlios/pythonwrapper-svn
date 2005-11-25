#include "TestExtract.h"
#include <string.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TestExtract);

void TestExtract::testBool()
{
    Number f1((short)0);
    String f2("");
    Number f3((long)0);
    Number f4(0.0);
    BorrowedReference f5(Py_False);
    BorrowedReference f6(Py_None);

    Number t1((short)1);
    String t2("test");
    String t3("1");
    Number t4(1.0);
    BorrowedReference t5(Py_True);

    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(f1));
    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(f2));
    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(f3));
    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(f4));
    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(f5));
    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(f6));

    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(t1));
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(t2));
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(t3));
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(t4));
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(t5));
}


void TestExtract::testString()
{
    String str("Test");
    CPPUNIT_ASSERT(strcmp("Test", extract<const char *>(str)) == 0);
}
