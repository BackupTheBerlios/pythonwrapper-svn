#ifndef _TestExtract_h_
#define _TestExtract_h_

#include "PWExtract.h"
#include "PWObject.h"
#include "PWNumber.h"
#include "PWString.h"
using namespace pw;

#include <cppunit/extensions/HelperMacros.h>

class TestExtract : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestExtract);
        CPPUNIT_TEST(testBool);
        CPPUNIT_TEST(testString);
        CPPUNIT_TEST(testValue<double>);
        CPPUNIT_TEST(testValue<unsigned short>);
        CPPUNIT_TEST(testValue<unsigned int>);
        CPPUNIT_TEST(testValue<unsigned long>);
        CPPUNIT_TEST(testValue<unsigned long long>);
        CPPUNIT_TEST(testValue<short>);
        CPPUNIT_TEST(testValue<int>);
        CPPUNIT_TEST(testValue<long>);
        CPPUNIT_TEST(testValue<long long>);
        CPPUNIT_TEST(testValue<float>);
        CPPUNIT_TEST(testValue<bool>);

        CPPUNIT_TEST_EXCEPTION(testThrows<double>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<unsigned short>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<unsigned int>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<unsigned long>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<unsigned long long>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<short>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<int>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<long>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<long long>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<float>, PythonException);
        CPPUNIT_TEST_EXCEPTION(testThrows<const char *>, PythonException);

    CPPUNIT_TEST_SUITE_END();
public:
    void testBool();
    void testString();

    template <class T>
    void testValue()
    {
        long long one = 1000000000;
        short two = 1234;
        double three = 1000.1234; 

        Number _pyLong((long long)one);
        Number _pyInt((short)two);
        Number _pyFloat(three);

        CPPUNIT_ASSERT_EQUAL((T)one, extract<T>(_pyLong));
        CPPUNIT_ASSERT_EQUAL((T)two, extract<T>(_pyInt));
        CPPUNIT_ASSERT_EQUAL((T)three, extract<T>(_pyFloat));
    }

    template <class T>
    void testThrows()
    {
        BorrowedReference obj(Py_None);
        extract<T>(obj);
    }
};

#endif
