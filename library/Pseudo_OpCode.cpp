#include "Pseudo_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>

// Initialize the static members
std::unordered_map<std::string, std::string> Pseudo_OpCode::op_format_map = {
    {"Label:", ":$"},   // Label definition
    {".text", "^."},    // Start text space
    {".data", "^."},    // Start data space
    {".info", "^."},    // Start info space
    {".equ", "^."},     // Constant definition
    {"include", "inc"}, // Include file
    {"org", "^org"}     // Set program counter reference value
};

std::unordered_map<std::string, std::string> Pseudo_OpCode::op_bin_map = {
    {"Label:", ""},    // Label definition
    {".text", ""},     // Start text space
    {".data", ""},     // Start data space
    {".info", ""},     // Start info space
    {".equ", ""},      // Constant definition
    {".include", ""},  // Include file
    {"org", ""}        // Set program counter reference value
};

std::unordered_map<std::string, std::string> Pseudo_OpCode::op_operand_map = {
    {"Label:", "p"},    // Label definition p
    {".text", ""},      // Start text space
    {".data", ""},      // Start data space
    {".info", ""},      // Start info space
    {".equ", "pp"},     // Constant definition, pp
    {".include", "p"},  // Include file, p
    {"org", "p"}        // Set program counter reference value, p
};

// Constructor
Pseudo_OpCode::Pseudo_OpCode(const std::string& opcode) : OpCode(opcode) {
    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Pseudo_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Pseudo_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Pseudo_OpCode does not have operand info");
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

void Pseudo_OpCode::set_size(u_int64_t size){
    this->size = size;    
}
void Pseudo_OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void Pseudo_OpCode::set_format(std::string format){
    this->format = format;
}
void Pseudo_OpCode::set_binary(std::string binary){
    this->binary = binary;
}


void Pseudo_OpCode::print_value() const {
    std::cout << "Pseudo_OpCode - Code: " << code_str << ", Binary: " << binary << ", Format: " << format << ", Size: " << size << std::endl;
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
