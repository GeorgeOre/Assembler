#include <bitset>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <regex>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <functional>

#include "Operand.hh"

#include "str_utils.hh"

// Global Constants
const std::unordered_set<std::string> supported_operations = {"+", "-", "*", "/"};

// Forward declarations
bool contains_expression(const std::string& operand);

// Constant handling
std::unordered_map<std::string, std::function<std::string(const std::string&)>> Operand::prefix_map = {
    {"0B", Operand::parseBinary}, {"0b", Operand::parseBinary},
    {"0F", Operand::parseOctal}, {"0f", Operand::parseOctal},
    // {"0D", Operand::parseDecimal}, {"0d", Operand::parseDecimal},
    // {"", Operand::parseDecimal}, ALT VERSION OF DECIMAL
    {"0X", Operand::parseHexadecimal}, {"0x", Operand::parseHexadecimal}
};

std::unordered_map<std::string, std::function<std::string(const std::string&)>> Operand::suffix_map = {
    {"B", Operand::parseBinary}, {"b", Operand::parseBinary},
    {"F", Operand::parseOctal}, {"f", Operand::parseOctal},
    // {"D", Operand::parseDecimal}, {"d", Operand::parseDecimal},
    // {"", Operand::parseDecimal}, ALT VERSION OF DECIMAL
    {"H", Operand::parseHexadecimal}, {"h", Operand::parseHexadecimal}
};

// Util functions
std::string padTo14Bits(const std::string& binaryString) {
    size_t length = binaryString.length();
    if (length >= 14) {
        return binaryString;
    }

    std::string paddedString = std::string(14 - length, '0') + binaryString;
    return paddedString;
}

// Constructor
Operand::Operand(const std::string& raw) : raw(raw), binary(""), size(0), is_user_defined(false), is_expression(false) {
// printf("INSIDE OPERAND CONSTRUCTOR\n");
    // Before handing individual operands, check for expressions
    if (contains_expression(raw)) {
// printf("\tOperand %s contained expression so binary will not be parsed\n", raw.c_str());
        this->is_expression = contains_expression(raw);
    } else {
// printf("\tOperand %s NOT contained expression\n", raw.c_str());

// printf("\tINSIDE OPERAND CONSTUCTOR: here is the bool for user defined %d\n", this->is_user_defined);
        parseRawToBinary();
// printf("\tINSIDE OPERAND CONSTUCTOR: here is the bool for user defined %d\n", this->is_user_defined);
    }
}

// Constructor Helpers

bool contains_expression(const std::string& operand) {
    // Split the operand by spaces
    std::vector<std::string> parts = split_string(operand, ' ');
    
    // Check if any part is an operator
    for (const std::string& part : parts) {
        if (supported_operations.find(part) != supported_operations.end()) {
            return true;
        }
    }
    
    return false;
}



void Operand::parseRawToBinary() {
    // Return if the string was empty
    if (this->raw.empty()) {
        return;
    }

    // Copy the string into an uppercase testing variable
    std::string tempRaw = raw;
// std::cout << "\t\tTesting parse raw to bin:  |" << tempRaw << "|" << std::endl;
    std::transform(tempRaw.begin(), tempRaw.end(), tempRaw.begin(), ::toupper);
std::cout << "\t\tTesting parse transfoemed upper to bin:  |" << tempRaw << "|" << std::endl;


// THIS IS FOR SUFFIX HANDLING
// Fetch the last character
    char last_char = tempRaw.back();
    std::string last_char_str(1, last_char); // Convert char to string


    // Process immediate constant values
    if (std::regex_match(tempRaw, std::regex("^[0-9]+$"))) {
printf("\t\t\tlooks like we are parsing a decimal value\n");
        // If the value is only digits, default to parse decimal
        this->binary = parseDecimal(tempRaw);
    // printf("\t\t\twe ended up with %s\n", this->binary.c_str());
    }    
    // Now check for constants with supported prefixes
    else if (std::regex_match(tempRaw, std::regex("^0.[0-9,A-F,a-f]+$"))) {
printf("\t\t\tlooks like we are parsing a PREFIX value\n");
        for (const auto& [prefix, func] : prefix_map) {
            if (tempRaw.find(prefix) == 0) {
                this->binary = func(tempRaw);
                // this->binary = func(tempRaw.substr(prefix.size()));
                // return;
            }
        }
    }
    // Suffixes next
    else if (suffix_map.find(last_char_str) != suffix_map.end()
        && std::regex_match(tempRaw, std::regex("^[0-9,A-F,a-f]+.$")) ) {
printf("\t\t\tlooks like we are parsing a SUFFIX value\n");
        for (const auto& [suffix, func] : suffix_map) {
            if (tempRaw.find(suffix) == tempRaw.size()-1) {
printf("\t\t\t\tWe found suffix %s and we parsing %s\n", suffix.c_str(), tempRaw.c_str());
                this->binary = func(tempRaw);
                // this->binary = func(tempRaw.substr(0, suffix.size()-1));
                // return;
            }
        }
// OLD VERSION
//     else if (std::regex_match(tempRaw, std::regex("^[0-9,A-F,a-f]+.$"))) {
// printf("\t\t\tlooks like we are parsing a SUFFIX value\n");
//         for (const auto& [suffix, func] : suffix_map) {
//             if (tempRaw.find(suffix) == 0) {
//                 this->binary = func(tempRaw.substr(suffix.size()));
//                 // return;
//             }
//         }
    } else {
        // If there was no constant number to turn into binary,
        // then it needs to be a user defined value
        this->is_user_defined = true;
printf("We have set this operand as user defined\n");
    }

    // Will be 0 if it was not defined
    this->size = binary.length();

    // ADJUST BINARY TO BE 14 BITS
    this->binary = padTo14Bits(this->binary);
    
printf("\t\t\tEND we ended up with %s\n", this->binary.c_str());
// std::cout << "SETTING CONSTURCTOR ENDING " << binary << std::endl;

}

std::string Operand::parseBinary(const std::string& binaryStr) {
    // Check if the string starts with "0x" and remove it if present
    std::string cleanBinaryStr = binaryStr;
    if (binaryStr.rfind("0b", 0) == 0 || binaryStr.rfind("0B", 0) == 0) {
        cleanBinaryStr = binaryStr.substr(2);
    }
    // Same thing for the suffix
    if (binaryStr.rfind("B", binaryStr.size()-1) == 0 || binaryStr.rfind("b", binaryStr.size()-1) == 0) {
        cleanBinaryStr = binaryStr.substr(0, binaryStr.size()-1);
    }

    return cleanBinaryStr;
}

std::string Operand::parseOctal(const std::string& octalStr) {
    // Check if the string starts with "0x" and remove it if present
    std::string cleanOctalStr = octalStr;
    if (octalStr.rfind("0x", 0) == 0 || octalStr.rfind("0X", 0) == 0) {
        cleanOctalStr = octalStr.substr(2);
    }
    // Same thing for the suffix
    if (octalStr.rfind("H", octalStr.size()-1) == 0 || octalStr.rfind("h", octalStr.size()-1) == 0) {
        cleanOctalStr = octalStr.substr(0, octalStr.size()-1);
    }
    
    // Convert octal string to unsigned long
    std::stringstream ss;
    ss << std::oct << cleanOctalStr;
    unsigned long n;
    ss >> n;

    // Calculate the number of bits needed to represent the number
    int numBits = n > 0 ? static_cast<int>(log2(n)) + 1 : 1;

    // Ensure a minimum bit length, e.g., 14 bits for the specific use case
    const int minBitLength = 14;
    numBits = std::max(numBits, minBitLength);

    // Convert to binary string of appropriate length
    std::string binaryString = std::bitset<64>(n).to_string().substr(64 - numBits);

    return binaryString;
}

std::string Operand::parseDecimal(const std::string& decimalStr) {
    // Convert decimal string to unsigned long
    unsigned long n = std::stoul(decimalStr);

    // Calculate the number of bits needed to represent the number
    int numBits = n > 0 ? static_cast<int>(log2(n)) + 1 : 1;

    // Ensure a minimum bit length, e.g., 14 bits for the specific use case
    const int minBitLength = 14;
    numBits = std::max(numBits, minBitLength);

    // Convert to binary string of appropriate length
    std::string binaryString = std::bitset<64>(n).to_string().substr(64 - numBits);
// printf("\tIn parseDecimal: %s\n", binaryString.c_str());
    return binaryString;
}

std::string Operand::parseHexadecimal(const std::string& hexStr) {

// printf("\tIn parseHex: %s\n", hexStr.c_str());
    // Check if the string starts with "0x" and remove it if present
    std::string cleanHexStr = hexStr;
    if (hexStr.rfind("0x", 0) == 0 || hexStr.rfind("0X", 0) == 0) {
        cleanHexStr = hexStr.substr(2);
    }
    // Same thing for the suffix
    if (hexStr.rfind("H", hexStr.size()-1) == 0 || hexStr.rfind("h", hexStr.size()-1) == 0) {
        cleanHexStr = hexStr.substr(0, hexStr.size()-1);
    }
// printf("\tIn parseHex: %s\n", cleanHexStr.c_str());
    // Convert hexadecimal string to unsigned long
    std::stringstream ss;
    ss << std::hex << cleanHexStr;
    unsigned long n;
    ss >> n;
// printf("\tIn parseHex: %s\n", cleanHexStr.c_str());
    // Calculate the number of bits needed to represent the number
    int numBits = n > 0 ? static_cast<int>(log2(n)) + 1 : 1;

    // Ensure a minimum bit length, e.g., 14 bits for the specific use case
    const int minBitLength = 14;
    numBits = std::max(numBits, minBitLength);

    // Convert to binary string of appropriate length
    std::string binaryString = std::bitset<64>(n).to_string().substr(64 - numBits);
// printf("\tIn parseHex: %s\n", binaryString.c_str());
    return binaryString;
}



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

bool Operand::get_is_expression(){
    return this->is_expression;
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
