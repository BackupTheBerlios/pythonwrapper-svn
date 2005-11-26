#include "TestDict.h"
#include "PWHandler.h"
#include "PWList.h"
#include "PythonWrapper.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestDict);

void TestDict::testStrings()
{
    PyObject *value1 = PyString_FromString("value1"),
             *value2 = PyString_FromString("value2"),
             *value3 = PyString_FromString("value3");

    int rc1 = value1->ob_refcnt,
        rc2 = value1->ob_refcnt,
        rc3 = value1->ob_refcnt;

    Dict d;
    d.setItem("key1", BorrowedReference(value1));
    d.setItem("key2", BorrowedReference(value2));
    d.setItem("key3", BorrowedReference(value3));

    CPPUNIT_ASSERT(d.getItem("key1").borrowReference() == value1);
    CPPUNIT_ASSERT(d.getItem("key2").borrowReference() == value2);
    CPPUNIT_ASSERT(d.getItem("key3").borrowReference() == value3);

    CPPUNIT_ASSERT_EQUAL(rc1+1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc2+1, value2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc3+1, value3->ob_refcnt);

    d.delItem("key1");
    try
    {
        d.getItem("key1");
        CPPUNIT_FAIL("Exception not thrown!");
    }
    catch (...) {}

    CPPUNIT_ASSERT_EQUAL(rc1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc2+1, value2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc3+1, value3->ob_refcnt);

    d.~Dict();
    
    CPPUNIT_ASSERT_EQUAL(rc1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc2, value2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc3, value3->ob_refcnt);

    Py_DECREF(value1);
    Py_DECREF(value2);
    Py_DECREF(value3);
}


void TestDict::testObjects()
{
    PyObject *value1 = PyString_FromString("value1"),
             *value2 = PyString_FromString("value2"),
             *value3 = PyString_FromString("value3");

    PyObject *key1 = PyString_FromString("key1"),
             *key2 = PyString_FromString("key2"),
             *key3 = PyString_FromString("key3");

    int rc1 = value1->ob_refcnt,
        rc2 = value1->ob_refcnt,
        rc3 = value1->ob_refcnt,
        kc1 = key1->ob_refcnt,
        kc2 = key2->ob_refcnt,
        kc3 = key3->ob_refcnt;

    Dict d;
    d.setItem(BorrowedReference(key1), BorrowedReference(value1));
    d.setItem(BorrowedReference(key2), BorrowedReference(value2));
    d.setItem(BorrowedReference(key3), BorrowedReference(value3));

    CPPUNIT_ASSERT(d.getItem("key1").borrowReference() == value1);
    CPPUNIT_ASSERT(d.getItem("key2").borrowReference() == value2);
    CPPUNIT_ASSERT(d.getItem("key3").borrowReference() == value3);

    CPPUNIT_ASSERT_EQUAL(rc1+1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc2+1, value2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc3+1, value3->ob_refcnt);
    
    CPPUNIT_ASSERT_EQUAL(kc1+1, key1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(kc2+1, key2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(kc3+1, key3->ob_refcnt);

    d.delItem(BorrowedReference(key1));
    try
    {
        d.getItem(BorrowedReference(key1));
        CPPUNIT_FAIL("Exception not thrown!");
    }
    catch (...) {}

    CPPUNIT_ASSERT_EQUAL(rc1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc2+1, value2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc3+1, value3->ob_refcnt);
    
    CPPUNIT_ASSERT_EQUAL(kc1, key1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(kc2+1, key2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(kc3+1, key3->ob_refcnt);

    d.~Dict();
    
    CPPUNIT_ASSERT_EQUAL(rc1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc2, value2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(rc3, value3->ob_refcnt);
    
    CPPUNIT_ASSERT_EQUAL(kc1, key1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(kc2, key2->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(kc3, key3->ob_refcnt);

    Py_DECREF(value1);
    Py_DECREF(value2);
    Py_DECREF(value3);
}


void TestDict::testStringGetThrow()
{
    mDict->getItem("test");
}


void TestDict::testGetThrow()
{
    Object str = build("test");
    mDict->getItem(str);
}


void TestDict::testOperatorGetNull()
{
    Object test = build("test");

    CPPUNIT_ASSERT((*mDict)["test"].borrowReference() == Py_None);
    CPPUNIT_ASSERT(!mDict->contains(test));

    Object n = build((short)7);

    CPPUNIT_ASSERT((*mDict)[n].borrowReference() == Py_None);
    CPPUNIT_ASSERT(!mDict->contains(n));
}


void TestDict::testOperatorSetNull()
{
    Object test = build("test2");

    CPPUNIT_ASSERT((*mDict)["test2"].borrowReference() == Py_None);
    (*mDict)["test2"] = BorrowedReference(Py_False);
    CPPUNIT_ASSERT(mDict->contains(test));
    CPPUNIT_ASSERT((*mDict)["test2"].borrowReference() == Py_False);

    Object n = build((short)7);

    CPPUNIT_ASSERT((*mDict)[n].borrowReference() == Py_None);
    (*mDict)[n] = BorrowedReference(Py_False);
    CPPUNIT_ASSERT(mDict->contains(n));
    CPPUNIT_ASSERT((*mDict)[n].borrowReference() == Py_False);

    (*mDict)["test"] = build((short)7);
    CPPUNIT_ASSERT((*mDict).contains(build("test")));
    CPPUNIT_ASSERT_EQUAL((short)7, extract<short>((*mDict).getItem(build("test"))));
    CPPUNIT_ASSERT_EQUAL((short)7, extract<short>((*mDict).getItem("test")));
}


void TestDict::testStringDelThrow()
{
    mDict->delItem("test");
}


void TestDict::testDelThrow()
{
    Object str = build("test");
    mDict->delItem(str);
}

void TestDict::setUp()
{
    mDict = new Dict();
    mDict->setItem("key1", NewReference(PyString_FromString("value1")));
    mDict->setItem("key2", NewReference(PyString_FromString("value2")));
    mDict->setItem("key3", NewReference(PyString_FromString("value3")));
}

void TestDict::tearDown()
{
    delete mDict;
}


void TestDict::testLength()
{
    CPPUNIT_ASSERT_EQUAL(3, mDict->length());

    mDict->delItem("key1");
    CPPUNIT_ASSERT_EQUAL(2, mDict->length());

    mDict->delItem("key2");
    CPPUNIT_ASSERT_EQUAL(1, mDict->length());

    mDict->delItem("key3");
    CPPUNIT_ASSERT_EQUAL(0, mDict->length());
}


void TestDict::testItems()
{
    List l = mDict->items();

    CPPUNIT_ASSERT_EQUAL(3, l.length());
}


void TestDict::testKeys()
{
    List l = mDict->keys();

    CPPUNIT_ASSERT_EQUAL(3, l.length());
    CPPUNIT_ASSERT(l.contains(build("key1")));
    CPPUNIT_ASSERT(l.contains(build("key2")));
    CPPUNIT_ASSERT(l.contains(build("key3")));
}


void TestDict::testValues()
{
    List l = mDict->values();

    CPPUNIT_ASSERT_EQUAL(3, l.length());
    CPPUNIT_ASSERT(l.contains(build("value1")));
    CPPUNIT_ASSERT(l.contains(build("value2")));
    CPPUNIT_ASSERT(l.contains(build("value3")));
}


void TestDict::testContains()
{
    CPPUNIT_ASSERT(mDict->contains(build("key1")));
    CPPUNIT_ASSERT(mDict->contains(build("key2")));
    CPPUNIT_ASSERT(mDict->contains(build("key3")));
}



void TestDict::testOperatorGet()
{
    PyObject *value = PyString_FromString("value1");
    int refcnt = value->ob_refcnt;

    Dict d;
    d.setItem("key1", BorrowedReference(value));
    
    // after this, refcnt holds current reference count
    CPPUNIT_ASSERT_EQUAL(++refcnt, value->ob_refcnt);

    Object obj = d["key1"];

    // after this, refcnt holds current reference count
    CPPUNIT_ASSERT_EQUAL(++refcnt, value->ob_refcnt);
    
    Py_DECREF(value);
}


void TestDict::testOperatorSet()
{
    PyObject *value1 = PyString_FromString("value1"),
             *value2 = PyString_FromString("value2");
    int refcnt1 = value1->ob_refcnt,
        refcnt2 = value2->ob_refcnt;

    Dict d;
    d.setItem("key1", BorrowedReference(value1));
    
    CPPUNIT_ASSERT_EQUAL(refcnt1+1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(refcnt2, value2->ob_refcnt);

    d["key1"] = Object(BorrowedReference(value2));

    CPPUNIT_ASSERT(d["key1"].borrowReference() == value2);
    CPPUNIT_ASSERT(d.getItem("key1").borrowReference() == value2);
    CPPUNIT_ASSERT_EQUAL(refcnt1, value1->ob_refcnt);
    CPPUNIT_ASSERT_EQUAL(refcnt2+1, value2->ob_refcnt);

    Py_DECREF(value1);
    Py_DECREF(value2);
}
