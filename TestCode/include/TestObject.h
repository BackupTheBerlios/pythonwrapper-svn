#ifndef _TestObject_h_
#define _TestObject_h_

#include "PWObject.h"
#include "PWExceptions.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestObject : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestObject);
        CPPUNIT_TEST(testConstructor);
        CPPUNIT_TEST(testCopyConstructor);
        CPPUNIT_TEST(testDefaultConstructor);
        CPPUNIT_TEST(testLength);
        CPPUNIT_TEST(testHasAttr);
        CPPUNIT_TEST(testGetSetAttr);
        CPPUNIT_TEST(testDelAttr);
        CPPUNIT_TEST(testHasAttrString);
        CPPUNIT_TEST(testGetSetAttrString);
        CPPUNIT_TEST(testDelAttrString);
        CPPUNIT_TEST(testCallFunction);
        CPPUNIT_TEST(testCallFunctionArgs);
        CPPUNIT_TEST(testCallFunctionNamedArgs);
        CPPUNIT_TEST(testMemberFunction);
        CPPUNIT_TEST(testMemberFunctionArgs);
        CPPUNIT_TEST(testMemberFunctionNamedArgs);
        CPPUNIT_TEST(testRefCount);
        CPPUNIT_TEST(testBorrowReference);
        CPPUNIT_TEST(testNewReference);

        CPPUNIT_TEST(testNot);
        CPPUNIT_TEST(testTrue);
        CPPUNIT_TEST_EXCEPTION(testNotThrows, PythonException);
        CPPUNIT_TEST_EXCEPTION(testTrueThrows, PythonException);
        
        CPPUNIT_TEST_EXCEPTION(testMemberFunctionMissing, PythonException);
        CPPUNIT_TEST_EXCEPTION(testMemberFunctionArgsMissing, PythonException);
        CPPUNIT_TEST_EXCEPTION(testMemberFunctionNamedArgsMissing, PythonException);
        
        CPPUNIT_TEST_EXCEPTION(testCallFunctionException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testCallFunctionArgsException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testCallFunctionNamedArgsException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testMemberFunctionException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testMemberFunctionArgsException, PythonException);
        CPPUNIT_TEST_EXCEPTION(testMemberFunctionNamedArgsException, PythonException);
    CPPUNIT_TEST_SUITE_END();
public:
    void testConstructor();        // Object(ReferenceHandler &)
    void testCopyConstructor();    // Object(const Object &)
    void testDefaultConstructor(); // Object()
    

    void testNot();        // operator !() const
    void testTrue();       // operator void *() const
    void testNotThrows();  // operator !() const
    void testTrueThrows(); // operator void *() const
    void testLength();     // length() const

    void testHasAttr();    // hasAttr(const Object &) const
    void testGetSetAttr(); // getAttr(const Object &) const | setAttr(const Object &)
    void testDelAttr();    // delAttr(const Object &)

    void testHasAttrString();    // hasAttr(const String &) const
    void testGetSetAttrString(); // getAttr(const String &) const | setAttr(const Object &)
    void testDelAttrString();    // delAttr(const String &)

    void testCallFunction();
    void testCallFunctionArgs();
    void testCallFunctionNamedArgs();

    void testMemberFunction();
    void testMemberFunctionArgs();
    void testMemberFunctionNamedArgs();

    void testCallFunctionException();
    void testCallFunctionArgsException();
    void testCallFunctionNamedArgsException();

    void testMemberFunctionException();
    void testMemberFunctionArgsException();
    void testMemberFunctionNamedArgsException();

    void testMemberFunctionMissing();
    void testMemberFunctionArgsMissing();
    void testMemberFunctionNamedArgsMissing();

    void testRefCount();
    void testBorrowReference();
    void testNewReference();

    void setUp();
    void tearDown();

private:
    Object ClassA;
    Object ClassB;
};

#endif
