#include "Doperand.hh"
#include "Operand.hh"
#include <iostream>

// Default constructor definition
Doperand::Doperand() : Operand<int>(0), someVariable(0) {}

// Constructor definition with value parameter
Doperand::Doperand(int val) : Operand<int>(val), someVariable(0) {}

// Destructor
Doperand::~Doperand() {}

// Member function
// Implementation of printValue method inherited from Operand
void Doperand::printValue() const {
    std::cout << "Parent value: " << operand_get_value() << std::endl;
}
