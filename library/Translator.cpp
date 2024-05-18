#include "Translator.hh"
#include <sstream>
#include <iterator>
#include <algorithm>  // Include algorithm for std::all_of
#include <cctype>     // Include cctype for isspace

// Static member initializations
std::unordered_map<std::string, PseudoOpCode> Translator::pseudo_op_enum;
std::unordered_map<std::string, Section> Translator::section_enum;
std::unordered_map<std::string, ConstPrefix> Translator::const_prefix_enum;
std::unordered_map<std::string, std::string> Translator::text_label_hashmap;
std::unordered_map<std::string, std::string> Translator::data_label_hashmap;
std::unordered_map<std::string, std::string> Translator::const_hashmap;

// Constructor
Translator::Translator(const std::string& inputFilePath, const std::string& outputFilePath)
    : asmFilePath(inputFilePath), outputFilePath(outputFilePath) {}

// Destructor
Translator::~Translator() {}

// Accessors
std::string Translator::get_asmFilePath() const {
    return asmFilePath;
}

std::string Translator::get_outputFilePath() const {
    return outputFilePath;
}

std::string Translator::get_errorFilePath() const {
    return errorFilePath;
}

// Mutators
void Translator::set_asmFilePath(const std::string& newInputFilePath) {
    asmFilePath = newInputFilePath;
}

void Translator::set_outputFilePath(const std::string& newOutputFilePath) {
    outputFilePath = newOutputFilePath;
}

void Translator::set_errorFilePath(const std::string& newErrorFilePath) {
    errorFilePath = newErrorFilePath;
}

// General methods
EventEnum Translator::translate(const std::string& asmFilePath) {
    this->asmFilePath = asmFilePath;
    this->outputFilePath = asmFilePath + ".out";
    this->errorFilePath = asmFilePath + ".err";

    EventEnum result = define_lines();
    if (result != EventEnum::SUCCESS) {
        return result;
    }

    first_pass();
    /*
    result = first_pass();
    if (result != EventEnum::SUCCESS) {
        return result;
    }
    */

   second_pass();
   //result = second_pass();
    
    return result;
}

EventEnum Translator::define_lines() {
    return define_lines(asmFilePath);
}

EventEnum Translator::define_lines(const std::string& filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        contains_error = true;
        return return_message(EventEnum::FILE_ERROR);
    }

    std::string line;
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
                define_lines(tokens[1]);
            } else {
                contains_error = true;
                return return_message(EventEnum::SYNTAX_ERROR);
            }
        } else {
            try {
                // Proper constructor call for Line
                lines_array.push_back(Line(0, line, OpCode(), Segment()));  
            } catch (const std::exception& e) {
                contains_error = true;
                return return_message(EventEnum::SYNTAX_ERROR);
            }
        }
    }

    inputFile.close();
    return contains_error ? return_message(EventEnum::ERROR_DETECTED) : return_message(EventEnum::SUCCESS);
}

void Translator::first_pass() {
    // Ensure lines_array is initialized
    if (lines_array.empty()) {
        contains_error = true;
        return;
    }

    // Loop through lines and store constants or labels
    for (const Line& line : lines_array) {
        // Implement the logic to store constants or labels into hashmaps
    }
}

void Translator::second_pass() {
    // Ensure lines_array is initialized
    if (lines_array.empty()) {
        contains_error = true;
        return;
    }

    // Loop through lines and translate to PICHEX format
    for (const Line& line : lines_array) {
        // Implement the translation logic
    }
}

EventEnum Translator::return_message(EventEnum event) {
    // Handle communication with the UI and return the event
    return event;
}

EventEnum Translator::make_error_file() {
    std::ofstream errorFile(errorFilePath);
    if (!errorFile.is_open()) {
        return EventEnum::FILE_ERROR;
    }

    for (const Line& line : lines_array) {
        // Write line numbers and corresponding error types to the file
    }

    errorFile.close();
    return EventEnum::SUCCESS;
}
