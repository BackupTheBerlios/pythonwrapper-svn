#include "TestNumber.h"
#include "PWExtract.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestNumber);

#define TEST_ALL(expected, actual)  \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("double", (double)(expected), extract<double>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("unsigned short", (unsigned short)(expected), extract<unsigned short>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("unsigned long", (unsigned long)(expected), extract<unsigned long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("unsigned long long", (unsigned long long)(expected), extract<unsigned long long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("long", (long)(expected), extract<long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("long long", (long long)(expected), extract<long long>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("bool", (expected) ? true : false, extract<bool>((actual))); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE("short", (short)(expected), extract<short>((actual)));

void TestNumber::testEmptyConstructor()
{
    Number n;

    TEST_ALL(0, n);
}

void TestNumber::testDouble()
{
    double one = 3.14159265,
           two = 100.0,
           three = 123.1234123412342;

    Number nOne(one);
    Number nTwo(two);
    Number nThree(three);

    TEST_ALL(one, nOne);
    TEST_ALL(two, nTwo);
    TEST_ALL(three, nThree);

}

void TestNumber::testUnsignedShort()
{
    unsigned short one = 0xFFFF,
                   two = 0,
                   three = 1,
                   four = 0xFFFE,
                   five = 0xFF;

    Number nOne(one);
    Number nTwo(two);
    Number nThree(three);
    Number nFour(four);
    Number nFive(five);
    
    TEST_ALL(one, nOne);
    TEST_ALL(two, nTwo);
    TEST_ALL(three, nThree);
    TEST_ALL(four, nFour);
    TEST_ALL(five, nFive);
}


void TestNumber::testUnsignedLong()
{
    unsigned long one = 0xFFFF,
                  two = 0,
                  three = 1,
                  four = 0xFFFE,
                  five = 0xFF;

    Number nOne(one);
    Number nTwo(two);
    Number nThree(three);
    Number nFour(four);
    Number nFive(five);
    
    TEST_ALL(one, nOne);
    TEST_ALL(two, nTwo);
    TEST_ALL(three, nThree);
    TEST_ALL(four, nFour);
    TEST_ALL(five, nFive);
}

void TestNumber::testUnsignedLongLong()
{
    unsigned long long one = 0xFFFF,
                  two = 0,
                  three = 1,
                  four = 0xFFFE,
                  five = 0xFF;

    Number nOne(one);
    Number nTwo(two);
    Number nThree(three);
    Number nFour(four);
    Number nFive(five);
    
    TEST_ALL(one, nOne);
    TEST_ALL(two, nTwo);
    TEST_ALL(three, nThree);
    TEST_ALL(four, nFour);
    TEST_ALL(five, nFive);
}

void TestNumber::testShort()
{
    short one = 0xEFF,
          two = 0,
          three = 1,
          four = 0xFFF,
          five = 0xFF;

    Number nOne(one);
    Number nTwo(two);
    Number nThree(three);
    Number nFour(four);
    Number nFive(five);
    
    TEST_ALL(one, nOne);
    TEST_ALL(two, nTwo);
    TEST_ALL(three, nThree);
    TEST_ALL(four, nFour);
    TEST_ALL(five, nFive);
}

void TestNumber::testLong()
{
    long  one = 0xEFFF,
          two = 0,
          three = 1,
          four = 0xFFFF,
          five = 12345;

    Number nOne(one);
    Number nTwo(two);
    Number nThree(three);
    Number nFour(four);
    Number nFive(five);
    
    TEST_ALL(one, nOne);
    TEST_ALL(two, nTwo);
    TEST_ALL(three, nThree);
    TEST_ALL(four, nFour);
    TEST_ALL(five, nFive);
}

void TestNumber::testLongLong()
{
    long long one = 0xEFFF,
          two = 0,
          three = 1,
          four = 0xFFFF,
          five = 0xFF;

    Number nOne(one);
    Number nTwo(two);
    Number nThree(three);
    Number nFour(four);
    Number nFive(five);
    
    TEST_ALL(one, nOne);
    TEST_ALL(two, nTwo);
    TEST_ALL(three, nThree);
    TEST_ALL(four, nFour);
    TEST_ALL(five, nFive);
}
