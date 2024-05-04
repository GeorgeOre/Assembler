// IndexOperand.hh
#include "Operand.hh"  // Include the parent class header file

#ifndef IndexOperand_HH  // Include guard to prevent multiple inclusion
#define IndexOperand_HH

// Declarations of classes, functions, and variables go here

class IndexOperand : public Operand{
public:
    // Constructor
    IndexOperand();

    // Destructor
    ~IndexOperand();

    // Member functions
    void someFunction();

private:
    // Member variables
    int someVariable;
};

#endif  // End of include guard