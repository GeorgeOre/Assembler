#include "Boperand.hh"
#include "Operand.hh"
#include <iostream>

// Default constructor definition
Boperand::Boperand() : Operand<int>(0), someVariable(0) {}

// Constructor definition with value parameter
Boperand::Boperand(int val) : Operand<int>(val), someVariable(0) {}

// Destructor
Boperand::~Boperand() {}

// Member function
// Implementation of printValue method inherited from Operand
void Boperand::printValue() const {
    std::cout << "Parent value: " << operand_get_value() << std::endl;
}
