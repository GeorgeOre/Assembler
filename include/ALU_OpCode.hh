#ifndef ALU_OpCode_HH
#define ALU_OpCode_HH

#include "OpCode.hh"
#include <string>
#include <map>
#include <memory>

class ALU_OpCode : public OpCode
{
private:
    static const std::map<std::string, std::string> pichex_map;
public:
    ALU_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands);

    std::string get_hex() const override;
    std::string get_code() const override;
    std::list<std::shared_ptr<Operand>> get_operands() const override;
    std::string get_format() const override;
    bool is_pseudo_op() const override;
};

#endif
