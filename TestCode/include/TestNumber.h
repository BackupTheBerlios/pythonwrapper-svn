#ifndef _TestNumber_h_
#define _TestNumber_h_

#include "PWNumber.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestNumber : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestNumber);
        CPPUNIT_TEST(testEmptyConstructor); 
        CPPUNIT_TEST(testDouble);
        CPPUNIT_TEST(testUnsignedShort);
        CPPUNIT_TEST(testUnsignedLong);
        CPPUNIT_TEST(testUnsignedLongLong);
        CPPUNIT_TEST(testShort);
        CPPUNIT_TEST(testLong);
        CPPUNIT_TEST(testLongLong);
    CPPUNIT_TEST_SUITE_END();
public:
    void testEmptyConstructor();
    void testDouble();
    void testUnsignedShort();
    void testUnsignedLong();
    void testUnsignedLongLong();
    void testShort();
    void testLong();
    void testLongLong();

protected:
};

#endif
