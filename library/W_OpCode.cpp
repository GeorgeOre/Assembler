#include "W_OpCode.hh"
#include <list>
#include <memory>

W_OpCode::W_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands) {
    this->code = opcode;
    this->operands = operands;
    auto it = w_map.find(opcode);
    if (it != w_map.end()) {
        this->pichex = it->second;
    } else {
        // Handle error or assign a default value
    }
}

std::string W_OpCode::get_hex() const {
    return pichex;
}

std::string W_OpCode::get_code() const {
    return code;
}

std::list<std::shared_ptr<Operand>> W_OpCode::get_operands() const {
    return operands;
}

std::string W_OpCode::get_format() const {
    return format;
}

bool W_OpCode::is_pseudo_op() const {
    return false;
}
