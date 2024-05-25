#include <bitset>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <regex>
#include <cmath>
#include <unordered_set>
#include <string>

#include "Operand.hh"

#include "str_utils.hh"

// Global Constants
const std::unordered_set<std::string> supported_operations = {"+", "-", "*", "/"};

std::string padTo14Bits(const std::string& binaryString) {
    size_t length = binaryString.length();
    if (length >= 14) {
        return binaryString;
    }

    std::string paddedString = std::string(14 - length, '0') + binaryString;
    return paddedString;
}

Operand::Operand(const std::string& raw) : raw(raw), binary(""), size(0), is_user_defined(false) {
// printf("\tINSIDE OPERAND CONSTUCTOR: here is the bool for user defined %d\n", this->is_user_defined);
    parseRawToBinary();
// printf("\tINSIDE OPERAND CONSTUCTOR: here is the bool for user defined %d\n", this->is_user_defined);
}

void Operand::parseRawToBinary() {
    // Return if the string was empty
    if (this->raw.empty()) {
        return;
    }

    // Copy the string into an uppercase testing variable
    std::string tempRaw = raw;
// std::cout << "\t\tTesting " << tempRaw << std::endl;
    std::transform(tempRaw.begin(), tempRaw.end(), tempRaw.begin(), ::toupper);

    // Parse binary according to the accepted prefixes and suffixes
    if (tempRaw.find("0B") == 0) {
// printf("yep we here\n");
        this->binary = parseBinary(tempRaw.substr(2, tempRaw.size() - 2));
    } else if (tempRaw.back() == 'B') {
        this->binary = parseOctal(tempRaw.substr(0, tempRaw.size() - 1));
    
    } else if (tempRaw.find("0F") == 0) {
        this->binary = parseOctal(tempRaw.substr(2, tempRaw.size() - 2));
    } else if (tempRaw.back() == 'F') {
        this->binary = parseOctal(tempRaw.substr(0, tempRaw.size() - 1));
    
    } else if (tempRaw.find("0D") == 0) {
        this->binary = parseDecimal(tempRaw.substr(2, tempRaw.size() - 2));
    } else if (tempRaw.back() == 'D') {
        this->binary = parseDecimal(tempRaw.substr(0, tempRaw.size() - 1));
    
    } else if (tempRaw.find("0X") == 0) {
        this->binary = parseHexadecimal(tempRaw.substr(2, tempRaw.size() - 2));
    } else if (tempRaw.back() == 'H') {
        this->binary = parseHexadecimal(tempRaw.substr(0, tempRaw.size() - 1));
    
    } else if (std::regex_match(tempRaw, std::regex("^[0-9]+$"))) {
// printf("\t\t\tlooks like we are parsing a decimal value\n");
        this->binary = parseDecimal(tempRaw);
// printf("\t\t\twe ended up with %s\n", this->binary.c_str());
    } else {
        // If there was no constant number to turn into binary
        // Then it needs to be a user defined value
// printf("We are about to set this operand as user defined\n");
        this->is_user_defined = true;
    }

    // Will be 0 if it was not defined
    this->size = binary.length();

    // ADJUST BINARY TO BE 14 BITS
    this->binary = padTo14Bits(this->binary);
    

// std::cout << "SETTING CONSTURCTOR ENDING " << binary << std::endl;

}

std::string Operand::parseBinary(const std::string& binaryStr) {
    return binaryStr;
}

std::string Operand::parseOctal(const std::string& octalStr) {
    std::stringstream ss;
    ss << std::oct << octalStr;
    unsigned long n;
    ss >> n;
    return std::bitset<64>(n).to_string().substr(64 - (n > 0 ? static_cast<int>(log2(n)) + 1 : 1));
}

std::string Operand::parseDecimal(const std::string& decimalStr) {
    unsigned long n = std::stoul(decimalStr);
    return std::bitset<64>(n).to_string().substr(64 - (n > 0 ? static_cast<int>(log2(n)) + 1 : 1));
}

std::string Operand::parseHexadecimal(const std::string& hexStr) {
    std::stringstream ss;
    ss << std::hex << hexStr;
    unsigned long n;
    ss >> n;
    return std::bitset<64>(n).to_string().substr(64 - (n > 0 ? static_cast<int>(log2(n)) + 1 : 1));
}

bool is_expression(const std::string& operand) {
    // Define a set of operators
    std::unordered_set<std::string> operators = {"+", "-", "*", "/"};

    // Split the operand by spaces
    std::vector<std::string> parts = split_string(operand, ' ');
    
    // Check if any part is an operator
    for (const std::string& part : parts) {
        if (operators.find(part) != operators.end()) {
            return true;
        }
    }
    
    return false;
}

/*
        // Before handing individual operands, check for expressions

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
*/

uint64_t Operand::get_size(){
    return this->size;
}

std::string& Operand::get_raw(){
    return  this->raw;
}

std::string& Operand::get_binary(){
    return this->binary;
}

bool Operand::get_is_user_defined(){
    return this->is_user_defined;
}

void Operand::set_size(uint64_t size) {
    this->size = size;
}

void Operand::set_raw(const std::string& raw) {
    this->raw = raw;
}

void Operand::set_binary(const std::string& binary) {
    this->binary = binary;
}

void Operand::set_is_user_defined(bool result) {
    this->is_user_defined = result;
}

void Operand::set_is_expression(bool result) {
    this->is_expression = result;
}

// void Operand::printValue() const {
//     std::cout << "BASE OPERAND Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
// }