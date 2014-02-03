#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include "sassert.h"

using std::string;
using std::vector;

#include "handler.h"
#include "scan.h"

scanner::scanner(std::istream& str ) : stream(str)
{
    // Initialise the handlers
    handlers[SYMBOL] = new symbol_handler();
    handlers[COMMA] = new singlechar_handler();

    // Initialise the character map
    charmap[','] = COMMA;
}

/**
 * Allows a unit test for assert. This will never be called in production code.
 */
void scanner::strop(void) const
{
    assert(false);
}

/** 
 * Removes all characters from the head of the current input stream, until the end of the
 * given token type is encountered.  @param tokenType the type of the token to read to the
 * end of @returns all chomped characters
 */
string scanner::chomp_to_end(token_t tokenType)
{
    // Check that the handler exists, and we haven't got an empty string
    assert(handlers.find(tokenType)!=handlers.end()); // LCOV_EXCL_LINE 
    assert(stream.peek()!=EOF);	                      // LCOV_EXCL_LINE
    
    // Delegate to the handler
    return handlers[tokenType]->chomp_token(stream);
}

/**
 * Removes and discards all whitespace at the head of the current input stream.
 */
void scanner::chomp_whitespace(void)
{
    char c;
    while (stream.peek()==' ')
	stream.read(&c,1);

}

/** 
 * Scans the input to produce q sequence of (token,value) pairs. 
 * The input is read from the stream given to the constructor, and the output is formed
 * in the internal (token,value) stack. 
 *
 * Scanning continues until either the end of the input stream is reached, or an 
 * error occurs (in which case the TBD exception is thrown
 */
void scanner::scan(void)
{

    // Clear the stack for a clean pass
    stack.clear();
    
    // Loop through the input
    char head;
    while (EOF!=(head=stream.peek())) 
    {
	static const auto iter = charmap.find(head);
	if ( charmap.end() != iter )
	{
	    token_t token = (*iter).second; // Retrieve the token
	    assert( handlers.find(token)!=handlers.end()); // LCOV_EXCL_LINE
	    handler* hndlr = handlers[token];   // Retrieve the handler

	    // Get the handler to pull the token text from the stream
	    tvpair_t pair = { .token = token, ._value = hndlr->chomp_token(stream) };

	    assert(pair.token == token);      // LCOV_EXCL_LINE
	    assert(pair._value.length() > 0); // LCOV_EXCL_LINE

	    // Pop the token and the text onto the stack
	    stack.push_back(pair);
	}
	else
	{
	    // Syntax error - unexpected character at head of input stream
	    /** @todo Create an exception for malformed input */
	    throw 0;
	}
    }
    
}


/**
 * Standard virtual destructor.
 */
scanner::~scanner()
{

}

