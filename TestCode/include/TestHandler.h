#ifndef _TestHandler_h_
#define _TestHandler_h_

#include "PWObject.h"
#include "PWHandler.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestHandler : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestHandler);
        CPPUNIT_TEST(testReferenceCounting);
        CPPUNIT_TEST_EXCEPTION(testNewReferenceNull, NullObjectException);
        CPPUNIT_TEST_EXCEPTION(testBorrowedReferenceNull, NullObjectException);
        CPPUNIT_TEST_EXCEPTION(testNewReferencePython, PythonException);
        CPPUNIT_TEST_EXCEPTION(testBorrrowedReferencePython, PythonException);
    CPPUNIT_TEST_SUITE_END();
public:
    void testReferenceCounting();
    void testNewReferenceNull();
    void testBorrowedReferenceNull();
    void testNewReferencePython();
    void testBorrrowedReferencePython();

    void tearDown();
};

#endif
