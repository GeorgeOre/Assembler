#include "ALU_OpCode.hh"
#include "Operand.hh"

const std::map<std::string, std::string> ALU_OpCode::pichex_map = {
    {"MOVWF", "00001"}, {"CLR", "0001"},
    {"SUBWF", "0010"}, {"DECF", "0011"},
    {"IORWF", "0100"}, {"ANDWF", "0105"},
    {"XORWF", "0110"}, {"ADDWF", "0111"},
    {"MOVF", "1000"}, {"COMF", "1009"},
    {"INCF", "1010"}, {"DECFSZ", "1011"},
    {"RRF", "1100"}, {"RLF", "1101"},
    {"SWAPF", "1110"}, {"INFSZ", "1111"}
};

ALU_OpCode::ALU_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands) {
    this->code = opcode;
    this->pichex = pichex_map.at(opcode);
    this->operands = operands;
    this->format = "00";
}

std::string ALU_OpCode::get_hex() const {
    return pichex;
}

std::string ALU_OpCode::get_code() const {
    return code;
}

std::list<std::shared_ptr<Operand>> ALU_OpCode::get_operands() const {
    return operands;
}

std::string ALU_OpCode::get_format() const {
    return format;
}

bool ALU_OpCode::is_pseudo_op() const {
    return false;
}
