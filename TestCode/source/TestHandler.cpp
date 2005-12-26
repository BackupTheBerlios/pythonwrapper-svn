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

    nr->contained();
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    nr->contained();
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    delete nr;
    Py_DECREF(obj);
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
    PyErr_Clear();
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

void TestHandler::testReferenceBorrowed()
{
    BorrowedReference br(PyString_FromString("Test"));
    CPPUNIT_ASSERT_EQUAL(2, br.getPtr()->ob_refcnt);

    Py_DECREF(br.getPtr());
    CPPUNIT_ASSERT_EQUAL(1, br.getPtr()->ob_refcnt);

    Object obj1(br);
    CPPUNIT_ASSERT_EQUAL(1, br.getPtr()->ob_refcnt);

    Object obj2(br);
    CPPUNIT_ASSERT_EQUAL(2, br.getPtr()->ob_refcnt);

    Object obj3(br);
    CPPUNIT_ASSERT_EQUAL(3, br.getPtr()->ob_refcnt);

}



void TestHandler::testUnusedNew()
{
    PyObject *obj = PyString_FromString("Test");

    Py_INCREF(obj);
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    NewReference *nr = new NewReference(obj);
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    delete nr;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    Py_DECREF(obj);
}

void TestHandler::testUnusedBorrowed()
{
    PyObject *obj = PyString_FromString("Test");
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    BorrowedReference *br = new BorrowedReference(obj);
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    delete br;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    Py_DECREF(obj);
}


void TestHandler::testBorrowCopy()
{
    BorrowedReference *b1 = 0, *b2 = 0;

    PyObject *obj = PyString_FromString("Test");
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    b1 = new BorrowedReference(obj);
    b2 = new BorrowedReference(*b1);
    delete b1;
    delete b2;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    b1 = new BorrowedReference(obj);
    b2 = new BorrowedReference(*b1);
    b1->contained();
    b2->contained();
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);

    delete b1;
    delete b2;
    CPPUNIT_ASSERT_EQUAL(3, obj->ob_refcnt);
    Py_DECREF(obj);
    Py_DECREF(obj);

    b1 = new BorrowedReference(obj);
    b1->contained();
    b2 = new BorrowedReference(*b1);
    delete b1;
    delete b2;
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);
    Py_DECREF(obj);

    b1 = new BorrowedReference(obj);
    b2 = new BorrowedReference(*b1);
    b1->contained();
    delete b1;
    delete b2;
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);
    Py_DECREF(obj);

    b1 = new BorrowedReference(obj);
    b2 = new BorrowedReference(*b1);
    b2->contained();
    delete b1;
    delete b2;
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);
    Py_DECREF(obj);

    Py_DECREF(obj);
}


void TestHandler::testNewCopy()
{
    NewReference *n1 = 0, *n2 = 0;

    PyObject *obj = PyString_FromString("Test");
    Py_INCREF(obj);
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);

    n1 = new NewReference(obj);
    n2 = new NewReference(*n1);
    delete n1;
    delete n2;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    n1 = new NewReference(obj);
    n2 = new NewReference(*n1);
    n1->contained();
    n2->contained();
    delete n1;
    delete n2;
    CPPUNIT_ASSERT_EQUAL(2, obj->ob_refcnt);
    Py_DECREF(obj);
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);


    n1 = new NewReference(obj);
    n1->contained();
    n2 = new NewReference(*n1);
    delete n1;
    delete n2;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);


    n1 = new NewReference(obj);
    n2 = new NewReference(*n1);
    n1->contained();
    delete n1;
    delete n2;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);


    n1 = new NewReference(obj);
    n2 = new NewReference(*n1);
    n2->contained();
    delete n1;
    delete n2;
    CPPUNIT_ASSERT_EQUAL(1, obj->ob_refcnt);

    Py_DECREF(obj);
}
