#include "B_OpCode.hh"
#include <list>
#include <memory>

B_OpCode::B_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands) {
    this->code = opcode;
    this->operands = operands;
    auto it = b_map.find(opcode);
    if (it != b_map.end()) {
        this->pichex = it->second;
    } else {
        // Handle error or assign a default value
    }
}

std::string B_OpCode::get_hex() const {
    return pichex;
}

std::string B_OpCode::get_code() const {
    return code;
}

std::list<std::shared_ptr<Operand>> B_OpCode::get_operands() const {
    return operands;
}

std::string B_OpCode::get_format() const {
    return format;
}

bool B_OpCode::is_pseudo_op() const {
    return false;
}
