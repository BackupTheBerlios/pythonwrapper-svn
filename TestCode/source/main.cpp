#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <cppunit/extensions/HelperMacros.h>

#include "PythonWrapperTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PythonWrapperTest );

#include <iostream>

int main(int argc, char* argv[])
{
    // create runner
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    // add tests
    runner.addTest( registry.makeTest() );

    // run tests
    bool wasSuccessful = runner.run( "", false );

    // return results
    return wasSuccessful;
}

