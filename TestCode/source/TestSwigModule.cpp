#include "TestSwigModule.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestSwigModule);

void TestSwigModule::testSwigModule()
{
    Interpreter i;

    i.runString(
        "import TestSwig\n"
        "a = TestSwig.A()\n"
        "b = TestSwig.B()\n"
        "i = TestSwig.Inner()\n"
        );
    CPPUNIT_ASSERT(! PyErr_Occurred());

    Object a = i.getObject("a");
    Object b = i.getObject("b");
    Object aval = i.evaluate("a.getValue");
    Object bval = i.evaluate("b.getValue");
    Object ival = i.evaluate("i.getValue");

    CPPUNIT_ASSERT_EQUAL(extract<int>(aval()), 7);
    CPPUNIT_ASSERT_EQUAL(extract<int>(bval()), 42);
    CPPUNIT_ASSERT_EQUAL(extract<int>(ival(Tuple::build(a))), 7);
    CPPUNIT_ASSERT_EQUAL(extract<int>(ival(Tuple::build(b))), 42);
}

void TestSwigModule::testToPyObject()
{
    CPPUNIT_ASSERT(false);
}

void TestSwigModule::testToPointer()
{
    CPPUNIT_ASSERT(false);
}
