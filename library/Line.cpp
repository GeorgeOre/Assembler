// Line.cpp
#include "Line.hh"

// OpCodes
#include "OpCode.hh"
#include "ALU_OpCode.hh"
#include "B_OpCode.hh"
#include "CTRL_OpCode.hh"
#include "W_OpCode.hh"
#include "Boperand.hh"

// Structures and Utils
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> Line::op_type_map = {
    // Bit-Oriented Instructions
    {"BCF", "B"}, {"BSF", "B"},
    {"BTFSC", "B"}, {"BTFSS", "B"},

    // Byte-Oriented Instructions
    {"MOVWF", "ALU"}, {"CLRF", "ALU"},  // CLR IS SOMETIMES CALLED CLRF or CLR?? MAYBE HANDLE THIS MAPPING LATER
    {"SUBWF", "ALU"}, {"DECF", "ALU"},
    {"IORWF", "ALU"}, {"ANDWF", "ALU"},
    {"XORWF", "ALU"}, {"ADDWF", "ALU"},
    {"MOVF", "ALU"}, {"COMF", "ALU"},
    {"INCF", "ALU"}, {"DECFSZ", "ALU"},
    {"RRF", "ALU"}, {"RLF", "ALU"},
    {"SWAPF", "ALU"}, {"INCFSZ", "ALU"},

    // Literal Operations
    {"ADDLW", "W"}, {"MOVLW", "W"}, 
    {"RETLW", "W"}, {"IORLW", "W"}, 
    {"ANDLW", "W"}, {"XORLW", "W"}, 
    {"SUBLW", "W"},
    
    // Control Operations
    {"CALL", "CTRL"}, {"GOTO", "CTRL"},

    // Miscellaneous Instructions
    {"NOP", "MISC"}, {"RETURN", "MISC"},
    {"RETFIE", "MISC"}, {"OPTION", "MISC"},
    {"SLEEP", "MISC"}, {"CLRWDT", "MISC"},
    {"TRIS", "MISC"}, {"CLRW", "ALU"}  // Check if CLRW exists later
};



Line::Line(uint64_t line_num, const std::string& section,
 const std::string& line,  const std::string& f_info)
 : line_number(line_num), memory_address(-1), section(section), 
 contains_error(false), raw_line(line), file_name(f_info) {

    // Search the line for comment
    std::size_t comment_start = this->raw_line.find(';');
    
    // Strip line of comment if it exists
    if (comment_start != std::string::npos) {
        this->raw_line.substr(0, comment_start);
    }
    
    // Parse line
    parseLine();

}

void Line::parseLine(const std::string& line) {
    // Make a stream iterator for the line and a holder for the opcode
    std::istringstream str_stream(line);
    std::string potential_opcode;

    // Get the first word, eliminating spaces and such
    str_stream >> potential_opcode;

    // std::cout << "WE ABOUT TO START PARSING THIS LINE ASS FOO: [" << potential_opcode << "]" << std::endl;

    // Attempt to create the OpCode object; 
    // this can throw an exception if the opcode is invalid
    try
    {
        if (op_type_map.find(potential_opcode) != op_type_map.end()) {
            std::string op_type = op_type_map.at(potential_opcode);
            
            if (op_type == "ALU") {
		        opcode = ALU_OpCode(potential_opcode);
            }
            else if (op_type == "B") {
                opcode = B_OpCode(potential_opcode, operands);
            }
            else if (op_type == "CTRL") {
                opcode = CTRL_OpCode(potential_opcode, operands);
            }
            else if (op_type == "MISC") {
                opcode = Misc_OpCode(potential_opcode, operands);
            }
            else if (op_type == "W") {
                opcode = W_OpCode(potential_opcode, operands);
            }
            if (opcode_type.compare("ALU") == 0) {
                operands.push_back(std::make_unique<FOperand>(operandValue));
            } else if (type == 'k') {
                operands.push_back(std::make_unique<KOperand>(operandValue));
            } else if (type == 'b') {
                operands.push_back(std::make_unique<BOperand>(operandValue));
            }
            

        }

        this->opcode = OpCode(potential_opcode);
    }
    catch(const std::exception& e)
    {
        // If there was an error in making the OpCode, set error messages
        this->contains_error = true;
        this->error_message = e.what();
    }
     

    // Parse the rest of the line as potential operands    
    std::string potential_operand;
    while (str_stream >> potential_operand) {
        // THIS LOGIC THAT CHOOSES THE TYPES OF OPCODES BASED
        // ON THE NUMBER OF OPERANDS AND THE OPCODE
        try
        {
            //
            std::string operandValue;
                        Operand operand = Operand(potential_operand);
            this->operands.push_back(operand);  // Assuming Boperand is a concrete Operand subclass
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        

    }

// void Line::parseLine(const std::string& line, 
//                      const std::unordered_map<std::string, std::string>& op_type_map) {
//     std::istringstream iss(line);
//     std::string opcodeStr;
//     iss >> opcodeStr;

//     opcode = OpCode(opcodeStr);

//     auto it = op_type_map.find(opcodeStr);
//     if (it != op_type_map.end()) {
//         std::string operandTypes = it->second;
//         std::string operandValue;

//         for (char type : operandTypes) {
//             if (iss >> operandValue) {
//                 if (type == 'f') {
//                     operands.push_back(std::make_unique<FOperand>(operandValue));
//                 } else if (type == 'k') {
//                     operands.push_back(std::make_unique<KOperand>(operandValue));
//                 } else if (type == 'b') {
//                     operands.push_back(std::make_unique<BOperand>(operandValue));
//                 }
//             }
//         }
//     }
// }

}

std::string get_addr(u_int64_t addr){
	std::stringstream stream;
	stream << std::hex << addr;
	std::string address = stream.str();
	size_t length = address.size();
	size_t to_add = 4 - length;
	address.insert(0, to_add, '0');
	return address;
}

std::string get_size(u_int64_t size){
	std::stringstream stream;
	stream << std::hex << size;
	std::string address = stream.str();
	size_t length = address.size();
	size_t to_add = 2 - length;
	address.insert(0, to_add, '0');
	return address;
}

std::string checksum(int size, std::string line2, std::string line3, std::string line4){
	int sum = size;
	for (int i = 0; i < line2.size(); i += 2){
		std::string sub = line2.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	for (int i = 0; i < line3.size(); i += 2){
		std::string sub = line3.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	for (int i = 0; i < line4.size(); i += 2){
		std::string sub = line4.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	int modded = sum % 256;
	int next = 256 - modded;
	std::stringstream stream;
	stream << std::hex << next;
	std::string cs = stream.str();
	return cs;
}

std::string& Line::to_pichex() const{
	std::string to_return = "";
	unsigned long binary = 10;
	// unsigned long binary = bitset<16>(opcode.get_hex()).to_ulong();
	std::stringstream stream;
	stream << std::hex << binary;
	std::string data = stream.str();
	size_t length = data.size();
	if (length % 2 == 1){	
		data.insert(0, 1, '0');
	}
	
    // THIS IS NO LONGER ALL BUT
    std::string all_but_checksum = get_size(data.size()) +  get_addr(this->memory_address) + "02" + data + checksum(data.size(), get_addr(this->memory_address), "02", data);
	return all_but_checksum;
}


int Line::get_line_number() const {
    return this->line_number;
}

int Line::get_memory_address() const {
    return this->memory_address;
}

const std::string& Line::get_section() const {
    return this->section;
}

const std::string& Line::get_raw_line() const {
    return this->raw_line;
}


const OpCode& Line::get_opcode() const {
    return this->opcode;
}

const std::vector<Operand>& Line::get_operands() const {
    return this->operands;
}

const std::string& Line::get_error_message() const {
    return this->error_message;
}

void Line::set_memory_address(u_int64_t address) {
    this->memory_address = address;
}


// #include "Line.hh"

// #include "ALU_OpCode.hh"
// #include "B_OpCode.hh"
// #include "CTRL_OpCode.hh"
// #include "Misc_OpCode.hh"
// #include "W_OpCode.hh"
// #include "Boperand.hh"
// #include "Doperand.hh"
// #include "Foperand.hh"
// #include "Koperand.hh"

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stdbool.h>
// #include <string>
// #include <bitset>
// #include <list>
// #include <inttypes.h>

// #include <sstream>
// #include <algorithm>
// #include <cctype>
// #include <iostream>
// #include <regex>

// Line::Line(int lineNumber, const std::string& section, const std::string& line)
//     : lineNumber(lineNumber), programMemoryAddress(-1), section(section),  error(false) {
//     parseLine(line);
//     // if (!validateOpcode(opcode.get_code()) || !validateOperands(operands)) {
//     //     error = true;
//     //     errorMessage = "Invalid opcode or operands.";
//     // }
// }


// // void Line::parseLine(const std::string& line) {
// //     std::string trimmedLine = line;
// //     // Remove comments
// //     auto commentPos = trimmedLine.find(';');
// //     if (commentPos != std::string::npos) {
// //         trimmedLine = trimmedLine.substr(0, commentPos);
// //     }

// //     std::istringstream stream(trimmedLine);
// //     std::string token;

// //     // Parse opcode and operands
// //     if (stream >> token) {
// //         opcode = OpCode(token);
// //         while (stream >> token) {
// //             operands.push_back(createOperand(token));
// //         }
// //     }
// // }
// void Line::parseLine(const std::string& line) {
//     std::istringstream iss(line);
//     std::string token;
//     if (!(iss >> token)) {
//         setError("Failed to parse line: " + line);
//         return;
//     }
//     try {
//         opcode = OpCode(token);
//     } catch (const std::exception& e) {
//         setError("Failed to initialize OpCode: " + std::string(e.what()));
//         return;
//     }

//     while (iss >> token) {
//         try {
//             operands.push_back(std::make_shared<Operand>(token));
//         } catch (const std::exception& e) {
//             setError("Failed to initialize Operand: " + std::string(e.what()));
//             return;
//         }
//     }

//     std::cout << "Parsed line: " << line << "\n";
//     std::cout << "OpCode: " << opcode.get_code() << "\n";
//     std::cout << "Operands: ";
//     for (const auto& operand : operands) {
//         std::cout << operand->getRaw() << " ";
//     }
//     std::cout << "\n";
// }

// bool Line::validateOpcode(const std::string& opcode) const {
//     // Placeholder validation logic
//     return !opcode.empty() && std::all_of(opcode.begin(), opcode.end(), ::isalpha);
// }

// bool Line::validateOperands(const std::vector<std::shared_ptr<Operand>>& operands) const {
//     // Placeholder validation logic
//     return !operands.empty();
// }

// std::shared_ptr<Operand> Line::createOperand(const std::string& token) const {
//     // Placeholder logic to create specific operand type
//     if (token.find("B") != std::string::npos) {
//         return std::make_shared<Boperand>(token);
//     } else if (token.find("D") != std::string::npos) {
//         return std::make_shared<Doperand>(token);
//     } else if (token.find("F") != std::string::npos) {
//         return std::make_shared<Foperand>(token);
//     } else if (token.find("K") != std::string::npos) {
//         return std::make_shared<Koperand>(token);
//     } else {
//         return nullptr; // Invalid operand type
//     }
// }

// int Line::getLineNumber() const {
//     return lineNumber;
// }

// int Line::getProgramMemoryAddress() const {
//     return programMemoryAddress;
// }

// const std::string& Line::getSection() const {
//     return section;
// }

// const OpCode& Line::getOpCode() const {
//     return opcode;
// }
// const std::vector<std::shared_ptr<Operand>>& Line::getOperands() const {
//     return operands;
// }

// bool Line::hasError() const {
//     return containsError;
// }

// std::string Line::getErrorMessage() const {
//     return errorMessage;
// }

// void Line::setProgramMemoryAddress(int address) {
//     programMemoryAddress = address;
// }
