#include "PythonWrapperTest.h"

#include <boost/python.hpp>
#include <boost/python/object.hpp>
using namespace boost::python;

void PythonWrapperTest::setUp()
{
    mPW.runString(
        "iVar = 1\n"
        "sVar = 'string'\n"
        );
}


void PythonWrapperTest::tearDown()
{
}

#include <iostream>


void PythonWrapperTest::testConstructor( )
{
    PythonWrapper pw;

    // this should throw if the constructor made a clean object
    // fail otherwise, since mPW contains iVar
    CPPUNIT_ASSERT_THROW( pw.evaluate( "iVar" ), PythonException );
}

void PythonWrapperTest::testCopyConstructor( )
{
    PythonWrapper pw( mPW );

    int iVar = extract<int>(pw.getObject( "iVar" ));
    std::string sVar = extract<std::string>(pw.evaluate( "sVar" ));
    
    CPPUNIT_ASSERT_EQUAL( iVar, 1 );
    CPPUNIT_ASSERT( sVar == "string" );
}

void PythonWrapperTest::testEquals( )
{
    PythonWrapper pw = mPW;
    int iVar = extract<int>(pw.getObject( "iVar" ));
    std::string sVar = extract<std::string>(pw.evaluate("sVar"));
    
    CPPUNIT_ASSERT_EQUAL( iVar, 1 );
    CPPUNIT_ASSERT( sVar == "string" );
}

void PythonWrapperTest::testRunString( )
{
    PythonWrapper pw;

    pw.runString(
        "def funct( ):\n"
        "    return 7"
        );
    pw.runString( "a = 1\n" );
    pw.runString( "b = 2" );
    pw.runString( "c = a + b + funct()\n" );

    int c = extract<int>(pw.evaluate("c"));

    CPPUNIT_ASSERT_EQUAL( c, 10 );
    CPPUNIT_ASSERT_THROW( pw.runString("bad_expression"), PythonException );
}

void PythonWrapperTest::testRunFile( )
{
    PythonWrapper pw;
    pw.runFile( "test.py" );
    CPPUNIT_ASSERT_THROW( pw.runFile("NotAFile"), FileException );
    CPPUNIT_ASSERT_THROW( pw.runFile("Errors.py"), PythonException );
}


void PythonWrapperTest::testEvaluate( )
{
    PythonWrapper pw;
    pw.runString(
        "def f( ):    \n"
        "    return 42  "
        );

    int iR = extract<int>(pw.evaluate("2**3 + f( )"));
    std::string sR = extract<std::string>(pw.evaluate("str( f() )"));
    CPPUNIT_ASSERT_EQUAL( iR, 50 );
    CPPUNIT_ASSERT( sR == "42" );
    CPPUNIT_ASSERT_THROW( mPW.evaluate( "badExpression" ), PythonException );
}


void PythonWrapperTest::testReset( )
{
    PythonWrapper pw;

    pw.runString( "test = True" );
    pw.reset( );

    CPPUNIT_ASSERT_THROW( pw.evaluate( "test" ), PythonException );
    CPPUNIT_ASSERT_THROW( pw.getObject( "test" ), PythonException );
}

void PythonWrapperTest::testGetObject( )
{
    int iVar = extract<int>(mPW.getObject( "iVar" ));
    std::string sVar = extract<std::string>(mPW.getObject("sVar"));

    CPPUNIT_ASSERT_EQUAL( iVar, 1 );
    CPPUNIT_ASSERT( sVar == "string" );
    CPPUNIT_ASSERT_THROW( mPW.getObject( "some_non_object" ), PythonException );
}
