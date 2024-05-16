#include "W_OpCode.hh"

// Constructor
W_OpCode::W_OpCode(const std::string& opcode, const std::list<Operand*>& op_operands)
    : OpCode(opcode), format("00"), operands(op_operands) {
    pichex_map = {
        // Initialize with actual values
    };
    code = opcode;
    pichex = pichex_map[opcode];
}

// Accessors
std::string W_OpCode::get_hex() const {
    return pichex;
}

std::string W_OpCode::get_code() const {
    return code;
}

std::string W_OpCode::get_operands() const {
    std::string ops;
    for (const auto& operand : operands) {
        ops += operand->getBinary() + " ";
    }
    return ops;
}

std::string W_OpCode::get_format() const {
    return format;
}
