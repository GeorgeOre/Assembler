
// Line.cpp
#include "Line.hh"

// OpCodes
#include "OpCode.hh"
#include "ALU_OpCode.hh"
#include "B_OpCode.hh"
#include "CTRL_OpCode.hh"
#include "Label_OpCode.hh"
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

// Structures
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// IO Utils
#include <iostream>
#include <sstream>
#include <iomanip>

// Math Utils
#include <numeric>
#include <algorithm>

// Misc Utils
#include <cctype>
#include <assert.h>
#include "str_utils.hh"


// Local (Static) Constants
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
    // {"Label:", "PSEUDO"},    // Label definition
    {".text", "PSEUDO"},     // Start text space
    {".data", "PSEUDO"},     // Start data space
    {".info", "PSEUDO"},     // Start info space
    {".equ", "PSEUDO"},      // Constant definition
    {".include", "PSEUDO"}   // Include file
};

// Constructor helper functions
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
    size_t valid = elements.size();

    // Attempt to create the OpCode object within the valid searching range
    for (size_t i = 0; i < MAX_OPCODE_POS && i < valid; i++) { 
            // std::cout << "\ttesting parse opcode" << i << std::endl;

        potential_opcode = elements[i];
    // std::cout << "\tpot op: |" << potential_opcode << "|" << std::endl;

        try // Try-catch to handle OpCode initalization errors
        {

    // std::cout << "\tinside the try" << std::endl;
            // Test for label first
            if (potential_opcode.back() == ':') {
    // std::cout << "\tdetected : at end" << std::endl;
                this->opcode = std::make_shared<Label_OpCode>(potential_opcode);
                // Add the element to the list to be parsed as a pseudo op
                // elements.push_back(potential_opcode.substr(0, potential_opcode.size()-1));
                elements.push_back(potential_opcode);
                // std::cout << "\tpushed back into elements" << std::endl;
            }   // Test for pseudo op next
            else if (potential_opcode.front() == '.') {
    // std::cout << "We got to line 3 found ." << std::endl;
                this->opcode = std::make_shared<Pseudo_OpCode>(potential_opcode);
            }   // Try to find predefined OpCodes
            else if (op_type_map.find(potential_opcode) != op_type_map.end()) {
    // std::cout << "We got to line 3 predefined opcode" << std::endl;
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
                else if (op_type == "W") {
                    this->opcode = std::make_shared<W_OpCode>(potential_opcode);
                }
                else {  // If none of these children were detected, then set error
                    this->contains_error = true;
                    this->error_message = "OpCode child type undefined in op_type_map (see Line.cpp)";
                }
            }   
            // Set found flag and remove the OpCode from the parsed elements
            elements.erase(elements.begin() + i);
            op_found = true;         
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

    // Set line to contain user defined if true for OpCode
    if (this->opcode->get_is_user_defined()) {
        this->contains_user_defined = true;
    }

}

void Line::parse_operands(const std::vector<std::string> &elements, const std::string operand_info) {
    // This function assumes that parse_opcode was called before it. The correct operand_info 
    // parameter should not have been attainable without parse_opcode being called. This is why
    // it is necesarry for the user to have passed in the info parameter even though it can be
    // easily accessed with this->get_opcode()->get_operand_info().

    // We were pipelined the elements that were modified by parse_opcode, we need the full string
    std::string operands_only = join_strings(elements, " ");

    // Now we need to parse the given elements into a vector of comma delimited operands
    std::vector<std::string> operands = split_string(operands_only, ',');

    // Make sure that the operand info matches the given operand elements
    assert(operand_info.size() == operands.size());
    

    // Go through all elements and define them based on the opcode's operand info
    std::string potential_operand;
    for (size_t i = 0; i < elements.size(); ++i) {
        potential_operand = elements[i];        
        try // Try-catch to handle OpCode initalization errors
        {
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

        // Check to see if the operand contained a user defined operand
        if (this->operands[i]->get_is_user_defined()) {
            // The line should know this to facilitate processing later
            this->contains_user_defined = true;
        }
    }

}

Line::Line(uint64_t line_number, const std::string& section,
    const std::string& line,  const std::string& f_name): 
        line_number(line_number), 
        memory_address(0), 
        section(section), 
        contains_error(false), 
        raw_line(line), 
        file_name(f_name), 
        contains_user_defined(false) {

    // std::cout << "We got to line 3 init constructor\n" << std::endl;


    // Search the line for comments and remove
    std::string stripped = remove_comments(line);

    // std::cout << "We got to line 3 strip good\n" << std::endl;


    // Start parsing line
    std::vector<std::string> elements = parse_line(stripped);

    // std::cout << "We got to line 3 parse good\n" << std::endl;


    // Define OpCode
    parse_opcode(elements);

    // std::cout << "We got to line 3 opcode good\n" << std::endl;


    // Define Operands
    std::string info = this->opcode->get_operand_info();
    parse_operands(elements, info);

}


// PICHEX CALCULARION FUNCTIONS
std::string get_addr(uint64_t addr){
	std::stringstream stream;
	stream << std::hex << std::uppercase << addr; // Changed to uppercase
	std::string address = stream.str();
	size_t length = address.size();
	size_t to_add = 4 - length;
	address.insert(0, to_add, '0');
	return address;
}

std::string get_size(uint64_t size){
	std::stringstream stream;
	stream << std::hex << std::uppercase << size; // Changed to uppercase
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
	stream << std::hex << std::uppercase << next; // Changed to uppercase
	std::string cs = stream.str();
	return cs;
}

std::string Line::to_pichex() const{
	// std::string to_return = "";
	unsigned long binary = 10;
	// unsigned long binary = bitset<16>(opcode.get_hex()).to_ulong();
	std::stringstream stream;
	stream << std::hex << std::uppercase << binary; // Changed to uppercase
	std::string data = stream.str();
	size_t length = data.size();
	if (length % 2 == 1){	
		data.insert(0, 1, '0');
	}
	
    // THIS IS NO LONGER ALL BUT
    std::string total_checksum = get_size(data.size()) +  get_addr(this->memory_address) + "02" + data + checksum(data.size(), get_addr(this->memory_address), "02", data);
	return ":" + total_checksum;
}

// Accessors and modifiers
uint64_t Line::get_line_number() {return this->line_number;}
uint64_t Line::get_memory_address() {return this->memory_address;}
std::string& Line::get_file_name() {return this->file_name;}
std::string& Line::get_section() {return this->section;}
std::string& Line::get_raw_line() {return this->raw_line;}
OpCode& Line::get_opcode() {return *this->opcode;}
std::vector<std::shared_ptr<Operand>>& Line::get_operands() {return this->operands;}
bool Line::get_contains_error() {return this->contains_error;}
bool Line::get_contains_user_defined() {return this->contains_user_defined;}
std::string& Line::get_error_message() {return this->error_message;}

void Line::set_line_number(uint64_t line){this->line_number = line;}
void Line::set_memory_address(uint64_t address){this->memory_address = address;}
void Line::set_file_name(std::string name){this->file_name = name;}
void Line::set_section(std::string section){this->section = section;}
void Line::set_raw_line(std::string line){this->raw_line = line;}
void Line::set_contains_error(bool result){this->contains_error = result;}
void Line::set_contains_user_defined(bool result){this->contains_user_defined = result;}
void Line::set_error_message(std::string message){this->error_message = message;}
