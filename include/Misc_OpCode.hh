#ifndef MISC_OPCODE_HH
#define MISC_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <list>
#include <memory>
#include <map>

class Misc_OpCode : public OpCode {
public:
    Misc_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands);
    std::string get_hex() const override;
    std::string get_code() const override;
    std::list<std::shared_ptr<Operand>> get_operands() const override;
    std::string get_format() const override;
    bool is_pseudo_op() const override;

private:
    std::map<std::string, std::string> misc_map = {
        {"NOP", "0000000"}, {"RETURN", "0001000"},
		{"RETFIE", "0001001"}, {"OPTION", "1100010"},
		{"SLEEP", "1100011"}, {"CLRWDT", "1100100"},
		{"TRIS", "11001"}
        // Add other Misc opcodes and their corresponding values
    };
};

#endif


