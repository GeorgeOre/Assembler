// ValueOperand.hh
#include "Operand.hh"  // Include the parent class header file


#ifndef ValueOperand_HH  // Include guard to prevent multiple inclusion
#define ValueOperand_HH

// Declarations of classes, functions, and variables go here

class ValueOperand : public Operand<int>{
public:
    // Constructor
    ValueOperand();

    // Destructor
    ~ValueOperand();

    // Member functions
    void someFunction();

    ValueOperand(int val) : Operand(val) {}

private:
    // Member variables
    int someVariable;
};

#endif  // End of include guard