#ifndef _PythonWrapperTest_h_
#define _PythonWrapperTest_h_

#include "OPPythonWrapper.h"
#include "OPException.h"
#include "OPPythonException.h"
#include "OPFileException.h"
using namespace OP;

#include <cppunit/extensions/HelperMacros.h>

class PythonWrapperTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PythonWrapperTest );
        CPPUNIT_TEST( testConstructor );
        CPPUNIT_TEST( testCopyConstructor );
        CPPUNIT_TEST( testEquals );
        CPPUNIT_TEST( testRunString );
        CPPUNIT_TEST( testRunFile );
        CPPUNIT_TEST( testEvaluate );
        CPPUNIT_TEST( testReset );
        CPPUNIT_TEST( testGetObject );
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    
    void testConstructor( );
    void testCopyConstructor( );
    void testEquals( );
    void testRunString( );
    void testRunFile( );
    void testEvaluate( );
    void testReset( );
    void testGetObject( );
    void testCreateDelete( );
protected:
    PythonWrapper mPW;
};

#endif
