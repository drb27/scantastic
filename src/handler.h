
#ifndef HANDLER_H_
#define HANDLER_H_

class handler
{
 public:
  virtual ~handler();

 protected:
  handler();

 public:
  /** @{ @name Interface Definition */

  /**
   * Removes one complete token from the input stream. The argorithm to do this varies
   * on the type of token, so classes that derive from handler should provide their own
   * implementation. 
   * @param stream the input stream from which to read the token representation.
   * @returns a string containing the token representation
   */
  virtual std::string chomp_token(std::istream& stream) const=0;

  /** @} */

};

class singlechar_handler : public handler
{
public:
    singlechar_handler();
    virtual ~singlechar_handler();

    virtual std::string chomp_token(std::istream& stream) const;
};

class symbol_handler : public handler
{
 public:
  symbol_handler();
  virtual ~symbol_handler();

  virtual std::string chomp_token(std::istream& stream) const;
};

#endif
