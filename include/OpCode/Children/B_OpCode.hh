#ifndef B_OPCODE_HH
#define B_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <string>
#include <list>
#include <map>
#include <iostream>

class B_OpCode : public OpCode
{
private:
    std::string format;
    std::map<std::string, std::string> pichex_map;
    std::list<Operand*> operands;
    std::string code;
    std::string pichex;

public:
    B_OpCode(const std::string& opcode, const std::list<Operand*>& op_operands);

    // Accessors
    std::string get_hex() const;
    std::string get_code() const;
    std::string get_operands() const;
    std::string get_format() const;
};

#endif
