#ifndef _PythonWrapperTest_h_
#define _PythonWrapperTest_h_

#include "OPPythonWrapper.h"
using namespace OP;

class PythonWrapperTest
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

  CPPUNIT_TEST_EXCEPTION( testGetObjectE, Exception );
  CPPUNIT_TEST_EXCEPTION( testEvaluatePE, PythonException );
  CPPUNIT_TEST_EXCEPTION( testRunStringPE, PythonException );
  CPPUNIT_TEST_EXCEPTION( testRunFilePE, PythonException );
  CPPUNIT_TEST_EXCEPTION( testRunFileFE, FileException );
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

  void testGetObjectE( );
  void testEvaluatePE( );
  void testRunStringPE( );
  void testRunFilePE( );
  void testRunFileFE( );
};

#endif
