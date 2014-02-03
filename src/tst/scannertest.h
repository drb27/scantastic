/*
 * lifetest.h
 *
 *  Created on: Sat Jan 25 13:45:17 EST 2014

 *      Author: drb
 */

#ifndef SCANNERTEST_H_
#define SCANNERTEST_H_

#include "TestCase.h"
#include "TestSuite.h"
#include "TestCaller.h"
#include "TestRunner.h"

#include <extensions/TestFactoryRegistry.h>
#include <ui/text/TextTestRunner.h>
#include <extensions/HelperMacros.h>

using namespace CppUnit;

/** 
 * \brief Unit tests
 *
 * This namespace is used for all unit tests
 */
namespace test {

  /**
   * \brief Provides unit tests for the scanner class.
   * 
   * @see scanner
   */
  class scanner : public TestCase
  {
    
  public:
    
    scanner() {}
    virtual ~scanner() {}
    
    void chomp_whitespace();
    void chomp_whitespace_empty();
    void chomp_to_end();
    void strop_throws_one();
    void singlechar_chomp_one_char();
    void singlechar_chomp_empty();
  
    void scan_empty_input();
    void scan_comma();
  
    /** @cond internal */
    CPPUNIT_TEST_SUITE( scanner );
    CPPUNIT_TEST( chomp_whitespace );
    CPPUNIT_TEST( chomp_whitespace_empty );
    CPPUNIT_TEST( chomp_to_end );
    CPPUNIT_TEST( strop_throws_one );
    CPPUNIT_TEST( singlechar_chomp_one_char );
    CPPUNIT_TEST( singlechar_chomp_empty );
    CPPUNIT_TEST( scan_empty_input );
    CPPUNIT_TEST( scan_comma );
    CPPUNIT_TEST_SUITE_END();
    /** @endcond */
  };
  
}

#endif /* SCANNERTEST_H_ */
