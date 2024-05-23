#include "ALU_OpCode.hh"
#include "Operand.hh"

#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, std::string> ALU_OpCode::op_format_map = {
    {"MOVWF", "^00...01...$"},  // Move W to f
    {"CLR", "^00...01...$"},    // Clear f (CLRF or CLRW)
    {"SUBWF", "^00...10...$"},  // Subtract W from f
    {"DECF", "^00...11...$"},   // Decrement f
    {"IORWF", "^00..100...$"},  // Inclusive OR f and W
    {"ANDWF", "^00..101...$"},  // AND f and W
    {"XORWF", "^00..110...$"},  // Exclusive OR f and W
    {"ADDWF", "^00..111...$"},  // Add W to f
    {"MOVF", "^00..000...$"},   // Move f to destination
    {"COMF", "^00..001...$"},   // Complement f
    {"INCF", "^00..010...$"},   // Increment f
    {"DECFSZ", "^00..011...$"}, // Decrement f, skip if zero
    {"RRF", "^00..100...$"},    // Rotate right through carry
    {"RLF", "^00..101...$"},    // Rotate left through carry
    {"SWAPF", "^00..110...$"},  // Swap nibbles of f
    {"INFSZ", "^00..111...$"},  // Increment f, skip if zero
};

std::unordered_map<std::string, std::string> ALU_OpCode::op_bin_map = {
    {"MOVWF", "0000001"},  // Move W to f
    {"CLR", "000001"},    // Clear f (CLRF or CLRW)
    {"SUBWF", "000010"},  // Subtract W from f
    {"DECF", "000011"},   // Decrement f
    {"IORWF", "000100"},  // Inclusive OR f and W
    {"ANDWF", "000101"},  // AND f and W
    {"XORWF", "000110"},  // Exclusive OR f and W
    {"ADDWF", "000111"},  // Add W to f
    {"MOVF", "001000"},   // Move f to destination
    {"COMF", "001001"},   // Complement f
    {"INCF", "001010"},   // Increment f
    {"DECFSZ", "001011"}, // Decrement f, skip if zero
    {"RRF", "001100"},    // Rotate right through carry
    {"RLF", "001101"},    // Rotate left through carry
    {"SWAPF", "001110"},  // Swap nibbles of f
    {"INFSZ", "001111"},  // Increment f, skip if zero
};


std::unordered_map<std::string, std::string> ALU_OpCode::op_operand_map = {
    {"MOVWF", "f"},  // Move W to f
    {"CLR", "df"},    // Clear f (CLRF or CLRW)
    {"SUBWF", "df"},  // Subtract W from f
    {"DECF", "df"},   // Decrement f
    {"IORWF", "df"},  // Inclusive OR f and W
    {"ANDWF", "df"},  // AND f and W
    {"XORWF", "df"},  // Exclusive OR f and W
    {"ADDWF", "df"},  // Add W to f
    {"MOVF", "df"},   // Move f to destination
    {"COMF", "df"},   // Complement f
    {"INCF", "df"},   // Increment f
    {"DECFSZ", "df"}, // Decrement f, skip if zero
    {"RRF", "df"},    // Rotate right through carry
    {"RLF", "df"},    // Rotate left through carry
    {"SWAPF", "df"},  // Swap nibbles of f
    {"INFSZ", "df"},  // Increment f, skip if zero
};

ALU_OpCode::ALU_OpCode(const std::string& opcode) : OpCode(opcode) {
    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("ALU_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("ALU_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("ALU_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info
        this->operand_info = op_operand_map.at(opcode);        
    }
}

// std::string ALU_OpCode::get_binary() const{
//     return this->binary;
// }

// void ALU_OpCode::set_binary(std::string binary){
//     this->binary = binary;
// }




// std::string ALU_OpCode::get_hex() const {
//     return pichex;
// }

// std::string ALU_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> ALU_OpCode::get_operands() const {
//     return operands;
// }

// std::string ALU_OpCode::get_format() const {
//     return format;
// }

// bool ALU_OpCode::is_pseudo_op() const {
//     return false;
// }
