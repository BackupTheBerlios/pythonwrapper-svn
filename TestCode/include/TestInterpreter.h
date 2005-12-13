#ifndef _TestInterpreter_h_
#define _TestInterpreter_h_

#include "PWInterpreter.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestInterpreter : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestInterpreter);
        CPPUNIT_TEST_EXCEPTION(testRunFileException, PythonException);
        CPPUNIT_TEST(testEvaluate);
        CPPUNIT_TEST(testRunString);
        CPPUNIT_TEST(testGetObject);
        CPPUNIT_TEST(testRunFile);
        CPPUNIT_TEST(testNamespaceSet);
        CPPUNIT_TEST(testNamespaceGet);
        CPPUNIT_TEST(testNamespaceCopy);

        CPPUNIT_TEST_EXCEPTION(testGetObjectException, Exception);
        CPPUNIT_TEST_EXCEPTION(testEvaluateException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testRunStringException, PythonException);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testEvaluate();
    void testRunString();
    void testGetObject();
    void testRunFile();
    void testNamespaceGet();
    void testNamespaceSet();
    void testNamespaceCopy();

    void testGetObjectException();
    void testEvaluateException();
    void testRunStringException();
    void testRunFileException();
private:
    Interpreter *sys;
};

#endif
