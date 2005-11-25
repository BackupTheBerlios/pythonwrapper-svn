#ifndef _TestTuple_h_
#define _TestTuple_h_

#include "PWTuple.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestTuple : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestTuple);
        CPPUNIT_TEST(testConstructor);
        CPPUNIT_TEST(testGetSet);
        CPPUNIT_TEST(testSize);
        CPPUNIT_TEST_EXCEPTION(testNonTupleConstructor, Exception);
    CPPUNIT_TEST_SUITE_END();
public:
    void testConstructor();
    void testNonTupleConstructor();
    void testGetSet();
    void testSize();
};

#endif
