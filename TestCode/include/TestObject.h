#ifndef _TestObject_h_
#define _TestObject_h_

#include "PWTuple.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestObject : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestObject);
        CPPUNIT_TEST(testCallFunction);
    CPPUNIT_TEST_SUITE_END();
public:
    void testCallFunction();
};

#endif
