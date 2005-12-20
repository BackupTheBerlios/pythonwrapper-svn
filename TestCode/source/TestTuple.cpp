#include "TestTuple.h"
#include "PWTuple.h"
#include "PWHandler.h"
#include "PWBuild.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestTuple);


void TestTuple::testConstructor()
{
    PyObject *py_o0 = PyString_FromString("Test");
    PyObject *py_o1 = PyString_FromString("Test");
    PyObject *py_o2 = PyString_FromString("Test");
    Object *obj0 = 0;
    Object *obj1 = 0;
    Object *obj2 = 0;
    Tuple *tuple = 0;

    obj0 = new Object(BorrowedReference(py_o0));
    obj1 = new Object(BorrowedReference(py_o1));
    obj2 = new Object(BorrowedReference(py_o2));
    
    CPPUNIT_ASSERT_EQUAL(2, py_o0->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(2, py_o1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(2, py_o2->ob_refcnt);

    CPPUNIT_ASSERT_EQUAL(obj0->getRefCount(), py_o0->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(obj1->getRefCount(), py_o1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(obj2->getRefCount(), py_o2->ob_refcnt);

    tuple = new Tuple(3);
    CPPUNIT_ASSERT(! PyErr_Occurred());
    tuple->setItem(0, *obj0);
    CPPUNIT_ASSERT(! PyErr_Occurred());
    tuple->setItem(1, *obj1);
    CPPUNIT_ASSERT(! PyErr_Occurred());
    tuple->setItem(2, *obj2);
    CPPUNIT_ASSERT(! PyErr_Occurred());

    CPPUNIT_ASSERT_THROW(tuple->setItem(3, *obj2), PythonException);
    
    CPPUNIT_ASSERT_EQUAL(3, py_o0->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(3, py_o1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(3, py_o2->ob_refcnt);

    CPPUNIT_ASSERT_EQUAL(obj0->getRefCount(), py_o0->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(obj1->getRefCount(), py_o1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(obj2->getRefCount(), py_o2->ob_refcnt);

    delete tuple;
    
    CPPUNIT_ASSERT_EQUAL(2, py_o0->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(2, py_o1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(2, py_o2->ob_refcnt);

    CPPUNIT_ASSERT_EQUAL(obj0->getRefCount(), py_o0->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(obj1->getRefCount(), py_o1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(obj2->getRefCount(), py_o2->ob_refcnt);

    delete obj0;
    delete obj1;
    delete obj2;
    
    CPPUNIT_ASSERT_EQUAL(1, py_o0->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(1, py_o1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(1, py_o2->ob_refcnt);

    Py_DECREF(py_o0);
    Py_DECREF(py_o1);
    Py_DECREF(py_o2);
}



void TestTuple::testNonTupleConstructor()
{
    Tuple(NewReference(PyList_New(0)));
}


void TestTuple::testGetSet()
{
    Tuple tuple(1);
    Object obj(NewReference(PyList_New(0)));

    tuple.setItem(0, obj);
    CPPUNIT_ASSERT(tuple.getItem(0).borrowReference() == obj.borrowReference());
} // testGetSet()


void TestTuple::testSize()
{
    Tuple tuple0(0);
    CPPUNIT_ASSERT_EQUAL(0, tuple0.length());

    Tuple tuple1(1);
    CPPUNIT_ASSERT_EQUAL(1, tuple1.length());
    
    Tuple tuple2(2);
    CPPUNIT_ASSERT_EQUAL(2, tuple2.length());
    
    Tuple tuple3(3);
    CPPUNIT_ASSERT_EQUAL(3, tuple3.length());
    
    Tuple tuple4(4);
    CPPUNIT_ASSERT_EQUAL(4, tuple4.length());
    
    Tuple tuple5(5);
    CPPUNIT_ASSERT_EQUAL(5, tuple5.length());
}

void TestTuple::testBuild()
{
    Object o1 = build("one");
    Object o2 = build("two");
    Object o3 = build("three");
    Object o4 = build("four");

    CPPUNIT_ASSERT_EQUAL(1, o1.getRefCount());
    CPPUNIT_ASSERT_EQUAL(1, o2.getRefCount());
    CPPUNIT_ASSERT_EQUAL(1, o3.getRefCount());
    CPPUNIT_ASSERT_EQUAL(1, o4.getRefCount());
    
    {
        Tuple t1 = Tuple::build(o1);
        Tuple t2 = Tuple::build(o1, o2);
        Tuple t3 = Tuple::build(o1, o2, o3);
        Tuple t4 = Tuple::build(o1, o2, o3, o4);

        CPPUNIT_ASSERT_EQUAL(1, t1.getRefCount());
        CPPUNIT_ASSERT_EQUAL(1, t2.getRefCount());
        CPPUNIT_ASSERT_EQUAL(1, t3.getRefCount());
        CPPUNIT_ASSERT_EQUAL(1, t4.getRefCount());

        CPPUNIT_ASSERT_EQUAL(2, o4.getRefCount());
        CPPUNIT_ASSERT_EQUAL(3, o3.getRefCount());
        CPPUNIT_ASSERT_EQUAL(4, o2.getRefCount());
        CPPUNIT_ASSERT_EQUAL(5, o1.getRefCount());
    }

    CPPUNIT_ASSERT_EQUAL(1, o1.getRefCount());
    CPPUNIT_ASSERT_EQUAL(1, o2.getRefCount());
    CPPUNIT_ASSERT_EQUAL(1, o3.getRefCount());
    CPPUNIT_ASSERT_EQUAL(1, o4.getRefCount());
}
