#include "B_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, std::string> B_OpCode::op_format_map = {
    {"BCF", "^01..000...$"},   // Bit Clear f
    {"BSF", "^01..001...$"},   // Bit Set f
    {"BTFSC", "^01..010...$"}, // Bit Test f, Skip if Clear
    {"BTFSS", "^01..011...$"}  // Bit Test f, Skip if Set
};

std::unordered_map<std::string, std::string> B_OpCode::op_bin_map = {
    {"BCF", "0100"},   // Bit Clear f
    {"BSF", "0101"},   // Bit Set f
    {"BTFSC", "0110"}, // Bit Test f, Skip if Clear
    {"BTFSS", "0111"}  // Bit Test f, Skip if Set
};

std::unordered_map<std::string, std::string> B_OpCode::op_operand_map = {
    {"BCF", "fb"},   // Bit Clear f
    {"BSF", "fb"},   // Bit Set f
    {"BTFSC", "fb"}, // Bit Test f, Skip if Clear
    {"BTFSS", "fb"}  // Bit Test f, Skip if Set
};

B_OpCode::B_OpCode(const std::string& opcode) : OpCode(opcode) {
    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("B_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("B_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("B_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info
        this->operand_info = op_operand_map.at(opcode);        
    }

    // this->code = opcode;
    // this->operands = operands;
    // auto it = b_map.find(opcode);
    // if (it != b_map.end()) {
    //     this->pichex = it->second;
    // } else {
    //     // Handle error or assign a default value
    // }
}

// std::string B_OpCode::get_hex() const {
//     return pichex;
// }

// std::string B_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> B_OpCode::get_operands() const {
//     return operands;
// }

// std::string B_OpCode::get_format() const {
//     return format;
// }

// bool B_OpCode::is_pseudo_op() const {
//     return false;
// }
