#include "TestHandler.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestHandler);

void TestHandler::testReferenceCounting()
{
    PyObject *obj = 0,
             *obj2 = 0;
    obj = PyList_New(0);

    CPPUNIT_ASSERT(obj);
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    NewReference *nr = new NewReference(obj);
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    delete nr;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    BorrowedReference *br = new BorrowedReference(obj);
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    br->contained();
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    br->contained();
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);

    delete br;
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);

    Py_DECREF(obj);
    Py_DECREF(obj);
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    Object *pwObject1;

    int count = Py_None->ob_refcnt;
    pwObject1 = new Object();
    CPPUNIT_ASSERT_EQUAL(count + 1, Py_None->ob_refcnt);

    delete pwObject1;
    CPPUNIT_ASSERT_EQUAL(count, Py_None->ob_refcnt);
    
    pwObject1 = new Object(BorrowedReference(obj));
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    delete pwObject1;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    Py_INCREF(obj);
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    pwObject1 = new Object(NewReference(obj));
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    delete pwObject1;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    pwObject1 = new Object(BorrowedReference(obj));
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    Object *pwObject2 = new Object(BorrowedReference(obj));
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);

    *pwObject1 = *pwObject2;
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);

    delete pwObject2;
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    obj2 = PyList_New(0);
    CPPUNIT_ASSERT_EQUAL(1, obj2->ob_refcnt);

    Object *pwObject3 = 0;
    pwObject2 = new Object(BorrowedReference(obj2));
    pwObject3 = pwObject2;
    CPPUNIT_ASSERT_EQUAL(2, obj2->ob_refcnt);

    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);
    *pwObject2 = *pwObject1;
    CPPUNIT_ASSERT_EQUAL(1, obj2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);

    *pwObject2 = *pwObject1;
    CPPUNIT_ASSERT_EQUAL(1, obj2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);

    delete pwObject3;
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    delete pwObject1;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(1, obj2->ob_refcnt);

    Py_DECREF(obj);
    Py_DECREF(obj2);
}



void TestHandler::testNewReferenceNull()
{
    NewReference(0);
}

void TestHandler::testBorrowedReferenceNull()
{
    BorrowedReference(0);
}

void TestHandler::testNewReferencePython()
{
    PyErr_SetString(PyExc_TypeError, "Test message.");
    NewReference(0);
}
void TestHandler::testBorrrowedReferencePython()
{
    PyErr_SetString(PyExc_TypeError, "Test message.");
    BorrowedReference(0);
}

void TestHandler::tearDown()
{
    CPPUNIT_ASSERT(!PyErr_Occurred());
}

void TestHandler::testReferenceNew()
{
    NewReference nr(PyString_FromString("Test"));
    CPPUNIT_ASSERT_EQUAL(1, nr.getPtr()->ob_refcnt);

    Object obj1(nr);
    CPPUNIT_ASSERT_EQUAL(1, nr.getPtr()->ob_refcnt);

    Object obj2(nr);
    CPPUNIT_ASSERT_EQUAL(2, nr.getPtr()->ob_refcnt);

    Object obj3(nr);
    CPPUNIT_ASSERT_EQUAL(3, nr.getPtr()->ob_refcnt);
}

void testReferenceBorrowed()
{
    NewReference nr(PyString_FromString("Test"));
    CPPUNIT_ASSERT_EQUAL(2, nr.getPtr()->ob_refcnt);

    Object obj1(nr);
    CPPUNIT_ASSERT_EQUAL(2, nr.getPtr()->ob_refcnt);

    Object obj2(nr);
    CPPUNIT_ASSERT_EQUAL(3, nr.getPtr()->ob_refcnt);

    Object obj3(nr);
    CPPUNIT_ASSERT_EQUAL(4, nr.getPtr()->ob_refcnt);

    Py_DECREF(nr.getPtr());
}
