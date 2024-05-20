#include "OpCode.hh"
#include <map>
#include <iostream>
#include <string>
#include <set>
//#include <unordered_set>
#include <unordered_map>
#include <stdexcept>

// Define the op_type_map here
std::unordered_map<std::string, std::string> op_type_map = {
        {"BCF", "B"}, {"BSF", "B"},
        {"BTFSC", "B"}, {"BTFSS", "B"},
        {"MOVWF", "ALU"}, {"CLR", "ALU"},
        {"SUBWF", "ALU"}, {"DECF", "ALU"},
        {"IORWF", "ALU"}, {"ANDWF", "ALU"},
        {"XORWF", "ALU"}, {"ADDWF", "ALU"},
        {"MOVF", "ALU"}, {"COMF", "ALU"},
        {"INCF", "ALU"}, {"DECFSZ", "ALU"},
        {"RRF", "ALU"}, {"RLF", "ALU"},
        {"SWAPF", "ALU"}, {"INFSZ", "ALU"},
        {"CALL", "CTRL"}, {"GOTO", "CTRL"},
        {"NOP", "MISC"}, {"RETURN", "MISC"},
        {"RETFIE", "MISC"}, {"OPTION", "MISC"},
        {"SLEEP", "MISC"}, {"CLRWDT", "MISC"},
        {"TRIS", "MISC"}, {"ADDLW", "W"},
        {"MOVLW", "W"}, {"RETLW", "W"},
        {"IORLW", "W"}, {"ANDLW", "W"},
        {"XORLW", "W"}, {"SUBLW", "W"}
};

std::unordered_map<std::string, std::string> valid_opcodes = {
        {"BCF", "B"}, {"BSF", "B"},
        {"BTFSC", "B"}, {"BTFSS", "B"},
        {"MOVWF", "ALU"}, {"CLR", "ALU"},
        {"SUBWF", "ALU"}, {"DECF", "ALU"},
        {"IORWF", "ALU"}, {"ANDWF", "ALU"},
        {"XORWF", "ALU"}, {"ADDWF", "ALU"},
        {"MOVF", "ALU"}, {"COMF", "ALU"},
        {"INCF", "ALU"}, {"DECFSZ", "ALU"},
        {"RRF", "ALU"}, {"RLF", "ALU"},
        {"SWAPF", "ALU"}, {"INFSZ", "ALU"},
        {"CALL", "CTRL"}, {"GOTO", "CTRL"},
        {"NOP", "MISC"}, {"RETURN", "MISC"},
        {"RETFIE", "MISC"}, {"OPTION", "MISC"},
        {"SLEEP", "MISC"}, {"CLRWDT", "MISC"},
        {"TRIS", "MISC"}, {"ADDLW", "W"},
        {"MOVLW", "W"}, {"RETLW", "W"},
        {"IORLW", "W"}, {"ANDLW", "W"},
        {"XORLW", "W"}, {"SUBLW", "W"}
};

// OpCode::OpCode(const std::string& code) : code(code) {}
OpCode::OpCode(const std::string& code) : code(code) {

    // std::cout << "WE IN" << code << std::endl;
    // std::cout << "WE IN" << this->code << std::endl;

    // printf("%pAHAHA\n", code);
    // printf("%sAHAHA\n", code);

    // this->code = code;

    if (valid_opcodes.find(code) == valid_opcodes.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        this->code = code;
        throw std::invalid_argument("Unknown opcode: " + code);
    } else{
            // printf("Ok tehre was no error\n");
    }

}

std::string OpCode::get_hex() const {
    return this->pichex;
}

std::string OpCode::get_code() const {
    printf("[%s]\n", this->code.c_str());
    return this->code;
}

std::list<std::shared_ptr<Operand>> OpCode::get_operands() const {
    return this->operands;
}

std::string OpCode::get_format() const {
    return this->format;
}

bool OpCode::is_pseudo_op() const {
    return false;
}


