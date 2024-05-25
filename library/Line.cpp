
// Line.cpp
#include "Line.hh"

// OpCodes
#include "OpCode.hh"
#include "ALU_OpCode.hh"
#include "B_OpCode.hh"
#include "CTRL_OpCode.hh"
#include "Misc_OpCode.hh"
#include "Pseudo_OpCode.hh"
#include "W_OpCode.hh"

// Operands
#include "Operand.hh"
#include "Boperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"
#include "Koperand.hh"
#include "Poperand.hh"

// Structures and Utils
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <assert.h>
#include <numeric>

static const size_t MAX_OPCODE_POS = 2;

std::unordered_map<std::string, std::string> Line::op_type_map = {
    // Bit-Oriented Instructions
    {"BCF", "B"}, {"BSF", "B"},
    {"BTFSC", "B"}, {"BTFSS", "B"},

    // Byte-Oriented Instructions
    {"MOVWF", "ALU"}, {"CLR", "ALU"},  // CLR IS SOMETIMES CALLED CLRF or CLRW?? MAYBE HANDLE THIS MAPPING LATER
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
    {"TRIS", "MISC"},//, {"CLRW", "ALU"}  // Check if CLRW exists later

    // Pseudo Ops
    {"Label:", "PSEUDO"},    // Label definition
    {".text", "PSEUDO"},     // Start text space
    {".data", "PSEUDO"},     // Start data space
    {".info", "PSEUDO"},     // Start info space
    {".equ", "PSEUDO"},      // Constant definition
    {".include", "PSEUDO"}   // Include file
};



Line::Line(uint64_t line_number, const std::string& section,
    const std::string& line,  const std::string& f_name): 
        line_number(line_number), 
        memory_address(0), 
        section(section), 
        contains_error(false), 
        raw_line(line), 
        file_name(f_name), 
        contains_user_defined(false) {

    // Search the line for comments and remove
    std::string stripped = remove_comments(line);

    // Start parsing line
    std::vector<std::string> elements = parse_line(stripped);

    // Define OpCode
    parse_opcode(elements);

    // Define Operands
    std::string info = this->opcode->get_operand_info();
    parse_operands(elements, info);

}

/* THIS IS THE VERSION THAT COMPILES BUT YOU GOTTA .hh IT
void Line::parseLine() {
    // Make a stream iterator for the line and a holder for the opcode
    std::istringstream str_stream(this->raw_line);
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
		        this->opcode = std::make_shared<ALU_OpCode>(potential_opcode);// ALU_OpCode(potential_opcode);
            }
            else if (op_type == "B") {
                this->opcode = std::make_shared<B_OpCode>(potential_opcode);
            }
            else if (op_type == "CTRL") {
                this->opcode = std::make_shared<CTRL_OpCode>(potential_opcode);
            }
            else if (op_type == "MISC") {
                this->opcode = std::make_shared<Misc_OpCode>(potential_opcode);
            }
            else if (op_type == "PSEUDO") {
                this->opcode = std::make_shared<Pseudo_OpCode>(potential_opcode);
            }
            else if (op_type == "W") {
                this->opcode = std::make_shared<W_OpCode>(potential_opcode);
            }
            else {
                // If none of these were detected, then set error
                this->contains_error = true;
                this->error_message = "OpCode type undefined in optype hashtable";
            }
        }
    }
    catch(const std::exception& e)
    {
        // If there was an error in making the specific OpCode, set error
        this->contains_error = true;
        this->error_message = e.what();
    }
     

    // Parse the rest of the line as potential operands    
    std::string potential_operand;
    std::string info = this->opcode->get_operand_info();
    int count = 0;
    while (str_stream >> potential_operand) {
        // Attempt to init each operand based on the opcode operand info
        try
        {
            // Try to init each operand according to the operand info
            if (info.at(count) == 'b') {
                this->operands.push_back(std::make_shared<Boperand>(potential_operand));
            } else if (info.at(count) == 'd') {
                this->operands.push_back(std::make_shared<Doperand>(potential_operand));
            } else if (info.at(count) == 'f') {
                this->operands.push_back(std::make_shared<Foperand>(potential_operand));
            } else if (info.at(count) == 'k') {
                this->operands.push_back(std::make_shared<Koperand>(potential_operand));
            } else if (info.at(count) == 'p') {
                this->operands.push_back(std::make_shared<Poperand>(potential_operand));
            } else {
                // If the operand type was not detected, set error
                this->contains_error = true;
                this->error_message = "Operand type undefined in operand elif";
            }
        }
        catch(const std::exception& e)
        {
            // If there was an error in making the specific Operand, set error
            this->contains_error = true;
            this->error_message = e.what();
        }

        // CURRENTLY ONLY OPERANDS WILL BE USER DEFINED
        // Check to see if the line contains a user defined operand
        if (this->operands[count]->get_is_user_defined()) {
            this->contains_user_defined = true;
        }
        
        // Update operand count
        count++;
        // printf("We have added %d operands\n", count);
    }
*/

// Helper functions
std::string remove_comments(const std::string &line) {
    std::size_t comment_start = line.find(';');
    // Strip line of comment if it exists
    if (comment_start != std::string::npos) {
        return line.substr(0, comment_start);
    }
    // If not, return the original line
    return line;
}

std::vector<std::string> parse_line(const std::string &line) {
    // Make a stream iterator for the line and start parsing the line
    std::istringstream str_stream(line);
    std::vector<std::string> words;
    std::string word;

    // Read all words from the stream assuming space delimitors
    while (str_stream >> word) {
        words.push_back(word);
    }

    // Return all items found
    return words;
}

void Line::parse_opcode(std::vector<std::string> &elements) {
    // Local vars
    std::string potential_opcode;
    bool op_found = false;

    // Attempt to create the OpCode object within the valid searching range
    for (size_t i = 0; i < MAX_OPCODE_POS && i < elements.size(); i++) { 
        potential_opcode = elements[i];
        try // Try-catch to handle OpCode initalization errors
        {
            if (op_type_map.find(potential_opcode) != op_type_map.end()) {
                std::string op_type = op_type_map.at(potential_opcode);
                
                if (op_type == "ALU") {
    		        this->opcode = std::make_shared<ALU_OpCode>(potential_opcode);
                }
                else if (op_type == "B") {
                    this->opcode = std::make_shared<B_OpCode>(potential_opcode);
                }
                else if (op_type == "CTRL") {
                    this->opcode = std::make_shared<CTRL_OpCode>(potential_opcode);
                }
                else if (op_type == "MISC") {
                    this->opcode = std::make_shared<Misc_OpCode>(potential_opcode);
                }
                else if (op_type == "PSEUDO") {
                    this->opcode = std::make_shared<Pseudo_OpCode>(potential_opcode);
                }
                else if (op_type == "W") {
                    this->opcode = std::make_shared<W_OpCode>(potential_opcode);
                }
                else {
                    // If none of these children were detected, then set error
                    this->contains_error = true;
                    this->error_message = "OpCode child type undefined in op_type_map (see Line.cpp)";
                }
                
                // Set found flag and remove the OpCode from the parsed elements
                elements.erase(elements.begin() + i);
                op_found = true;
            }            
        }
        catch(const std::exception& e)
        {
            // If there was an error in initalizing the OpCode, set error
            this->contains_error = true;
            this->error_message = e.what();
        }

        // Exit the for loop if an OpCode was created
        if (op_found == true) {
            break;
        }
    }

    // Set an error if no OpCode was detected
    if (op_found == false) {
        this->contains_error = true;
        this->error_message = "No OpCode or pseudo op found";
    }

}

// From internet
std::string join_strings(const std::vector<std::string>& vec, const std::string& separator) {
    if (vec.empty()) return "";
    return std::accumulate(std::next(vec.begin()), vec.end(), vec[0],
                           [&separator](const std::string& a, const std::string& b) {
                               return a + separator + b;
                           });
}
std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start)); // Add the last segment
    
    return result;
}

void Line::parse_operands(const std::vector<std::string> &elements, const std::string operand_info) {
    // This function assumes that parse_opcode was called before it. The correct operand_info 
    // parameter should not have been attainable without parse_opcode being called. This is why
    // it is necesarry for the user to have passed in the info parameter even though it can be
    // easily accessed with this->get_opcode()->get_operand_info().
    std::string operands_only = join_strings(elements, " ");

    // Now we need to parse the given elements into a vector of comma delimited operands
    std::vector<std::string> operands = split_string(operands_only, ',');

    // Make sure that the operand info matches the given operand elements
    assert(operand_info.size() == operands.size());

    // Go through all elements and define them based on the opcode's operand info
    std::string potential_operand;
    for (size_t i = 1; i < elements.size(); ++i) {
        potential_operand = elements[i];
        try // Try-catch to handle OpCode initalization errors
        {
            // Try to init each operand according to the operand info
            if (operand_info.at(i) == 'b') {
                this->operands.push_back(std::make_shared<Boperand>(potential_operand));
            } else if (operand_info.at(i) == 'd') {
                this->operands.push_back(std::make_shared<Doperand>(potential_operand));
            } else if (operand_info.at(i) == 'f') {
                this->operands.push_back(std::make_shared<Foperand>(potential_operand));
            } else if (operand_info.at(i) == 'k') {
                this->operands.push_back(std::make_shared<Koperand>(potential_operand));
            } else if (operand_info.at(i) == 'p') {
                this->operands.push_back(std::make_shared<Poperand>(potential_operand));
            } else {
                // If the operand type was not detected, set error
                this->contains_error = true;
                this->error_message = "Operand type undefined in operand elif";
            }
        }
        catch(const std::exception& e)
        {
            // If there was an error in making the specific Operand, set error
            this->contains_error = true;
            this->error_message = e.what();
        }
        // Placeholder print
        std::cout << "Operand: " << elements[i] << std::endl;

        // Example of identifying and evaluating an expression
        if (elements[i].find('+') != std::string::npos ||
            elements[i].find('-') != std::string::npos) {
            std::cout << "Expression found: " << elements[i] << std::endl;
            // Evaluate the expression (simple example, you might want a full parser here)
            // For example, if the operand is "1+2", you should evaluate it and print the result
        }

        // Example of user-defined handling (you can expand this logic)
        if (elements[i].find("user_defined") != std::string::npos) {
            std::cout << "User defined element found: " << elements[i] << std::endl;
        }
    }


    // Parse the rest of the line as potential operands    

    // CURRENTLY ONLY OPERANDS WILL BE USER DEFINED
    // Check to see if the line contains a user defined operand
    if (this->operands[count]->get_is_user_defined()) {
        this->contains_user_defined = true;
    }
    
    // Update operand count
    count++;
    // printf("We have added %d operands\n", count);

}

/* EXPRESSION BS
#include <stack>
#include <unordered_map>

int evaluate_expression(const std::string &expression, const std::unordered_map<std::string, int> &symbol_table) {
    std::stack<int> values;
    std::stack<char> operators;

    auto apply_operator = [](std::stack<int> &values, char op) {
        int b = values.top(); values.pop();
        int a = values.top(); values.pop();
        switch (op) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/': values.push(a / b); break;
        }
    };

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isspace(ch)) {
            continue;
        } else if (isdigit(ch)) {
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                ++i;
            }
            --i;
            values.push(value);
        } else if (isalpha(ch)) {
            std::string symbol;
            while (i < expression.length() && (isalnum(expression[i]) || expression[i] == '_')) {
                symbol += expression[i];
                ++i;
            }
            --i;
            if (symbol_table.find(symbol) != symbol_table.end()) {
                values.push(symbol_table.at(symbol));
            } else {
                throw std::runtime_error("Undefined symbol: " + symbol);
            }
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                apply_operator(values, operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();
            }
        } else if (strchr("+-* /", ch)) { // THIS SPACE WAS CAUSING COMMENT PROBLEMS AND SHOULD BE REMOVED
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                apply_operator(values, operators.top());
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        apply_operator(values, operators.top());
        operators.pop();
    }
    return values.top();
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

void second_pass(std::vector<Line> &lines, const std::unordered_map<std::string, int> &symbol_table) {
    for (Line &line : lines) {
        for (Operand &operand : line.operands) {
            if (operand.type == EXPRESSION) {
                try {
                    int result = evaluate_expression(operand.value, symbol_table);
                    operand.type = IMMEDIATE;
                    operand.value = std::to_string(result);
                } catch (const std::exception &e) {
                    std::cerr << "Error evaluating expression: " << operand.value << " - " << e.what() << std::endl;
                }
            }
        }
    }
}

*/


// void Line::parseLine() {}

// JEB VERSION
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


// PICHEX CALCULARION FUNCTIONS

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

std::string Line::to_pichex() const{
	// std::string to_return = "";
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
    std::string total_checksum = get_size(data.size()) +  get_addr(this->memory_address) + "02" + data + checksum(data.size(), get_addr(this->memory_address), "02", data);
	return total_checksum;
}









u_int64_t Line::get_line_number() {//
    return this->line_number;
}
u_int64_t Line::get_memory_address() {//
    return this->memory_address;
}
std::string& Line::get_file_name() {//
    return this->file_name;
}
std::string& Line::get_section() {//
    return this->section;
}
std::string& Line::get_raw_line() {//
    return this->raw_line;
}
OpCode& Line::get_opcode() {//
    return *this->opcode;
}
std::vector<std::shared_ptr<Operand>>& Line::get_operands() {//
    return this->operands;
}
bool Line::get_contains_error() {//
    return this->contains_error;
}
bool Line::get_contains_user_defined() {//
    return this->contains_user_defined;
}
std::string& Line::get_error_message() {//
    return this->error_message;
}

void Line::set_line_number(uint64_t line){
    this->line_number = line;
}
void Line::set_memory_address(uint64_t address){
    this->memory_address = address;
}
void Line::set_file_name(std::string name){
    this->file_name = name;
}
void Line::set_section(std::string section){
    this->section = section;
}
void Line::set_raw_line(std::string line){
    this->raw_line = line;
}
void Line::set_contains_error(bool result){
    this->contains_error = result;
}
void Line::set_contains_user_defined(bool result){
    this->contains_user_defined = result;
}
void Line::set_error_message(std::string message){
    this->error_message = message;
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
