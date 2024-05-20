#ifndef B_OPCODE_HH
#define B_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <list>
#include <memory>
#include <map>

class B_OpCode : public OpCode {
public:
    B_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands);
    std::string get_hex() const override;
    std::string get_code() const override;
    std::list<std::shared_ptr<Operand>> get_operands() const override;
    std::string get_format() const override;
    bool is_pseudo_op() const override;

private:
    std::map<std::string, std::string> b_map = {
        {"BCF", "00"}, {"BSF", "01"},
		{"BTFSC", "10"}, {"BTFSS", "11"}
    };
};

#endif

