
#include "Doperand.hh"
#include <iostream>

// Constructor
Doperand::Doperand(const std::string &raw) : Operand(nullptr, raw) {
    setSize(1);  // Set the size to 1 bit
    setBinary(raw);  // Set the binary value to match the raw string
}

// Destructor
Doperand::~Doperand() {}

// Member functions
void Doperand::printValue() const {
    std::cout << "Doperand value: " << getRaw() << std::endl;
}
