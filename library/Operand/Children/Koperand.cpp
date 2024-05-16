#include "Koperand.hh"
#include <iostream>

// Constructor
Koperand::Koperand(const std::string &raw) : Operand(nullptr, raw) {
    setSize(8);  // Set the size to 8 bits
    setBinary(raw);  // Set the binary value to match the raw string
}

// Destructor
Koperand::~Koperand() {}

// Member functions
void Koperand::printValue() const {
    std::cout << "Koperand value: " << getRaw() << std::endl;
}
