#include "Doperand.hh"
#include <iostream>

// Constructor
Doperand::Doperand(const std::string &raw) : Operand(nullptr, raw) {
    setSize(3);  // Set the size to 3 bits
    setBinary(raw);  // Set the binary value to match the raw string
}

// Destructor
Doperand::~Doperand() {}

// Member functions
void Doperand::printValue() const {
    std::cout << "Doperand value: " << getRaw() << std::endl;
}