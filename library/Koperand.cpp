#include "Koperand.hh"
#include <iostream>

// Constructor
Koperand::Koperand(const std::string &raw) : Operand(raw) {
    setSize(8);  // Set the size to 8 bits
    setBinary(raw);  // Set the binary value to match the raw string
}

void Koperand::identifyChild() const {
    std::cout << "This is a Koperand." << std::endl;
}

void Koperand::printValue() const {
    std::cout << "Koperand - Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
