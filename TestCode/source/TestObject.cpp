#include "TestObject.h"
#include "PWBuild.h"
#include "PWHandler.h"
#include "PWExtract.h"
#include "PWInterpreter.h"
#include "PWTuple.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestObject);


void TestObject::setUp()
{
    Interpreter i;
    i.runString(
        "class A:\n"
        "  def __init__(self):\n"
        "    self.meaning = 42\n"
        "  def setMeaning(self, val):\n"
        "    self.meaning = val\n"
        "  def getMeaning(self):\n"
        "    return self.meaning\n"
        "  def __nonzero__(self):\n"
        "    raise TypeError, 'Error'\n");

    i.runString(
        "class B:\n"
        "  def __len__(self):\n"
        "    return 4\n"
        "  def function(self, one, two, three, four=4, five=5):\n"
        "    assert(one == 1)\n"
        "    assert(two == 2)\n"
        "    assert(three == 3)\n"
        "    assert(four == 4)\n"
        "    assert(five == 5)\n"
        "  def noArgs(self): pass\n");

    ClassA = i.getObject("A");
    ClassB = i.getObject("B");
}


void TestObject::tearDown()
{
    ClassA = Object();
    ClassB = Object();
    CPPUNIT_ASSERT(!PyErr_Occurred());
}

void TestObject::testConstructor()
{
    NewReference s1(PyString_FromString("Hello world."));
    NewReference s2(PyString_FromString("Hello world!"));

    Object o1(s1);
    Object o2(s2);

    CPPUNIT_ASSERT_EQUAL(1, o1.getRefCount());
    CPPUNIT_ASSERT_EQUAL(1, o2.getRefCount());
}


void TestObject::testCopyConstructor()
{
    int count = ClassA.getRefCount();
    Object ClassA2(ClassA);
    
    CPPUNIT_ASSERT_EQUAL(count+1, ClassA.getRefCount());
    CPPUNIT_ASSERT(ClassA.borrowReference() == ClassA2.borrowReference());
}


void TestObject::testDefaultConstructor()
{
    int count = Py_None->ob_refcnt;
    Object *obj = new Object;

    CPPUNIT_ASSERT_EQUAL(count+1, obj->getRefCount());
    CPPUNIT_ASSERT_EQUAL(count+1, Py_None->ob_refcnt);

    delete obj;
    CPPUNIT_ASSERT_EQUAL(count, Py_None->ob_refcnt);
    CPPUNIT_ASSERT(! PyErr_Occurred());
}

void TestObject::testLength()
{
    CPPUNIT_ASSERT_EQUAL(-1, ClassA().length());
    CPPUNIT_ASSERT_EQUAL( 4, ClassB().length());
}


static Object makeString(const char *str)
{
    return Object(NewReference(PyString_FromString(str)));
}


void TestObject::testHasAttr()
{
    Object setMeaning = build("setMeaning");
    Object getMeaning = build("getMeaning");
    Object doesNotExist = build("doesNotExist");
    Object function = build("function");

    CPPUNIT_ASSERT(ClassA.hasAttr(setMeaning));
    CPPUNIT_ASSERT(ClassA.hasAttr(getMeaning));
    CPPUNIT_ASSERT(! ClassA.hasAttr(doesNotExist));

    CPPUNIT_ASSERT(ClassB.hasAttr(function));
    CPPUNIT_ASSERT(! ClassA.hasAttr(doesNotExist));
}


void TestObject::testGetSetAttr()
{
    Object attr = build("attr");

    Object a = ClassA();
    Object val = makeString("Some value");

    a.setAttr(attr, val);
    CPPUNIT_ASSERT(a.hasAttr(attr));
    CPPUNIT_ASSERT(a.getAttr(attr).borrowReference() == val.borrowReference());
}


void TestObject::testDelAttr()
{
    Object attr = build("attr");

    Object a = ClassA();
    Object val = makeString("Some value");

    a.setAttr(attr, val);
    CPPUNIT_ASSERT(a.hasAttr(attr));
    CPPUNIT_ASSERT(a.getAttr(attr).borrowReference() == val.borrowReference());

    a.delAttr(attr);
    CPPUNIT_ASSERT(!a.hasAttr(attr));
}

void TestObject::testHasAttrString()
{
    CPPUNIT_ASSERT(ClassA.hasAttr("setMeaning"));
    CPPUNIT_ASSERT(ClassA.hasAttr("getMeaning"));
    CPPUNIT_ASSERT(! ClassA.hasAttr("doesNotExist"));

    CPPUNIT_ASSERT(ClassB.hasAttr("function"));
    CPPUNIT_ASSERT(! ClassA.hasAttr("doesNotExist"));
}


void TestObject::testGetSetAttrString()
{
    Object a = ClassA();
    Object val = makeString("Some value");

    a.setAttr("attr", val);
    CPPUNIT_ASSERT(a.hasAttr("attr"));
    CPPUNIT_ASSERT(a.getAttr("attr").borrowReference() == val.borrowReference());
}


void TestObject::testDelAttrString()
{
    Object a = ClassA();
    Object val = makeString("Some value");

    a.setAttr("attr", val);
    CPPUNIT_ASSERT(a.hasAttr("attr"));
    CPPUNIT_ASSERT(a.getAttr("attr").borrowReference() == val.borrowReference());

    a.delAttr("attr");
    CPPUNIT_ASSERT(!a.hasAttr("attr"));
}

void TestObject::testCallFunction()
{
    Object b = ClassB();
    Object noArgs = b.getAttr("noArgs");
    noArgs();
}

void TestObject::testCallFunctionArgs()
{
    Object i42 = NewReference(PyInt_FromLong(42));
    Object i7  = NewReference(PyInt_FromLong(7));

    Object a = ClassA();
    Object setMeaning = a.getAttr("setMeaning");
    Object getMeaning = a.getAttr("getMeaning");

    CPPUNIT_ASSERT(i42.borrowReference() == getMeaning().borrowReference());
    setMeaning(i7);
    CPPUNIT_ASSERT(i7.borrowReference() == getMeaning().borrowReference());

    setMeaning(Tuple::build(i42));
    CPPUNIT_ASSERT(i42.borrowReference() == getMeaning().borrowReference());

    Object b = ClassB();
    Object function = b.getAttr("function");

    function(Tuple::build(build((long)1), build((long)2), build((long)3)));
    function(Tuple::build(build((long)1), build((long)2), build((long)3), build((long)4)));
}

void TestObject::testCallFunctionNamedArgs()
{
    Object b = ClassB();
    Object function = b.getAttr("function");
    Dict named;
    named["four"] = build((long)4);
    named["five"] = build((long)5);

    function(Tuple::build(build((long)1), build((long)2), build((long)3)), named);

    named.delItem("four");
    function(Tuple::build(build((long)1), build((long)2), build((long)3), build((long)4)), named);
}

void TestObject::testMemberFunction()
{
    Object b = ClassB();
    b.call("noArgs");
}

void TestObject::testMemberFunctionArgs()
{
    Object i42 = Object(NewReference(PyInt_FromLong(42)));
    Object i7  = Object(NewReference(PyInt_FromLong(7)));

    Object a = ClassA();

    CPPUNIT_ASSERT(i42.borrowReference() == a.call("getMeaning").borrowReference());
    a.call("setMeaning", i7);
    CPPUNIT_ASSERT(i7.borrowReference() == a.call("getMeaning").borrowReference());

    a.call("setMeaning", i42);
    CPPUNIT_ASSERT(i42.borrowReference() == a.call("getMeaning").borrowReference());

    Object b = ClassB();

    b.call("function", Tuple::build(build((long)1), build((long)2), build((long)3)));
    b.call("function", Tuple::build(build((long)1), build((long)2), build((long)3), build((long)4)));
}
void TestObject::testMemberFunctionNamedArgs()
{
    Object b = ClassB();
    Dict named;
    named["four"] = build((long)4);
    named["five"] = build((long)5);

    b.call("function", Tuple::build(build((long)1), build((long)2), build((long)3)), named);

    named.delItem("four");
    b.call("function", Tuple::build(build((long)1), build((long)2), build((long)3), build((long)4)), named);
}



void TestObject::testMemberFunctionMissing()
{
    Object b = ClassB();
    b.call("doesNotExist");
}


void TestObject::testMemberFunctionArgsMissing()
{
    Object b = ClassB();
    Object obj;
    b.call("doesNotExist", obj);
}


void TestObject::testMemberFunctionNamedArgsMissing()
{
    Object b = ClassB();
    Object obj;
    Dict d;
    b.call("doesNotExist", obj, d);
}



void TestObject::testCallFunctionException()
{
    Object function = ClassB().getAttr("function");
    function();
}


void TestObject::testCallFunctionArgsException()
{
    Object function = ClassB().getAttr("function");
    function(Object());
}


void TestObject::testCallFunctionNamedArgsException()
{
    Object function = ClassB().getAttr("function");
    function(Object(), Dict());
}


void TestObject::testMemberFunctionException()
{
    Object b = ClassB();
    b.call("function");
}


void TestObject::testMemberFunctionArgsException()
{
    Object b = ClassB();
    b.call("function", Object());
}


void TestObject::testMemberFunctionNamedArgsException()
{
    Object b = ClassB();
    b.call("function", Object());
}

void TestObject::testNot()
{
    Object t = BorrowedReference(Py_True);
    Object f = BorrowedReference(Py_False);
    Object n = BorrowedReference(Py_None);

    CPPUNIT_ASSERT(! !t);
    CPPUNIT_ASSERT(! f);
    CPPUNIT_ASSERT(! n);
}


void TestObject::testTrue()
{
    Object t = BorrowedReference(Py_True);
    Object f = BorrowedReference(Py_False);
    Object n = BorrowedReference(Py_None);

    if (t)
        (void *)(0);
    else
        CPPUNIT_ASSERT_MESSAGE("Expression should have evaluated to true.", false);

        
    if (f)
        CPPUNIT_ASSERT_MESSAGE("Expression should have evaluated to false.", false);
    else
        (void *)(0);

    
    if (n)
        CPPUNIT_ASSERT_MESSAGE("Expression should have evaluated to false.", false);
    else
        (void *)(0);
}

void TestObject::testNotThrows()
{
    Object a = ClassA();

    if (!a)
        (void *)(0);
}


void TestObject::testTrueThrows()
{
    Object a = ClassA();

    if (a)
        (void *)(0);
}



void TestObject::testRefCount()
{
    Object i = build((short)7);
    Object s = build("hello");

    CPPUNIT_ASSERT(i.borrowReference()->ob_refcnt == i.getRefCount());
    CPPUNIT_ASSERT(s.borrowReference()->ob_refcnt == s.getRefCount());
}


void TestObject::testBorrowReference()
{
    PyObject *iobj = PyInt_FromLong(7);
    PyObject *sobj = PyString_FromString("hello");

    Object i = NewReference(iobj);
    Object s = NewReference(sobj);

    int iCount = iobj->ob_refcnt;
    CPPUNIT_ASSERT(i.borrowReference() == iobj);
    CPPUNIT_ASSERT(iCount == i.getRefCount());

    int sCount = sobj->ob_refcnt;
    CPPUNIT_ASSERT(s.borrowReference() == sobj);
    CPPUNIT_ASSERT(sCount == s.getRefCount());
}


void TestObject::testNewReference()
{
    PyObject *iobj = PyInt_FromLong(7);
    PyObject *sobj = PyString_FromString("hello");

    Object i = NewReference(iobj);
    Object s = NewReference(sobj);

    int iCount = iobj->ob_refcnt;
    CPPUNIT_ASSERT(i.newReference() == iobj);
    CPPUNIT_ASSERT(iCount+1 == i.getRefCount());
    Py_DECREF(iobj);

    int sCount = sobj->ob_refcnt;
    CPPUNIT_ASSERT(s.newReference() == sobj);
    CPPUNIT_ASSERT(sCount+1 == s.getRefCount());
    Py_DECREF(sobj);
}
