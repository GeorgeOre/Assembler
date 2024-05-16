#include "Translator.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

// Static member initializations
std::unordered_map<std::string, OpCode> Translator::op_code_enum;
std::unordered_map<std::string, PseudoOpCode> Translator::pseudo_op_enum;
std::unordered_map<std::string, Section> Translator::section_enum;
std::unordered_map<std::string, ConstPrefix> Translator::const_prefix_enum;
std::unordered_map<std::string, std::string> Translator::text_label_hashmap;
std::unordered_map<std::string, std::string> Translator::data_label_hashmap;
std::unordered_map<std::string, std::string> Translator::const_hashmap;

// Constructor
Translator::Translator(const std::string& inputFilePath, const std::string& outputFilePath)
    : input_file_path(inputFilePath), output_file_path(outputFilePath) {}

// Destructor
Translator::~Translator() {}

// Accessors
std::string Translator::get_input_file_path() const {
    return input_file_path;
}

std::string Translator::get_output_file_path() const {
    return output_file_path;
}

std::string Translator::get_error_file_path() const {
    return error_file_path;
}

// Mutators
void Translator::set_input_file_path(const std::string& newInputFilePath) {
    input_file_path = newInputFilePath;
}

void Translator::set_output_file_path(const std::string& newOutputFilePath) {
    output_file_path = newOutputFilePath;
}

void Translator::set_error_file_path(const std::string& newErrorFilePath) {
    error_file_path = newErrorFilePath;
}

// General methods
EventEnum Translator::define_lines() {
    return define_lines(input_file_path);
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
        if (line.empty() || line[0] == '#' || std::all_of(line.begin(), line.end(), isspace)) {
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
                lines_array.push_back(Line(line));  // Assuming Line has a constructor that takes a string
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
    std::ofstream errorFile(error_file_path);
    if (!errorFile.is_open()) {
        return EventEnum::FILE_ERROR;
    }

    for (const Line& line : lines_array) {
        // Write line numbers and corresponding error types to the file
    }

    errorFile.close();
    return EventEnum::SUCCESS;
}
