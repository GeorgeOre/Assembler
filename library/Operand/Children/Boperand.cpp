//#include "Boperand.hh"
#include "../../../include/Operand/Children/Boperand.hh"

// No additional implementation needed if constructor and identifyChild are defined in the header

#include "Boperand.hh"
#include <iostream>

// Constructor
Boperand::Boperand(const std::string &raw) : Operand(nullptr, raw) {
    setSize(3);  // Set the size to 3 bits
    setBinary(raw);  // Set the binary value to match the raw string
}

// Destructor
Boperand::~Boperand() {}

// Member functions
void Boperand::printValue() const {
    std::cout << "Boperand value: " << getRaw() << std::endl;
}
