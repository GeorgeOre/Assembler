#include "Misc_OpCode.hh"
#include <list>
#include <memory>

Misc_OpCode::Misc_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands) {
    this->code = opcode;
    this->operands = operands;
    auto it = misc_map.find(opcode);
    if (it != misc_map.end()) {
        this->pichex = it->second;
    } else {
        // Handle error or assign a default value
    }
}

std::string Misc_OpCode::get_hex() const {
    return pichex;
}

std::string Misc_OpCode::get_code() const {
    return code;
}

std::list<std::shared_ptr<Operand>> Misc_OpCode::get_operands() const {
    return operands;
}

std::string Misc_OpCode::get_format() const {
    return format;
}

bool Misc_OpCode::is_pseudo_op() const {
    return false;
}
