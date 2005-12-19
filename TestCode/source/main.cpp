#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>
#include "PWSystem.h"

int main(int argc, char* argv[])
{
    pw::System sys;
    sys.loadSwigModule("_TestSwig.dll");
    sys.initialize();

    // Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));

    // Run the tests
    bool wasSucessful = runner.run();

    // Clean up
    sys.finalize();

    return wasSucessful ? 0 : 1;
}
