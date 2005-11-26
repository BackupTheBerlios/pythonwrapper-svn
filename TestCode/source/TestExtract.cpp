#include "TestExtract.h"
#include "PWBuild.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestExtract);

void TestExtract::testBool()
{
    Object f1 = build((short)0);
    Object f2 = build("");
    Object f3 = build((long)0);
    Object f4 = build(0.0);
    Object f5 = build(false);
    BorrowedReference f6(Py_None);

    Object t1 = build((short)1);
    Object t2 = build("test");
    Object t3 = build("1");
    Object t4 = build(1.0);
    Object t5 = build(true);

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
    Object str = build("Test");
    CPPUNIT_ASSERT(strcmp("Test", extract<const char *>(str)) == 0);
}
