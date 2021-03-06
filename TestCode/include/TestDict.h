#ifndef _TestDict_h_
#define _TestDict_h_

#include "PWDict.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestDict : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDict);
        CPPUNIT_TEST(testStrings);
        CPPUNIT_TEST(testObjects);
        CPPUNIT_TEST(testLength);
        CPPUNIT_TEST(testItems);
        CPPUNIT_TEST(testKeys);
        CPPUNIT_TEST(testValues);
        CPPUNIT_TEST(testContains);
        CPPUNIT_TEST(testOperatorGet);
        CPPUNIT_TEST(testOperatorSet);
        CPPUNIT_TEST(testOperatorGetNull);
        CPPUNIT_TEST(testOperatorSetNull);

        CPPUNIT_TEST_EXCEPTION(testStringGetThrow, Exception);
        CPPUNIT_TEST_EXCEPTION(testGetThrow, PythonException);
        CPPUNIT_TEST_EXCEPTION(testStringDelThrow, PythonException);
        CPPUNIT_TEST_EXCEPTION(testDelThrow, PythonException);
    CPPUNIT_TEST_SUITE_END();
public:
    void testStrings();
    void testObjects();

    void testLength();
    void testItems();
    void testKeys();
    void testValues();
    void testContains();

    void testOperatorGet();
    void testOperatorGetNull();
    void testOperatorSet();
    void testOperatorSetNull();

    void testStringGetThrow();
    void testGetThrow();
    void testStringDelThrow();
    void testDelThrow();

    void setUp();
    void tearDown();

protected:
    Dict *mDict;
};

#endif
