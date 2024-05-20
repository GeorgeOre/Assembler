#include "CTRL_OpCode.hh"
#include <list>
#include <memory>

CTRL_OpCode::CTRL_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands) {
    this->code = opcode;
    this->operands = operands;
    auto it = ctrl_map.find(opcode);
    if (it != ctrl_map.end()) {
        this->pichex = it->second;
    } else {
        // Handle error or assign a default value
    }
}

std::string CTRL_OpCode::get_hex() const {
    return pichex;
}

std::string CTRL_OpCode::get_code() const {
    return code;
}

std::list<std::shared_ptr<Operand>> CTRL_OpCode::get_operands() const {
    return operands;
}

std::string CTRL_OpCode::get_format() const {
    return format;
}

bool CTRL_OpCode::is_pseudo_op() const {
    return false;
}
