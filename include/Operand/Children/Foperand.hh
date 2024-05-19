#ifndef FOPERAND_HH  // Include guard to prevent multiple inclusion
#define FOPERAND_HH

#include "Operand.hh"  // Include the parent class header file

class Foperand : public Operand {
public:
    // Constructor
    Foperand(const std::string &raw);

    // Destructor

    // Member functions
    void printValue() const override;

};

#endif  // End of include guard
