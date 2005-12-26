#ifndef _TestBuild_h_
#define _TestBuild_h_

#include "PWBuild.h"
using namespace pw;

#define TEST_ALL(expected, actual)  \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("double", (double)(expected), extract<double>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("unsigned short", (unsigned short)(expected), extract<unsigned short>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("unsigned long", (unsigned long)(expected), extract<unsigned long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("unsigned long long", (unsigned long long)(expected), extract<unsigned long long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("long", (long)(expected), extract<long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("long long", (long long)(expected), extract<long long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("bool", (expected) ? true : false, extract<bool>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("short", (short)(expected), extract<short>((actual)));

#include <cppunit/extensions/HelperMacros.h>

class TestBuild : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestBuild);
        CPPUNIT_TEST(testBuild<double>);
        CPPUNIT_TEST(testBuild<unsigned short>);
        CPPUNIT_TEST(testBuild<unsigned long>);
        CPPUNIT_TEST(testBuild<unsigned long long>);
        CPPUNIT_TEST(testBuild<short>);
        CPPUNIT_TEST(testBuild<long>);
        CPPUNIT_TEST(testBuild<long long>);
        CPPUNIT_TEST(testBool);
        CPPUNIT_TEST(testString);
    CPPUNIT_TEST_SUITE_END();
public:
    template <class Numeric>
    void testBuild()
    {
        Numeric f0 = (Numeric)3.14159265,
                f1 = (Numeric)100.0,
                f2 = (Numeric)123.1234123412342,
                i0 = (Numeric)0xFFFF,
                i1 = (Numeric)0,
                i2 = (Numeric)1,
                i3 = (Numeric)0xFFFE,
                i4 = (Numeric)0xFF;

        TEST_ALL(f0, build(f0));
        TEST_ALL(f1, build(f1));
        TEST_ALL(f2, build(f2));
        TEST_ALL(i0, build(i0));
        TEST_ALL(i1, build(i1));
        TEST_ALL(i2, build(i2));
        TEST_ALL(i3, build(i3));
        TEST_ALL(i4, build(i4));
    }

    void testBool();
    void testString();

    void tearDown() {CPPUNIT_ASSERT(!PyErr_Occurred());}
protected:
};

#endif
