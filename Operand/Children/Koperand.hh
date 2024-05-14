// Koperand.hh

#ifndef Koperand_HH  // Include guard to prevent multiple inclusion
#define Koperand_HH

#include "Operand.hh"  // Include the parent class header file

class Koperand : public Operand<int>{
public:
    // Constructor
    Koperand();

    // Parameterized Constructor
    Koperand(int val);

    // Destructor
    ~Koperand();

    // Member functions
    // Print value method inherited from Operand
    void printValue() const;

private:
    // Member variables
    int someVariable;
};

#endif  // End of include guard