#include "TestBuild.h"
#include "PWExtract.h"
#include "PWBuild.h"

#include <string.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TestBuild);

void TestBuild::testBool()
{
    Object t = build(true);
    Object f = build(false);

    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(t));
    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(f));
}


void TestBuild::testString()
{
    const char *cs1 = "Test 1.";
    const char *cs2 = "Test 2.";

    Object s1 = build(cs1);
    Object s2 = build(cs2);

    CPPUNIT_ASSERT(strcmp(cs1, extract<const char *>(s1)) == 0);
    CPPUNIT_ASSERT(strcmp(cs2, extract<const char *>(s2)) == 0);
}
