#ifndef _TestTypeManager_h_
#define _TestTypeManager_h_

#include <PythonWrapper.h>
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestTypeManager : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestTypeManager);
        CPPUNIT_TEST(testFindConverter);
        CPPUNIT_TEST_EXCEPTION(testFindThrow, Exception);
    CPPUNIT_TEST_SUITE_END();
public:
    void testFindConverter();
    void testFindThrow();
};

#endif
