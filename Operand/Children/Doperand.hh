// Doperand.hh

#ifndef Doperand_HH  // Include guard to prevent multiple inclusion
#define Doperand_HH

#include "Operand.hh"  // Include the parent class header file

class Doperand : public Operand<int>{
public:
    // Constructor
    Doperand();

    // Parameterized Constructor
    Doperand(int val);

    // Destructor
    ~Doperand();

    // Member functions
    // Print value method inherited from Operand
    void printValue() const;

private:
    // Member variables
    int someVariable;
};

#endif  // End of include guard