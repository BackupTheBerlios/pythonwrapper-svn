#include "TestSystem.h"
#include "PWExtract.h"
#include <string.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TestSystem);

void TestSystem::setUp()
{
    sys = new System();
}

void TestSystem::tearDown()
{
    delete sys;
}


void TestSystem::testEvaluate()
{
    Object obj = sys->evaluate("'test' + ' test2'");
    CPPUNIT_ASSERT(strcmp("test test2", extract<const char *>(obj)) == 0);

    obj = sys->evaluate("3**3 - 9 + -18");
    CPPUNIT_ASSERT_EQUAL(0, extract<int>(obj));
}


void TestSystem::testRunString()
{
    Object obj = sys->runString("val = 3; obj = `val`");
    CPPUNIT_ASSERT(Py_None == obj.borrowReference());

    obj = sys->evaluate("val");
    CPPUNIT_ASSERT_EQUAL(3, extract<int>(obj));

    obj = sys->evaluate("obj");
    CPPUNIT_ASSERT(strcmp("3", extract<const char *>(obj)) == 0);
}


void TestSystem::testGetObject()
{
    Object obj = sys->runString("val = 3; obj = `val`");
    CPPUNIT_ASSERT(Py_None == obj.borrowReference());

    obj = sys->getObject("val");
    CPPUNIT_ASSERT_EQUAL(3, extract<int>(obj));

    obj = sys->getObject("obj");
    CPPUNIT_ASSERT(strcmp("3", extract<const char *>(obj)) == 0);
}


void TestSystem::testGetObjectException()
{
    sys->getObject("asdf");
}

void TestSystem::testEvaluateException()
{
    sys->evaluate("asdf");
}


void TestSystem::testRunStringException()
{
    sys->runString("asdf");
}


void TestSystem::testRunFile()
{
    CPPUNIT_FAIL("System::runFile crashes.");
    sys->runFile("NoErrors.py");
}

void TestSystem::testRunFileException()
{
    CPPUNIT_FAIL("System::runFile crashes.");
    sys->runFile("Errors.py");
}


void TestSystem::testNamespaceCopy()
{
    System sys2;

    CPPUNIT_ASSERT(sys->getNamespace().borrowReference() !=
        sys2.getNamespace().borrowReference());

    CPPUNIT_ASSERT(PyDict_Check(sys->getNamespace().borrowReference()));
}
