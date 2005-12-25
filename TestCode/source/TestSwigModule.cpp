#include "TestSwigModule.h"
#include "TSClassA.h"
#include "TSClassB.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestSwigModule);

void TestSwigModule::testSwigModule()
{
    Object a = i->getObject("a");
    Object b = i->getObject("b");
    Object aval = i->evaluate("a.getValue");
    Object bval = i->evaluate("b.getValue");
    Object ival = i->evaluate("i.getValue");

    CPPUNIT_ASSERT_EQUAL(extract<int>(aval()), 7);
    CPPUNIT_ASSERT_EQUAL(extract<int>(bval()), 42);
    CPPUNIT_ASSERT_EQUAL(extract<int>(ival(Tuple::build(a))), 7);
    CPPUNIT_ASSERT_EQUAL(extract<int>(ival(Tuple::build(b))), 42);
}

void TestSwigModule::testBuild()
{
    i->reset();

    ts::A *a = new ts::A();
    Object pa = build<ts::A *>(a, true);
    CPPUNIT_ASSERT_EQUAL(7, extract<int>(pa.call("getValue")));

    i->getNamespace()["a"] = pa;
    i->runString("a.setValue(84)\n");

    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(i->evaluate("a.this.own()")));
    CPPUNIT_ASSERT_EQUAL(84, extract<int>(pa.call("getValue")));
    CPPUNIT_ASSERT_EQUAL(84, extract<int>(i->evaluate("a.getValue()")));
}

void TestSwigModule::testExtract()
{
    Object pa = i->getObject("a");
    Object pb = i->getObject("b");
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(i->evaluate("a.this.own()")));
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(i->evaluate("b.this.own()")));

    ts::A *a = extract<ts::A*>(pa, false);
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(i->evaluate("a.this.own()")));

    a = extract<ts::A *>(pa, true);
    CPPUNIT_ASSERT_EQUAL(false, extract<bool>(i->evaluate("a.this.own()")));

    CPPUNIT_ASSERT_EQUAL(7, extract<int>(i->evaluate("a.getValue()")));
    CPPUNIT_ASSERT_EQUAL(7, a->getValue());
    i->runString("a.setValue(22)\n");
    CPPUNIT_ASSERT_EQUAL(22, extract<int>(i->evaluate("a.getValue()")));
    CPPUNIT_ASSERT_EQUAL(22, a->getValue());

    i->runString("a.this.acquire()");
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(i->evaluate("a.this.own()")));

    a = extract<ts::B *>(pb, false);
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(i->evaluate("b.this.own()")));
    CPPUNIT_ASSERT_EQUAL(42, extract<int>(i->evaluate("b.getValue()")));
    CPPUNIT_ASSERT_EQUAL(42, a->getValue());

    a->setValue(22);
    CPPUNIT_ASSERT_EQUAL(22, extract<int>(i->evaluate("b.getValue()")));
    CPPUNIT_ASSERT_EQUAL(22, a->getValue());
}


void TestSwigModule::setUp()
{
    i = new Interpreter();
    i->runString(
        "import TestSwig\n"
        "a = TestSwig.A()\n"
        "b = TestSwig.B()\n"
        "i = TestSwig.Inner()\n"
        );

    CPPUNIT_ASSERT(! PyErr_Occurred());
}


void TestSwigModule::tearDown()
{
    delete i;
    CPPUNIT_ASSERT(!PyErr_Occurred());
}