#include "ALU_OpCode.hh"

// Constructor
ALU_OpCode::ALU_OpCode(const std::string& opcode, const std::list<Operand*>& op_operands)
    : OpCode(opcode), format("00"), operands(op_operands) {
    pichex_map = {
        {"MOVWF", "00001"}, {"CLR", "0001"},
        {"SUBWF", "0010"}, {"DECF", "0011"},
        {"IORWF", "0100"}, {"ANDWF", "0101"},
        {"XORWF", "0110"}, {"ADDWF", "0111"},
        {"MOVF", "1000"}, {"COMF", "1001"},
        {"INCF", "1010"}, {"DECFSZ", "1011"},
        {"RRF", "1100"}, {"RLF", "1101"},
        {"SWAPF", "1110"}, {"INFSZ", "1111"}
    };
    code = opcode;
    pichex = pichex_map[opcode];
}

// Accessors
std::string ALU_OpCode::get_hex() const {
    return pichex;
}

std::string ALU_OpCode::get_code() const {
    return code;
}

std::string ALU_OpCode::get_operands() const {
    std::string ops;
    for (const auto& operand : operands) {
        ops += operand->getBinary() + " ";
    }
    return ops;
}

std::string ALU_OpCode::get_format() const {
    return format;
}
