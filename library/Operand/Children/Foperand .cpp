#include "Foperand.hh"
#include <iostream>

// Constructor
Foperand::Foperand(const std::string &raw) : Operand(nullptr, raw) {
    setSize(3);
    setBinary(raw);
}

// Destructor
Foperand::~Foperand() {}

// Functions
void Foperand::printValue() const {
    std::cout << "Foperand value: " << getRaw() << std::endl;
}
