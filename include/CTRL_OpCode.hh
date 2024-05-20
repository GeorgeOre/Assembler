#ifndef CTRL_OPCODE_HH
#define CTRL_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <list>
#include <memory>
#include <map>

class CTRL_OpCode : public OpCode {
public:
    CTRL_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands);
    std::string get_hex() const override;
    std::string get_code() const override;
    std::list<std::shared_ptr<Operand>> get_operands() const override;
    std::string get_format() const override;
    bool is_pseudo_op() const override;

private:
    std::map<std::string, std::string> ctrl_map = {
        {"CALL", "000100"},
        {"GOTO", "000101"}
        // Add other CTRL opcodes and their corresponding values
    };
};

#endif
