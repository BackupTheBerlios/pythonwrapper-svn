#ifndef _TestSwigModule_h_
#define _TestSwigModule_h_

#include <PythonWrapper.h>
#include "PWInterpreter.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestSwigModule : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSwigModule);
        CPPUNIT_TEST(testSwigModule);
        CPPUNIT_TEST(testToPyObject);
        CPPUNIT_TEST(testToPointer);
    CPPUNIT_TEST_SUITE_END();
public:
    void testSwigModule();
    void testToPyObject();
    void testToPointer();
};

#endif
