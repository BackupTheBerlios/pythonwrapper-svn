#ifndef _TestList_h_
#define _TestList_h_

#include "PWList.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestList : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestList);
        CPPUNIT_TEST(testLength);
        CPPUNIT_TEST(testGetItem);
        CPPUNIT_TEST(testSetItem);
        CPPUNIT_TEST(testDelItem);
        CPPUNIT_TEST(testGetSlice);
        CPPUNIT_TEST(testSetSlice);
        CPPUNIT_TEST(testDelSlice);
        CPPUNIT_TEST(testAppend);
        CPPUNIT_TEST(testOperatorGet);
        CPPUNIT_TEST(testOperatorSet);
    CPPUNIT_TEST_SUITE_END();
public:
    void testLength();

    void testGetItem();
    void testSetItem();
    void testDelItem();

    void testGetSlice();
    void testSetSlice();
    void testDelSlice();

    void testAppend();
    void testOperatorGet();
    void testOperatorSet();
    
    void testReverse();
    void testSort();

    void setUp();
    void tearDown();

protected:
    List *mList;
    PyObject **mObjList;
};

#endif
