#ifndef CTRL_OPCODE_HH
#define CTRL_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <string>
#include <list>
#include <map>
#include <iostream>

class CTRL_OpCode : public OpCode
{
private:
    std::string format;
    std::map<std::string, std::string> pichex_map;
    std::list<Operand*> operands;
    std::string code;
    std::string pichex;

public:
    CTRL_OpCode(const std::string& opcode, const std::list<Operand*>& op_operands);

    // Accessors
    std::string get_hex() const;
    std::string get_code() const;
    std::string get_operands() const;
    std::string get_format() const;
};

#endif
