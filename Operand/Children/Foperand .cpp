#include "Foperand.hh"
#include "Operand.hh"
#include <iostream>

// Default constructor definition
Foperand::Foperand() : Operand<int>(0), someVariable(0) {}

// Constructor definition with value parameter
Foperand::Foperand(int val) : Operand<int>(val), someVariable(0) {}

// Destructor
Foperand::~Foperand() {}

// Member function
// Implementation of printValue method inherited from Operand
void Foperand::printValue() const {
    std::cout << "Parent value: " << operand_get_value() << std::endl;
}
