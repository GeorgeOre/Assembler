#include "CTRL_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, std::string> CTRL_OpCode::op_format_map = {
    {"CALL", "^10."},   // Call subroutine
    {"GOTO", "^10."},   // Go to address
};

std::unordered_map<std::string, std::string> CTRL_OpCode::op_bin_map = {
    {"CALL", "100"},   // Call subroutine
    {"GOTO", "101"},   // Go to address
};

std::unordered_map<std::string, std::string> CTRL_OpCode::op_operand_map = {
    {"CALL", "k"},   // Call subroutine
    {"GOTO", "k"},   // Go to address
};

CTRL_OpCode::CTRL_OpCode(const std::string& opcode) : OpCode(opcode) {

    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("CTRL_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("CTRL_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("CTRL_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info
        this->operand_info = op_operand_map.at(opcode);        
    }

    // this->code = opcode;
    // this->operands = operands;
    // auto it = ctrl_map.find(opcode);
    // if (it != ctrl_map.end()) {
    //     this->pichex = it->second;
    // } else {
    //     // Handle error or assign a default value
    // }
}

// std::string CTRL_OpCode::get_hex() const {
//     return pichex;
// }

// std::string CTRL_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> CTRL_OpCode::get_operands() const {
//     return operands;
// }

// std::string CTRL_OpCode::get_format() const {
//     return format;
// }

// bool CTRL_OpCode::is_pseudo_op() const {
//     return false;
// }
