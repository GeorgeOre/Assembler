#ifndef BOPERAND_HH  // Include guard to prevent multiple inclusion
#define BOPERAND_HH

#include "Operand.hh"  // Include the parent class header file

class Boperand : public Operand {
public:
    // Constructor
    Boperand(const std::string &raw);

    // Destructor
    ~Boperand();

    // Member functions
    void printValue() const;

};

#endif  // End of include guard