#ifndef _TestSystem_h_
#define _TestSystem_h_

#include "PWSystem.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestSystem : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSystem);
        CPPUNIT_TEST(testEvaluate);
        CPPUNIT_TEST(testRunString);
        CPPUNIT_TEST(testGetObject);
        CPPUNIT_TEST(testRunFile);
        CPPUNIT_TEST(testNamespaceCopy);

        CPPUNIT_TEST_EXCEPTION(testGetObjectException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testEvaluateException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testRunStringException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testRunFileException, PythonException);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testEvaluate();
    void testRunString();
    void testGetObject();
    void testRunFile();
    void testNamespaceCopy();

    void testGetObjectException();
    void testEvaluateException();
    void testRunStringException();
    void testRunFileException();
private:
    System *sys;
};

#endif
