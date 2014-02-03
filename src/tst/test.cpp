#include "TestCase.h"
#include "TestSuite.h"
#include "TestCaller.h"
#include "TestRunner.h"

#include <extensions/TestFactoryRegistry.h>
#include <ui/text/TextTestRunner.h>
#include <extensions/HelperMacros.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;

#include "sassert.h"
#include "scannertest.h"

/** \cond internal */
CPPUNIT_TEST_SUITE_REGISTRATION(test::scanner);
/** \endcond */

/**
 * Runs the unit test suites */
int main(int argc, char** argv)
{
  try
    {
      using CppUnit::Test;

      Test* test = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
      CppUnit::TextTestRunner runner;
      runner.addTest(test);
      runner.run();
      return 0;
    }
  catch (assertexception& e)
    {
      std::cerr << e.what() << std::endl;
      std::abort();
    }
}
