#include "TestInterpreter.h"
#include "PythonWrapper.h"
#include <string.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TestInterpreter);

void TestInterpreter::setUp()
{
    sys = new Interpreter();
}

void TestInterpreter::tearDown()
{
    delete sys;
    CPPUNIT_ASSERT(!PyErr_Occurred());
}


void TestInterpreter::testEvaluate()
{
    Object obj = sys->evaluate("'test' + ' test2'");
    CPPUNIT_ASSERT(strcmp("test test2", extract<const char *>(obj)) == 0);

    obj = sys->evaluate("3**3 - 9 + -18");
    CPPUNIT_ASSERT_EQUAL(0, extract<int>(obj));
}


void TestInterpreter::testRunString()
{
    Object obj = sys->runString("val = 3; obj = `val`");
    CPPUNIT_ASSERT(Py_None == obj.borrowReference());

    obj = sys->evaluate("val");
    CPPUNIT_ASSERT_EQUAL(3, extract<int>(obj));

    obj = sys->evaluate("obj");
    CPPUNIT_ASSERT(strcmp("3", extract<const char *>(obj)) == 0);
}


void TestInterpreter::testGetObject()
{
    Object obj = sys->runString("val = 3; obj = `val`");
    CPPUNIT_ASSERT(Py_None == obj.borrowReference());

    obj = sys->getObject("val");
    CPPUNIT_ASSERT_EQUAL(3, extract<int>(obj));

    obj = sys->getObject("obj");
    CPPUNIT_ASSERT(strcmp("3", extract<const char *>(obj)) == 0);
}


void TestInterpreter::testGetObjectException()
{
    sys->getObject("asdf");
}

void TestInterpreter::testEvaluateException()
{
    sys->evaluate("asdf");
}


void TestInterpreter::testRunStringException()
{
    sys->runString("asdf");
}


void TestInterpreter::testRunFile()
{
    sys->runFile("NoErrors.py");
}

void TestInterpreter::testRunFileException()
{
    sys->runFile("Errors.py");
}


void TestInterpreter::testNamespaceCopy()
{
    Interpreter sys2;

    CPPUNIT_ASSERT(sys->getNamespace().borrowReference() !=
        sys2.getNamespace().borrowReference());

    CPPUNIT_ASSERT(PyDict_Check(sys->getNamespace().borrowReference()));
}


void TestInterpreter::testNamespaceSet()
{
    Dict namesp = sys->getNamespace();
    namesp["test"] = build((short)7);

    CPPUNIT_ASSERT(namesp.contains(build("test")));
    CPPUNIT_ASSERT_EQUAL((short)7, extract<short>(namesp.getItem("test")));
    CPPUNIT_ASSERT_EQUAL(true, extract<bool>(sys->evaluate("test == 7")));
}


void TestInterpreter::testNamespaceGet()
{
    Dict namesp = sys->getNamespace();
    sys->runString("test = 70");

    CPPUNIT_ASSERT(namesp.contains(build("test")));
    CPPUNIT_ASSERT_EQUAL((short)70, extract<short>(namesp.getItem("test")));
    CPPUNIT_ASSERT_EQUAL((short)70, extract<short>(namesp["test"]));
}
