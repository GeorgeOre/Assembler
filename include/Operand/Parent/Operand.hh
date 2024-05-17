#ifndef OPERAND_HH
#define OPERAND_HH

#include <string>
#include <iostream>
#include "OpCode.hh"

class OpCode; // Forward declaration

class Operand {
private:
    OpCode *opcode;  // Pointer to associated OpCode
    uint64_t size;   // Size of the operand in bits
    std::string raw;      // Raw string that was parsed
    std::string binary;   // Binary value in string format

public:
    // Constructors
    Operand(OpCode *opcode, const std::string &raw);

    // Destructor
    virtual ~Operand();

    // Accessors
    uint64_t getSize() const;
    const std::string &getRaw() const;
    const std::string &getBinary() const;

    // Modifiers
    void setSize(uint64_t size);
    void setRaw(const std::string &raw);
    void setBinary(const std::string &binary);

    // Inheritance
    virtual void identifyChild() const;

    // Print value
    virtual void printValue() const;
};

#endif
