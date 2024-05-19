#include "Operand.hh"
#include "Boperand.hh"
#include <iostream>

// Constructor
Boperand::Boperand(const std::string &raw) : Operand(raw) {
    setSize(3);  // Set the size to 3 bits
    setBinary(raw);  // Set the binary value to match the raw string
}

// Boperand::Boperand(const std::string &raw) : Operand(nullptr, raw) {
//     setSize(3);  // Set the size to 3 bits
//     setBinary(raw);  // Set the binary value to match the raw string
// }

// Destructor
// Boperand::~Boperand() {}

// Member functions
void Boperand::printValue() const {
    std::cout << "Boperand value: " << getRaw() << std::endl;
}
