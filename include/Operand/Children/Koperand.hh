#ifndef KOPERAND_HH  // Include guard to prevent multiple inclusion
#define KOPERAND_HH

#include "Operand.hh"  // Include the parent class header file

class Koperand : public Operand {
public:
    // Constructor
    Koperand(const std::string &raw);

    // Destructor

    // Member functions
    void printValue() const override;

};

#endif  // End of include guard
