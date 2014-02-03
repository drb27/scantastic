
#ifndef SCAN_H_
#define SCAN_H_

/** 
 * token_t represents the type of the token 
 */
typedef enum{

    SYMBOL,
    BINARY_OPERATOR,
    STRING_OPEN,
    STRING_CLOSE,
    STRING_LITERAL,
    COMMA,
    NUMBER_LITERAL,
    TUPLE_OPEN,
    TUPLE_CLOSE

} token_t;

/** 
 * Represents a token and a value 
 */
typedef struct
{
    token_t token; /** The token type */
    string _value;   /** The value of the token */
} tvpair_t;

/**
 * stack_t is the token stack for already scanned tokens and values 
 */
typedef vector<tvpair_t> stack_t;

/**
 * Maps initial characters to the token type they represent
 */
typedef std::map<char,token_t> charmap_t;

namespace test {
    class scanner;
}

class handler;

class scanner
{
    friend test::scanner;
public:
    scanner(std::istream& str);
    virtual ~scanner();

    void strop(void) const;
  
protected:
    virtual string chomp_to_end(token_t tokenType);
    virtual void chomp_whitespace(void);
    virtual void scan(void);

    stack_t stack;
    std::istream& stream;
    std::map<token_t,handler*> handlers;
    charmap_t charmap;
};

#endif
