#include "Doperand.hh"
#include <iostream>

// Constructor
Doperand::Doperand(const std::string &raw) : Operand(raw) {
    setSize(1);  // Set the size to 1 bit
    setBinary(raw);  // Set the binary value to match the raw string
}

void Doperand::identifyChild() const {
    std::cout << "This is a Doperand." << std::endl;
}

void Doperand::printValue() const {
    std::cout << "Doperand - Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
