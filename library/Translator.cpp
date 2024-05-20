#include "Translator.hh"
#include <sstream>

// Initialize static members
std::unordered_map<std::string, Section> Translator::section_enum;
std::unordered_map<std::string, ConstPrefix> Translator::const_prefix_enum;
std::unordered_map<std::string, std::string> Translator::text_label_hashmap;
std::unordered_map<std::string, std::string> Translator::data_label_hashmap;
std::unordered_map<std::string, std::string> Translator::const_hashmap;

Translator::Translator(const std::string& inputPath, const std::string& outputPath)
    : asmFilePath(inputPath), outputFilePath(outputPath), contains_error(false) {}

Translator::~Translator() {}

std::string Translator::get_asmFilePath() const {
    return asmFilePath;
}

std::string Translator::get_outputFilePath() const {
    return outputFilePath;
}

std::string Translator::get_errorFilePath() const {
    return errorFilePath;
}

std::vector<Line> Translator::get_lines_array() {
    return lines_array;
}

void Translator::set_asmFilePath(const std::string& newInputFilePath) {
    asmFilePath = newInputFilePath;
}

void Translator::set_outputFilePath(const std::string& newOutputFilePath) {
    outputFilePath = newOutputFilePath;
}

void Translator::set_errorFilePath(const std::string& newErrorFilePath) {
    errorFilePath = newErrorFilePath;
}

EventEnum Translator::define_lines() {
    // Implementation
    return EventEnum::SUCCESS;
}

EventEnum Translator::first_pass() {
    // Implementation
    return EventEnum::SUCCESS;
}

EventEnum Translator::second_pass() {
    // Implementation
    return EventEnum::SUCCESS;
}

void Translator::write_output() {
    // Implementation
}

void Translator::receive_message(EventEnum event) {
    // Implementation
    this->message = event;
}

EventEnum Translator::return_message() {
    // Implementation
    return EventEnum::SUCCESS;
}

EventEnum Translator::make_error_file() {
    // Implementation
    return EventEnum::SUCCESS;
}
