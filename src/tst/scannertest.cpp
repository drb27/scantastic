#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>

using std::string;
using std::vector;

#include "sassert.h"
#include "scannertest.h"
#include "scan.h"
#include "handler.h"

using namespace CppUnit;

namespace test {

    /** @{ @name Unit Tests*/
  
    /**
     * \brief Tests ::scanner::chomp_whitespace() function
   
     * Tests with streams that start with whitespace, and not
     * @see ::scanner::chomp_whitespace()
     */
  
    void scanner::chomp_whitespace()
    {
	// Create a stringstream and start with whitespace
	const string ts = "Hello";
	std::stringstream ss;
	ss << "  " << ts;
    
	::scanner s(ss);
	s.chomp_whitespace();
	string result;
	getline(ss,result);
	CPPUNIT_ASSERT_MESSAGE("chomp_whitespace() gave unexpected result!",ts==result);      
    
	std::stringstream ss2;
	ss2 << ts;

	::scanner s2(ss2);
	s2.chomp_whitespace();
	string result2;
	getline(ss2,result2);
	CPPUNIT_ASSERT_MESSAGE("chomp_whitespace() screwed the string!", ts==result2);
    }

    void scanner::chomp_whitespace_empty()
    {
	std::stringstream ss;
	::scanner s(ss);
	s.chomp_whitespace();
    }
  
    void scanner::chomp_to_end()
    {
	std::stringstream ss;
	ss << "Hello";
	::scanner s(ss);
	s.chomp_to_end(SYMBOL);
    }

    void scanner::strop_throws_one()
    {
	std::stringstream ss;
	::scanner s(ss);
	CPPUNIT_ASSERT_THROW(s.strop(),assertexception); 
    }

    void scanner::singlechar_chomp_one_char()
    {
	::singlechar_handler h;
	std::stringstream ss;
	ss << "+";
	std::string result = h.chomp_token(ss);
	std::string message = "Chomp failed. Expected:|+|, Received:|" + result + "|";
	CPPUNIT_ASSERT_MESSAGE(message,result=="+");
    }

    void scanner::singlechar_chomp_empty()
    {
	::singlechar_handler h;
	std::stringstream ss;
	CPPUNIT_ASSERT_THROW(h.chomp_token(ss),assertexception); 
    }
  
    void scanner::scan_empty_input()
    {
	std::stringstream ss;
	::scanner s(ss);
	s.scan();
    }

    void scanner::scan_comma()
    {
	std::stringstream ss;
	ss << ",";
	::scanner s(ss);
	s.scan();
    }
  
    /** @} */
  

}
