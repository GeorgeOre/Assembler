
#include "Foperand.hh"
#include <iostream>

// Constructor
Foperand::Foperand(const std::string &raw) : Operand(nullptr, raw) {
    setSize(7);  // Set the size to 7 bits
    setBinary(raw);  // Set the binary value to match the raw string
}

// Destructor
Foperand::~Foperand() {}

// Member functions
void Foperand::printValue() const {
    std::cout << "Foperand value: " << getRaw() << std::endl;
}
