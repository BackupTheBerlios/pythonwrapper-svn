#include "TestList.h"
#include "PWHandler.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestList);

void TestList::setUp()
{
    mObjList = new PyObject *[8];
    mObjList[0] = PyInt_FromLong(1);
    mObjList[1] = PyInt_FromLong(2);
    mObjList[2] = PyInt_FromLong(3);
    mObjList[3] = PyInt_FromLong(4);
    mObjList[4] = PyInt_FromLong(5);
    mObjList[5] = PyString_FromString("six");
    mObjList[6] = PyString_FromString("seven");
    mObjList[7] = PyString_FromString("eight");

    mList = new List();

    mList->append(NewReference(mObjList[0]));
    mList->append(NewReference(mObjList[1]));
    mList->append(NewReference(mObjList[2]));
    mList->append(NewReference(mObjList[3]));
    mList->append(NewReference(mObjList[4]));
    mList->append(NewReference(mObjList[5]));
    mList->append(NewReference(mObjList[6]));
    mList->append(NewReference(mObjList[7]));
}


void TestList::tearDown()
{
    delete [] mObjList;
    delete mList;
}

void TestList::testLength()
{
    CPPUNIT_ASSERT_EQUAL(8, mList->length());
    
    mList->delItem(0);
    CPPUNIT_ASSERT_EQUAL(7, mList->length());
}



void TestList::testGetItem()
{
    CPPUNIT_ASSERT(mObjList[0] == mList->getItem(0).borrowReference());
    CPPUNIT_ASSERT(mObjList[1] == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(mObjList[2] == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(mObjList[3] == mList->getItem(3).borrowReference());
    CPPUNIT_ASSERT(mObjList[4] == mList->getItem(4).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(5).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(6).borrowReference());
    CPPUNIT_ASSERT(mObjList[7] == mList->getItem(7).borrowReference());
}


void TestList::testSetItem()
{
    mList->setItem(0, BorrowedReference(mObjList[7]));
    mList->setItem(1, BorrowedReference(mObjList[6]));
    mList->setItem(2, BorrowedReference(mObjList[5]));
    mList->setItem(3, BorrowedReference(mObjList[4]));
    mList->setItem(4, BorrowedReference(mObjList[3]));
    mList->setItem(5, BorrowedReference(mObjList[2]));
    mList->setItem(6, BorrowedReference(mObjList[1]));
    mList->setItem(7, BorrowedReference(mObjList[0]));
    
    CPPUNIT_ASSERT(mObjList[7] == mList->getItem(0).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(mObjList[4] == mList->getItem(3).borrowReference());
    CPPUNIT_ASSERT(mObjList[3] == mList->getItem(4).borrowReference());
    CPPUNIT_ASSERT(mObjList[2] == mList->getItem(5).borrowReference());
    CPPUNIT_ASSERT(mObjList[1] == mList->getItem(6).borrowReference());
    CPPUNIT_ASSERT(mObjList[0] == mList->getItem(7).borrowReference());
}

void TestList::testDelItem()
{
    mList->delItem(0);
    CPPUNIT_ASSERT_EQUAL(7, mList->length());

    mList->delItem(6);
    CPPUNIT_ASSERT_EQUAL(6, mList->length());
    
    CPPUNIT_ASSERT(mObjList[1] == mList->getItem(0).borrowReference());
    CPPUNIT_ASSERT(mObjList[2] == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(mObjList[3] == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(mObjList[4] == mList->getItem(3).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(4).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(5).borrowReference());

    mList->delItem(3);
    CPPUNIT_ASSERT_EQUAL(5, mList->length());
    
    CPPUNIT_ASSERT(mObjList[1] == mList->getItem(0).borrowReference());
    CPPUNIT_ASSERT(mObjList[2] == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(mObjList[3] == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(3).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(4).borrowReference());
}


void TestList::testGetSlice()
{
    mList->delSlice(1, 3);

    CPPUNIT_ASSERT(mObjList[0] == mList->getItem(0).borrowReference());
    CPPUNIT_ASSERT(mObjList[3] == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(mObjList[4] == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(3).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(4).borrowReference());
    CPPUNIT_ASSERT(mObjList[7] == mList->getItem(5).borrowReference());
}


void TestList::testSetSlice()
{
    PyObject *o9  = PyInt_FromLong(9),
             *o10 = PyInt_FromLong(10),
             *o11 = PyInt_FromLong(11);

    List l;
    l.append(NewReference(o9));
    l.append(NewReference(o10));
    l.append(NewReference(o11));

    mList->setSlice(1, 3, l);

    CPPUNIT_ASSERT(mObjList[0] == mList->getItem(0).borrowReference());

    CPPUNIT_ASSERT(o9 == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(o10 == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(o11 == mList->getItem(3).borrowReference());

    CPPUNIT_ASSERT(mObjList[3] == mList->getItem(4).borrowReference());
    CPPUNIT_ASSERT(mObjList[4] == mList->getItem(5).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(6).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(7).borrowReference());
    CPPUNIT_ASSERT(mObjList[7] == mList->getItem(8).borrowReference());
}


void TestList::testDelSlice()
{
    mList->delSlice(1, 4);

    CPPUNIT_ASSERT(mObjList[0] == mList->getItem(0).borrowReference());
    CPPUNIT_ASSERT(mObjList[4] == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(3).borrowReference());
    CPPUNIT_ASSERT(mObjList[7] == mList->getItem(4).borrowReference());
}

void TestList::testAppend()
{
    PyObject *o8  = PyInt_FromLong(9),
             *o9  = PyInt_FromLong(10),
             *o10 = PyInt_FromLong(11);

    mList->append(NewReference(o8));
    mList->append(NewReference(o9));
    mList->append(NewReference(o10));

    CPPUNIT_ASSERT(mObjList[0] == mList->getItem(0).borrowReference());
    CPPUNIT_ASSERT(mObjList[1] == mList->getItem(1).borrowReference());
    CPPUNIT_ASSERT(mObjList[2] == mList->getItem(2).borrowReference());
    CPPUNIT_ASSERT(mObjList[3] == mList->getItem(3).borrowReference());
    CPPUNIT_ASSERT(mObjList[4] == mList->getItem(4).borrowReference());
    CPPUNIT_ASSERT(mObjList[5] == mList->getItem(5).borrowReference());
    CPPUNIT_ASSERT(mObjList[6] == mList->getItem(6).borrowReference());
    CPPUNIT_ASSERT(mObjList[7] == mList->getItem(7).borrowReference());
    CPPUNIT_ASSERT(o8  == mList->getItem(8).borrowReference());
    CPPUNIT_ASSERT(o9  == mList->getItem(9).borrowReference());
    CPPUNIT_ASSERT(o10 == mList->getItem(10).borrowReference());
}


void TestList::testOperatorGet()
{
    CPPUNIT_ASSERT((*mList)[0].borrowReference() == mObjList[0]);
    CPPUNIT_ASSERT((*mList)[1].borrowReference() == mObjList[1]);
    CPPUNIT_ASSERT((*mList)[2].borrowReference() == mObjList[2]);
    CPPUNIT_ASSERT((*mList)[3].borrowReference() == mObjList[3]);
    CPPUNIT_ASSERT((*mList)[4].borrowReference() == mObjList[4]);
    CPPUNIT_ASSERT((*mList)[5].borrowReference() == mObjList[5]);
    CPPUNIT_ASSERT((*mList)[6].borrowReference() == mObjList[6]);
    CPPUNIT_ASSERT((*mList)[7].borrowReference() == mObjList[7]);
}

void TestList::testOperatorSet()
{
    (*mList)[0] = BorrowedReference(mObjList[7]);
    (*mList)[1] = BorrowedReference(mObjList[6]);
    (*mList)[2] = BorrowedReference(mObjList[5]);
    (*mList)[3] = BorrowedReference(mObjList[4]);
    (*mList)[4] = BorrowedReference(mObjList[3]);
    (*mList)[5] = BorrowedReference(mObjList[2]);
    (*mList)[6] = BorrowedReference(mObjList[1]);
    (*mList)[7] = BorrowedReference(mObjList[0]);

    CPPUNIT_ASSERT((*mList)[0].borrowReference() == mObjList[7]);
    CPPUNIT_ASSERT((*mList)[1].borrowReference() == mObjList[6]);
    CPPUNIT_ASSERT((*mList)[2].borrowReference() == mObjList[5]);
    CPPUNIT_ASSERT((*mList)[3].borrowReference() == mObjList[4]);
    CPPUNIT_ASSERT((*mList)[4].borrowReference() == mObjList[3]);
    CPPUNIT_ASSERT((*mList)[5].borrowReference() == mObjList[2]);
    CPPUNIT_ASSERT((*mList)[6].borrowReference() == mObjList[1]);
    CPPUNIT_ASSERT((*mList)[7].borrowReference() == mObjList[0]);
}

void TestList::testReverse()
{
    mList->reverse();

    CPPUNIT_ASSERT((*mList)[0].borrowReference() == mObjList[7]);
    CPPUNIT_ASSERT((*mList)[1].borrowReference() == mObjList[6]);
    CPPUNIT_ASSERT((*mList)[2].borrowReference() == mObjList[5]);
    CPPUNIT_ASSERT((*mList)[3].borrowReference() == mObjList[4]);
    CPPUNIT_ASSERT((*mList)[4].borrowReference() == mObjList[3]);
    CPPUNIT_ASSERT((*mList)[5].borrowReference() == mObjList[2]);
    CPPUNIT_ASSERT((*mList)[6].borrowReference() == mObjList[1]);
    CPPUNIT_ASSERT((*mList)[7].borrowReference() == mObjList[0]);
}


void TestList::testSort()
{
    mList->sort();

    CPPUNIT_ASSERT((*mList)[0].borrowReference() == mObjList[0]);
    CPPUNIT_ASSERT((*mList)[1].borrowReference() == mObjList[1]);
    CPPUNIT_ASSERT((*mList)[2].borrowReference() == mObjList[2]);
    CPPUNIT_ASSERT((*mList)[3].borrowReference() == mObjList[3]);
    CPPUNIT_ASSERT((*mList)[4].borrowReference() == mObjList[4]);
    CPPUNIT_ASSERT((*mList)[7].borrowReference() == mObjList[5]);
    CPPUNIT_ASSERT((*mList)[6].borrowReference() == mObjList[6]);
    CPPUNIT_ASSERT((*mList)[5].borrowReference() == mObjList[7]);
}
