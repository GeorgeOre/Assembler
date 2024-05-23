#include "OpCode.hh"
#include <map>
#include <iostream>
#include <string>
#include <set>
//#include <unordered_set>
#include <unordered_map>
#include <stdexcept>


//MAYBE ALL MAPS ARE IRRELEVANT IN THIS FILE AND SHOULD INSTEAD BE IN THE CHILDREN FILES
// Define the op_format_map here
// std::unordered_map<std::string, std::string> op_format_map = {
//     {"BCF", "^0100[01]...$"},  // Clear bit b of f
//     {"BSF", "^0101[01]...$"},  // Set bit b of f
//     {"BTFSC", "^0110[01]...$"}, // Skip if bit b of f is clear
//     {"BTFSS", "^0111[01]...$"}, // Skip if bit b of f is set
//     {"MOVWF", "^00...01...$"},  // Move W to f
//     {"CLR", "^00...01...$"},    // Clear f (CLRF or CLRW)
//     {"SUBWF", "^00...10...$"},  // Subtract W from f
//     {"DECF", "^00...11...$"},   // Decrement f
//     {"IORWF", "^00..100...$"},  // Inclusive OR f and W
//     {"ANDWF", "^00..101...$"},  // AND f and W
//     {"XORWF", "^00..110...$"},  // Exclusive OR f and W
//     {"ADDWF", "^00..111...$"},  // Add W to f
//     {"MOVF", "^00..000...$"},   // Move f to destination
//     {"COMF", "^00..001...$"},   // Complement f
//     {"INCF", "^00..010...$"},   // Increment f
//     {"DECFSZ", "^00..011...$"}, // Decrement f, skip if zero
//     {"RRF", "^00..100...$"},    // Rotate right through carry
//     {"RLF", "^00..101...$"},    // Rotate left through carry
//     {"SWAPF", "^00..110...$"},  // Swap nibbles of f
//     {"INFSZ", "^00..111...$"},  // Increment f, skip if zero
//     {"CALL", "^100...$"},       // Call subroutine
//     {"GOTO", "^101...$"},       // Jump to address k
//     {"NOP", "^00000000000000$"}, // No operation
//     {"RETURN", "^00000000001000$"}, // Return from subroutine
//     {"RETFIE", "^00000000001001$"}, // Return from interrupt
//     {"OPTION", "^000000011010$"},   // Copy W to OPTION register (deprecated)
//     {"SLEEP", "^000000011011$"},    // Go into standby mode
//     {"CLRWDT", "^000000011100$"},   // Restart watchdog timer
//     {"TRIS", "^0000000111..$"},     // Copy W to tri-state register (deprecated)
//     {"ADDLW", "^111110.$"},         // Add literal to W
//     {"MOVLW", "^110000.$"},         // Move literal to W
//     {"RETLW", "^110001.$"},         // Move literal to W and return from subroutine
//     {"IORLW", "^111000.$"},         // Inclusive OR literal with W
//     {"ANDLW", "^111001.$"},         // AND literal with W
//     {"XORLW", "^111010.$"},         // Exclusive OR literal with W
//     {"SUBLW", "^111100.$"},         // Subtract W from literal
// };

// // Define the op_type_map here
// std::unordered_map<std::string, std::string> op_type_map = {
//     {"BCF", "B, f"},             // Clear bit b of f
//     {"BSF", "B, f"},             // Set bit b of f
//     {"BTFSC", "B, f"},           // Skip if bit b of f is clear
//     {"BTFSS", "B, f"},           // Skip if bit b of f is set
//     {"MOVWF", "f"},              // Move W to f
//     {"CLR", "f, d"},             // Clear f
//     {"SUBWF", "f, d"},           // Subtract W from f
//     {"DECF", "f, d"},            // Decrement f
//     {"IORWF", "f, d"},           // Inclusive OR f and W
//     {"ANDWF", "f, d"},           // AND f and W
//     {"XORWF", "f, d"},           // Exclusive OR f and W
//     {"ADDWF", "f, d"},           // Add W to f
//     {"MOVF", "f, d"},            // Move f to destination
//     {"COMF", "f, d"},            // Complement f
//     {"INCF", "f, d"},            // Increment f
//     {"DECFSZ", "f, d"},          // Decrement f, skip if zero
//     {"RRF", "f, d"},             // Rotate right through carry
//     {"RLF", "f, d"},             // Rotate left through carry
//     {"SWAPF", "f, d"},           // Swap nibbles of f
//     {"INFSZ", "f, d"},           // Increment f, skip if zero
//     {"CALL", "k"},               // Call subroutine
//     {"GOTO", "k"},               // Jump to address k
//     {"NOP", "None"},             // No operation
//     {"RETURN", "None"},          // Return from subroutine
//     {"RETFIE", "None"},          // Return from interrupt
//     {"OPTION", "None"},          // Copy W to OPTION register (deprecated)
//     {"SLEEP", "None"},           // Go into standby mode
//     {"CLRWDT", "None"},          // Restart watchdog timer
//     {"TRIS", "f"},               // Copy W to tri-state register (deprecated)
//     {"ADDLW", "k"},              // Add literal to W
//     {"MOVLW", "k"},              // Move literal to W
//     {"RETLW", "k"},              // Move literal to W and return from subroutine
//     {"IORLW", "k"},              // Inclusive OR literal with W
//     {"ANDLW", "k"},              // AND literal with W
//     {"XORLW", "k"},              // Exclusive OR literal with W
//     {"SUBLW", "k"}               // Subtract W from literal
// };

// std::unordered_map<std::string, std::string> valid_opcodes = {
//         {"BCF", "B"}, {"BSF", "B"},
//         {"BTFSC", "B"}, {"BTFSS", "B"},
//         {"MOVWF", "ALU"}, {"CLR", "ALU"},
//         {"SUBWF", "ALU"}, {"DECF", "ALU"},
//         {"IORWF", "ALU"}, {"ANDWF", "ALU"},
//         {"XORWF", "ALU"}, {"ADDWF", "ALU"},
//         {"MOVF", "ALU"}, {"COMF", "ALU"},
//         {"INCF", "ALU"}, {"DECFSZ", "ALU"},
//         {"RRF", "ALU"}, {"RLF", "ALU"},
//         {"SWAPF", "ALU"}, {"INFSZ", "ALU"},
//         {"CALL", "CTRL"}, {"GOTO", "CTRL"},
//         {"NOP", "MISC"}, {"RETURN", "MISC"},
//         {"RETFIE", "MISC"}, {"OPTION", "MISC"},
//         {"SLEEP", "MISC"}, {"CLRWDT", "MISC"},
//         {"TRIS", "MISC"}, {"ADDLW", "W"},
//         {"MOVLW", "W"}, {"RETLW", "W"},
//         {"IORLW", "W"}, {"ANDLW", "W"},
//         {"XORLW", "W"}, {"SUBLW", "W"}
// };

// OpCode::OpCode(const std::string& code) : code(code) {}
OpCode::OpCode(const std::string& code) : code_str(code) {
    // This constructor should theoretically never be called, but we can make it exist to set the code_str

    // std::cout << "WE IN" << code << std::endl;
    // std::cout << "WE IN" << this->code << std::endl;
    // printf("%pAHAHA\n", code);
    // printf("%sAHAHA\n", code);

    //THIS CODE SHOULD BE IN CHILD AND A TRY CATCH SHOULD BE IN LINE!!! VVVVVVVVV
/*
    // Make sure that the opcode is valid
    if (op_type_map.find(code) == op_type_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        this->code_str = code;
        throw std::invalid_argument("Unknown opcode: " + code);
    } else{
        // If it was valid we should set params
        this->operand_info = op_type_map.at(code);
        this->format = op_format_map.at(code);
        
    }
*/

}



std::string OpCode::get_code_str(){
    // printf("[%s]\n", this->code_str.c_str());
    return this->code_str;
}

uint64_t OpCode::get_size(){
    return this->size;
}

std::string OpCode::get_operand_info(){
    return this->operand_info;
}

std::string OpCode::get_format(){
    return this->format;
}

// bool OpCode::get_is_pseudo_op(){
//     return this->is_pseudo_op;
// }


// std::list<std::shared_ptr<Operand>> OpCode::get_operands() const {
//     return this->operands;
// }

// void OpCode::set_code(std::string code){
//     this->code_str = code;
// }

// THE FOLLOWING ARE DEFAULTS AND SHOULD ALWAYS BE OVERWRITTEN
void OpCode::set_size(u_int64_t size){
    this->size = size;
}
void OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void OpCode::set_format(std::string format){
    this->format = format;
}

// void OpCode::set_is_pseudo_op(bool result){
//     this->is_pseudo_op = result;
// }

