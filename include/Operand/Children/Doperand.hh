#ifndef DOPERAND_HH  // Include guard to prevent multiple inclusion
#define DOPERAND_HH

#include "Operand.hh"  // Include the parent class header file

class Doperand : public Operand {
public:
    // Constructor
    Doperand(const std::string &raw);

    // Destructor

    // Member functions
    void printValue() const override;

};

#endif  // End of include guard
