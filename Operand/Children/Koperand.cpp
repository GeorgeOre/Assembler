#include "Koperand.hh"
#include "Operand.hh"
#include <iostream>

// Default constructor definition
Koperand::Koperand() : Operand<int>(0), someVariable(0) {}

// Constructor definition with value parameter
Koperand::Koperand(int val) : Operand<int>(val), someVariable(0) {}

// Destructor
Koperand::~Koperand() {}

// Member function
// Implementation of printValue method inherited from Operand
void Koperand::printValue() const {
    std::cout << "Parent value: " << operand_get_value() << std::endl;
}
