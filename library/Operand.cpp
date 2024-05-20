#include <bitset>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <regex>
#include <cmath>

#include "Operand.hh"

Operand::Operand(const std::string& raw) : raw(raw), binary(""), size(0) {
    parseRawToBinary();
}

void Operand::parseRawToBinary() {
    // printf("we parsing to binary\n");
    // Return if the string was empty
    if (raw.empty()) {
        return;
    }

    // Copy the string into an uppercase testing variable
    std::string tempRaw = raw;
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
        this->binary = parseDecimal(tempRaw);
    }

    size = binary.length();

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

uint64_t Operand::getSize() const {
    return size;
}

const std::string& Operand::getRaw() const {
    return raw;
}

const std::string& Operand::getBinary() const {
    return binary;
}

void Operand::setSize(uint64_t size) {
    this->size = size;
}

void Operand::setRaw(const std::string& raw) {
    this->raw = raw;
}

void Operand::setBinary(const std::string& binary) {
    this->binary = binary;
}

void Operand::printValue() const {
    std::cout << "Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
