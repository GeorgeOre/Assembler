
// Line.cpp
#include "Line.hh"
#include "Translator.hh"

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
#include <bitset>

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
    {"MOVWF", "ALU"}, {"CLR", "ALU"},
    {"CLRF", "ALU"}, {"CLRW", "ALU"},
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
    {"TRIS", "MISC"},

    // Pseudo Ops
    // {"Label:", "PSEUDO"},// Label definition
    {".TEXT", "PSEUDO"},    // Start text space
    {".DATA", "PSEUDO"},    // Start data space
    {".INFO", "PSEUDO"},    // Start info space
    {".EQU", "PSEUDO"},     // Constant definition
    {".INCLUDE", "PSEUDO"}, // Include file

    // Lowercase
    {"bcf", "B"}, {"bsf", "B"}, {"btfsc", "B"}, {"btfss", "B"},
    {"movwf", "ALU"}, {"clr", "ALU"}, {"clrf", "ALU"}, {"clrw", "ALU"}, {"subwf", "ALU"}, {"decf", "ALU"},
    {"iorwf", "ALU"}, {"andwf", "ALU"}, {"xorwf", "ALU"}, {"addwf", "ALU"},
    {"movf", "ALU"}, {"comf", "ALU"}, {"incf", "ALU"}, {"decfsz", "ALU"},
    {"rrf", "ALU"}, {"rlf", "ALU"}, {"swapf", "ALU"}, {"incfsz", "ALU"},
    {"addlw", "W"}, {"movlw", "W"}, {"retlw", "W"}, {"iorlw", "W"},
    {"andlw", "W"}, {"xorlw", "W"}, {"sublw", "W"}, {"call", "CTRL"},
    {"goto", "CTRL"}, {"nop", "MISC"}, {"return", "MISC"}, {"retfie", "MISC"},
    {"option", "MISC"}, {"sleep", "MISC"}, {"clrw", "MISC"}, {"clrw", "ALU"},
    {"tris", "MISC"}, {".text", "PSEUDO"}, {".data", "PSEUDO"},
    {".info", "PSEUDO"}, {".equ", "PSEUDO"}, {".include", "PSEUDO"}

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

std::vector<std::string> parse_line(std::string &line) {
    // Make a stream iterator for the line and start parsing the line
    std::istringstream str_stream(line);
    std::vector<std::string> words;
    std::string word;

    // Read all words from the stream assuming space delimitors
    while (str_stream >> word) {
        words.push_back(word);
// std::cout << "\t\t" << word << std::endl;        
    }

    // Return all items found
    return words;
}

void Line::parse_opcode(std::vector<std::string> &elements) {
    // Local vars
    std::string potential_opcode;
    bool op_found = false;
    size_t opcode_i;

    // Ensure that the elements vector is not empty
    if (elements.empty()) {
        return;
    }    

    // Attempt to create the OpCode object within the valid searching range
    for (size_t i = 0; ((i < MAX_OPCODE_POS) && (i < elements.size())); i++) { 
// std::cout << "\t\ttesting parse opcode " << i << " found already:" << op_found << std::endl;

        potential_opcode = elements[i];
// std::cout << "\t\t\tpot op: |" << potential_opcode.c_str() << "|" << std::endl;

        try // Try-catch to handle OpCode initalization errors
        {

// std::cout << "\t\t\tinside the try" << std::endl;
            // Test for label first
// std::cout << "\t\t\t\top:" << potential_opcode << std::endl;
// std::cout << "\t\t\t\tback:" << potential_opcode.back() << std::endl;
// std::cout << "\t\t\t\tfront:" << potential_opcode.front() << std::endl;
// std::cout << "\t\t\t\tfound:" << (op_type_map.find(potential_opcode) != op_type_map.end()) << std::endl;

            if (potential_opcode.back() == ':') {
// std::cout << "\t\t\tdetected : at end" << std::endl;
                this->opcode = std::make_shared<Label_OpCode>(potential_opcode);
                // Add the element to the list to be parsed as a pseudo op

                elements.push_back(potential_opcode.substr(0, potential_opcode.size()-1));
                // elements.push_back(potential_opcode);
// std::cout << "\t\t\tpushed " << potential_opcode.substr(0, potential_opcode.size()-1) << " back into elements" << std::endl;

                opcode_i = i;
                op_found = true;
                break;

            }   // Test for pseudo op next
            else if (potential_opcode.front() == '.') {
// std::cout << "\t\t\tfound . at front" << std::endl;
                this->opcode = std::make_shared<Pseudo_OpCode>(potential_opcode);
// std::cout << "\t\t\tpseudo op created successfully" << std::endl;
// printf("\t\t\t\tbin: %s\n\t\t\t\tstr: %s\n\t\t\t\tformat: %s\n", this->opcode->binary.c_str(), this->opcode->code_str.c_str(), this->opcode->format.c_str());
// printf("\t\t\t\tsize: %ld\n\t\t\t\tis user defed: %d\n\t\t\t\tformat: %s\n", this->opcode->size, this->opcode->is_user_defined, this->opcode->operand_info.c_str());
                opcode_i = i;
                op_found = true;
                break;

            }   // Try to find predefined OpCodes
            else if (op_type_map.find(potential_opcode) != op_type_map.end()) {
// std::cout << "\t\t\tWe got to line predefined opcode" << std::endl;
                std::string op_type = op_type_map.at(potential_opcode);
// std::cout << "\t\t\tWe got to line predefined opcode2" << std::endl;

                std::string copy = potential_opcode;

                if (op_type == "ALU") {
// std::cout << "\t\t\t\twas ALU B4" << std::endl;
    		        this->opcode = std::make_shared<ALU_OpCode>(copy);
// std::cout << "\t\t\t\twas ALU" << std::endl;
                    // break;
                }
                else if (op_type == "B") {
// std::cout << "\t\t\t\twas B B4" << std::endl;
                    
                    this->opcode = std::make_shared<B_OpCode>(copy);
// std::cout << "\t\t\t\twas B" << std::endl;
                    // break;
                }
                else if (op_type == "CTRL") {
// std::cout << "\t\t\t\twas CTRL B4" << std::endl;
                    this->opcode = std::make_shared<CTRL_OpCode>(copy);
// std::cout << "\t\t\t\twas CTRL" << std::endl;
                    // break;
                }
                else if (op_type == "MISC") {
// std::cout << "\t\t\t\twas MISC B4" << std::endl;
                    this->opcode = std::make_shared<Misc_OpCode>(copy);
// std::cout << "\t\t\t\twas MISC" << std::endl;
                    // break;
                }
                else if (op_type == "W") {
// std::cout << "\t\t\t\twas W B4" << std::endl;
                    this->opcode = std::make_shared<W_OpCode>(copy);
// std::cout << "\t\t\t\twas W" << std::endl;
                    // break;
                }
                else {  // If none of these children were detected, then set error
// std::cout << "\t\t\t\tUH OH ERROR" << std::endl;         
                    this->contains_error = true;
                    this->error_message = "OpCode child type undefined in op_type_map (see Line.cpp)";
                }
    //    elements.erase(elements.begin() + i);
                opcode_i = i;
                op_found = true;
// std::cout << "\t\t\tset op_found to true in order to break: " << op_found << std::endl;
                break;
            }   

// std::cout << "\t\t\tSKIPPED THIS OPCODE OPTION WAS NOT IT: " << op_found << std::endl;
        }
        catch(const std::exception& e)
        {
            // If there was an error in initalizing the OpCode, set error
            this->contains_error = true;
            this->error_message = e.what();
            // std::cout << "HOLY FUCK IT WAS JUST CATCHING" << std::endl;
        }

            // Set found flag and remove the OpCode from the parsed elements            

        // Exit the for loop if an OpCode was created
//         if (op_found == true) {
// std::cout << "\tWE BREAKING??\n" << std::endl;
//             break;
//         }
    }

// std::cout << "\t\t\tOMG WE OUTIE" << std::endl;

    // Set an error if no OpCode was detected
    if (op_found == false) {
        this->contains_error = true;
        this->error_message = "No OpCode or pseudo op found";
    } else {
// printf("\t\t\terased element at start + %zu\n", opcode_i);
        elements.erase(elements.begin() + opcode_i);
    }
    

    // Set line to contain user defined if true for OpCode
    if (this->opcode->get_is_user_defined()) {
// printf("\t\t\topcode was UD with bool: %d\n", this->opcode->get_is_user_defined());
        this->contains_user_defined = true;
    }

}

void Line::parse_operands(std::vector<std::string> &elements, std::string operand_info) {
    // This function assumes that parse_opcode was called before it. The correct operand_info 
    // parameter should not have been attainable without parse_opcode being called. This is why
    // it is necesarry for the user to have passed in the info parameter even though it can be
    // easily accessed with this->get_opcode()->get_operand_info().

    // Ensure that the elements vector is not empty
    if (elements.empty()) {
        return;
    }

// std::cout << elements.size() << std::endl;
// std::cout << operand_info.size() << std::endl;

// std::cout << operands.size() << std::endl;
// std::cout << operand_info.size() << std::endl;
// printf("\t\top info target: %zu vs split\n", operands_only.c_str());
    // Make sure that the operand info matches the given operand elements
    assert(operand_info.size() == elements.size());



    // We were pipelined the elements that were modified by parse_opcode, we need the full string
    std::string operands_only = join_strings(elements, " ");
// printf("\t\trecombined operands: %s\n", operands_only.c_str());
    // Now we need to parse the given elements into a vector of comma or space (exclusive) delimited operands
    std::vector<std::string> operands;
    if (operands_only.find(",") == std::string::npos) {
        operands = split_string(operands_only, ' ');
    } else {
        operands = split_string(operands_only, ',');
    }
    
// std::cout << "\t\toperand count after respliting" << operands.size() << std::endl;

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
// printf("makeing k op\n");
                this->operands.push_back(std::make_shared<Koperand>(potential_operand));
            } else if (operand_info.at(i) == 'p') {
// printf("makeing p op\n");
                this->operands.push_back(std::make_shared<Poperand>(potential_operand));
// printf("p op has bin defined as: %s with bin: %s\n", this->operands[this->operands.size()-1]->get_raw().c_str(), this->operands[this->operands.size()-1]->get_binary().c_str());
            } else {
                // If the operand type was not detected, set error
                this->contains_error = true;
                // this->error_message = "Operand type undefined in operand elif";
            }
// printf("we got thgouth no errors\n");
        }
        catch(const std::exception& e)
        {
// printf("wair hold up its actually error catching\n");
            // If there was an error in making the specific Operand, set error
            this->contains_error = true;
            this->error_message = e.what();
        }

        // Check to see if the operand contained a user defined operand
        if (this->operands[i]->get_is_user_defined()) {
            // The line should know this to facilitate processing later
// printf("The %zu operand was OD\n", i);
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

// std::cout << "\tWe are inside line init constructor\n" << std::endl;


    // Search the line for comments and remove
    // std::string copy = line;
    std::string stripped = remove_comments(line);
    stripped = trim_left(stripped);
    this->no_comments = stripped;

// std::cout << "\t\tstripped line: |" << stripped <<  "|\n" << std::endl;


    // Start parsing line
    std::vector<std::string> elements = parse_line(stripped);

// std::cout << "\tThe line has parsed good into " << elements.size() <<  " elements\n" << std::endl;

    if (elements.size() != 0) {
            

    // Define OpCode
    parse_opcode(elements);

// std::cout << "\tThe line says init opcode went good\n" << std::endl;


    // Define Operands
    std::string info = this->opcode->get_operand_info();
    parse_operands(elements, info);
    }
}


// PICHEX CALCULARION FUNCTIONS

// Function to convert binary string to an integer
unsigned long binaryStringToInt(const std::string& binaryString) {
    return std::bitset<64>(binaryString).to_ulong(); // Assuming 64-bit binary strings
}
// Function to convert an integer to a binary string
std::string intToBinaryString(unsigned long number, size_t length) {
    return std::bitset<64>(number).to_string().substr(64 - length); // Adjust to desired length
}
// Function to bitwise add binary strings
std::string bitwiseAddBinaryStrings(const std::vector<std::string>& binaryStrings) {
    if (binaryStrings.empty()) {
        return "0";
    }

    // Initialize result to 0
    unsigned long result = 0;

    // Convert each binary string to an integer and perform bitwise OR
    for (const std::string& binaryString : binaryStrings) {
        result |= binaryStringToInt(binaryString);
    }

    // Convert the result back to a binary string
    return intToBinaryString(result, binaryStrings[0].length());
}
// Utility function to convert a binary string to a hexadecimal string
std::string binaryToHex(const std::string &binary) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::stoi(binary, nullptr, 2);
    return ss.str();
}
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
    // Change to hex and to uppercase
	stream << std::hex << std::uppercase << size; // Changed to uppercase
	std::string address = stream.str();
	size_t length = address.size();
	size_t to_add = 2 - length;
	address.insert(0, to_add, '0');
	return address;
}

std::string get_checksum(uint64_t size, std::string address, std::string rec_type, std::string data){
    // Add each byte into a sum
	uint64_t sum = size;
	for (uint64_t i = 0; i < address.size(); i += 2){
		std::string sub = address.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	for (uint64_t i = 0; i < rec_type.size(); i += 2){
		std::string sub = rec_type.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	for (uint64_t i = 0; i < data.size(); i += 2){
		std::string sub = data.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
    // Mod to prevent overflow
	uint64_t modded = sum % 256;
    // Take the 2's compliment and mask filter out upper 30 bits
	uint64_t next = (~modded + 1) & 0x00000000000000FF;
    // Turn into hex string
	std::stringstream stream;
	stream << std::hex << std::uppercase << next; // Changed to uppercase
	std::string cs = stream.str();
	return cs;
}

std::string Line::to_pichex(std::unordered_map<std::string, std::string> hashmap) const {
    // PICHEX depends on five strings:
    std::string data;
    std::string byte_count;
    std::string address;
    std::string record_type;
    std::string checksum;

    // First, fetch opcode binary
    std::string opcode_bin = this->opcode->binary;

// std::cout << "We are in to pichex" << std::endl;
// printf("\topcode: %s original bin data: %s\n",this->opcode->get_code_str().c_str(),this->opcode->get_binary().c_str());

    // Next, fetch the necessary operands binaries
    std::vector<std::string> operand_bins;
    for (size_t i = 0; i < this->operands.size(); i++) {
        // Make sure to handle variable operands
        if (this->operands[i]->get_is_user_defined()) {
// std::cout << "\tFound user defined operand" << std::endl;

// printf("\t\toperand %zu original bin data: %s\n", i, this->operands[i]->get_binary().c_str());
            this->operands[i]->set_raw(hashmap[this->operands[i]->get_raw()]);
            this->operands[i]->parseRawToBinary();
        }
// printf("\t\toperand %zu after parseRawToBinary bin data: %s\n", i, this->operands[i]->get_binary().c_str());

// std::cout << "Adding binary value of :" << this->operands[i]->get_binary() << std::endl;        
        operand_bins.push_back(this->operands[i]->get_binary());
    }

    // Combine them into an overall binary string
    operand_bins.push_back(opcode_bin);
    std::string tot_bin = bitwiseAddBinaryStrings(operand_bins);

    // Convert binary to hexadecimal
// printf("\t\ttotal combined bin data: %s\n", tot_bin.c_str());
    data = binaryToHex(tot_bin);
// printf("\t\thex data: %s\n", data.c_str());


    // Ensure the length of the data string is even
    if (data.size() % 2 == 1) {
        data.insert(0, 1, '0');
    }

    // For now we will make sure each line is two bytes
    while (data.size() != 4) {
        data.insert(0, 1, '0');
    }

// printf("\t\thex data after even adjustment: %s\n", data.c_str());

    // Fill out all other params
    byte_count += get_size(data.size()/2); // depends on how many bytes of data were provided
    address = get_addr(this->memory_address);
    record_type = "00"; // This is a data record
    checksum = get_checksum(2, address, record_type, data);

    // Construct the final string (this must have a ':' prefix)
    std::string total = ":" + byte_count + address + record_type + data + checksum;
    // printf("\n\t\t\tbyte count: %s\n\t\t\taddress: %s\n\t\t\trecord type: %s\n\t\t\tdata: %s\n\t\t\tchecksum: %s\n\t\t\ttotal: %s\n", byte_count.c_str(), address.c_str(), record_type.c_str(), data.c_str(), checksum.c_str(), total.c_str());
    return total;
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
