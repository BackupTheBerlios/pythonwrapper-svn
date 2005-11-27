#ifndef _TestDLib_h_
#define _TestDLib_h_

#include "PWList.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestDLib : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDLib);
        CPPUNIT_TEST(testLoad);
        CPPUNIT_TEST(testBaseLoad);
    CPPUNIT_TEST_SUITE_END();
public:
    void testLoad();
    void testBaseLoad();

protected:
};

#endif
