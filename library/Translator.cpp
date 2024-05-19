#include "Translator.hh"

#include "Line.hh"
#include "OpCode.hh"

#include <sstream>
#include <iterator>
#include <algorithm>  // Include algorithm for std::all_of
#include <cctype>     // Include cctype for isspace
#include <stdexcept>  // Include error handling lib

#include <list>

// Static member initializations
// std::unordered_map<std::string, PseudoOpCode> Translator::pseudo_op_enum;
std::unordered_map<std::string, Section> Translator::section_enum;
std::unordered_map<std::string, ConstPrefix> Translator::const_prefix_enum;
std::unordered_map<std::string, std::string> Translator::text_label_hashmap;
std::unordered_map<std::string, std::string> Translator::data_label_hashmap;
std::unordered_map<std::string, std::string> Translator::const_hashmap;

// Constructor
Translator::Translator() {
    // Later add some default paths or somthing
    throw std::invalid_argument("Please make sure that you init traslator with file paths");
}

Translator::Translator(const std::string& inputFilePath, const std::string& outputFilePath)
    : asmFilePath(inputFilePath), outputFilePath(outputFilePath) {}

// Destructor
Translator::~Translator() {}

// Accessors
std::string Translator::get_asmFilePath() const {
    return this->asmFilePath;
}

std::string Translator::get_outputFilePath() const {
    return this->outputFilePath;
}

std::string Translator::get_errorFilePath() const {
    return this->errorFilePath;
}

// FOR TESTING ONLY
std::vector<Line> Translator::get_lines_array(){
    return this->lines_array;
}


// Mutators
void Translator::set_asmFilePath(const std::string& newInputFilePath) {
    this->asmFilePath = newInputFilePath;
}

void Translator::set_outputFilePath(const std::string& newOutputFilePath) {
    this->outputFilePath = newOutputFilePath;
}

void Translator::set_errorFilePath(const std::string& newErrorFilePath) {
    this->errorFilePath = newErrorFilePath;
}

// General methods
EventEnum Translator::define_lines() {
    
    std::ifstream inputFile(this->asmFilePath);
    if (!inputFile.is_open()) {
        contains_error = true;
        return EventEnum::FILE_ERROR;
        // return return_message(EventEnum::FILE_ERROR);
    }

    std::string line;
    u_int64_t cur_num = 1;
    while (std::getline(inputFile, line)) {
        // Skip empty or comment lines
        if (line.empty() || line[0] == '#' || std::all_of(line.begin(), line.end(), [](unsigned char c){ return std::isspace(c); })) {
            continue;
        }

        // Handle .include directive separately
        if (line.find(".include") != std::string::npos) {
            // Parse include file path and call define_lines recursively
            std::istringstream iss(line);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
            if (tokens.size() == 2) {
                //define_lines(tokens[1]);
            } else {
                contains_error = true;
                return EventEnum::FILE_ERROR;
                // return return_message(EventEnum::SYNTAX_ERROR);
            }
        } else {
            try {
                // Proper constructor call for Line
                lines_array.push_back(Line(cur_num, 0, line, Segment()));  
            } catch (const std::exception& e) {
                // contains_error = true;
                // return return_message(EventEnum::SYNTAX_ERROR);
                Line error_line = Line(cur_num, 0, line, Segment());
                error_line.contains_error = true;
                lines_array.push_back(error_line);

            }
        }
        cur_num++;
    }

    inputFile.close();
    return contains_error ? EventEnum::ERROR_DETECTED : EventEnum::SUCCESS;
}

EventEnum Translator::first_pass() {
    // Ensure lines_array is initialized
    if (lines_array.empty()) {
        contains_error = true;
        return EventEnum::ERROR_DETECTED;
    }

    // Loop through lines and store constants or labels
    for (const Line& line : lines_array) {
        // Get essential testing values
        //  OpCode code = line.opcode;
        //  list<Operand> operands = code.operands;
        //  uint64_t num_operands = (uint64_t)operands.size();

        int num_operands = 1;
        // Our first test will categorize each line by how many operands it has
        if (num_operands == 0) {
            // Check if the OpCode is a pseudo op
            if (false)//code.is_pseudo_op())
            {
                // Handle section change pseudo op
                if ( false){//code.get_code().compare(".text") | code.get_code().compare(".data") ) {
                    // Set translator to now define labels in the newly set section/segment
                } 
                // Handle label pseudo op            
                else {
                    // Store that label in the right map
                }                
            }
            else {
                // If it is not a pseudo op, then we need not store anything
                    // Handle OpCodes 
                    //  NOP
                    //  RETURN
                    //  RETFIE
                    //  OPTION
                    //  SLEEP
                    //  CLRWDT
            }
        } else if (num_operands == 1) {
            // Now it will look to handle lines that have only one operand

            // Check if the OpCode is a pseudo op
            if (false)//code.is_pseudo_op())
            {
                // Handle variable definition pseudo op
                if (false){// code.get_code().compare(".text") | code.get_code().compare(".data") ) {
                // if (line.get_opcode() == Segment) {
                    // Add variables to variable map and assign it a memory address
                } 
                // Handle constant definition pseudo op
                else {
                    // Add the constant and its value to the corresponding map
                }                
            }
            // else {
            //     // If it is not a pseudo op, then we need not store anything
            // }
        } else {
            // All other cases have two operands
            // There are no pseudo ops with two operands so we do not need to store anything
        }       
    }
}

EventEnum Translator::second_pass() {
    // Ensure lines_array is initialized
    if (lines_array.empty()) {
        contains_error = true;
        return EventEnum::ERROR_DETECTED;
    }

    // Open the output file
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        return EventEnum::FILE_ERROR;
    }

    // Loop through lines
    for (const Line& line : lines_array) {
        // Assign addresses to each line
        //line.set_address();
        // Translate to PICHEX format and add to the file
        //outputFile << line.to_pichex() << "\n";

    }

    // Close file and report successs
    outputFile.close();
    return EventEnum::SUCCESS;  // can add a ? erorr check return
}

void Translator::receive_message(EventEnum event) {
    // Handle communication with the UI and return the event
    this->message = event;
}

EventEnum Translator::return_message() {
    // Handle communication with the UI and return the event
    return message;
}

EventEnum Translator::make_error_file() {
    // This function should not be implemented
    return EventEnum::ERROR_DETECTED;
}
