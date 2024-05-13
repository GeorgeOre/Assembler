// Boperand.hh

#ifndef Boperand_HH  // Include guard to prevent multiple inclusion
#define Boperand_HH

#include "Operand.hh"  // Include the parent class header file

class Boperand : public Operand<int>{
public:
    // Constructor
    Boperand();

    // Parameterized Constructor
    Boperand(int val);

    // Destructor
    ~Boperand();

    // Member functions
    // Print value method inherited from Operand
    void printValue() const;

private:
    // Member variables
    int someVariable;
};

#endif  // End of include guard