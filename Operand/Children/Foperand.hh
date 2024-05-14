// Foperand.hh

#ifndef Foperand_HH  // Include guard to prevent multiple inclusion
#define Foperand_HH

#include "Operand.hh"  // Include the parent class header file

class Foperand : public Operand<int>{
public:
    // Constructor
    Foperand();

    // Parameterized Constructor
    Foperand(int val);

    // Destructor
    ~Foperand();

    // Member functions
    // Print value method inherited from Operand
    void printValue() const;

private:
    // Member variables
    int someVariable;
};

#endif  // End of include guard