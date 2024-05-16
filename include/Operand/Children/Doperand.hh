#ifndef DOPERAND_HH
#define DOPERAND_HH

#include "Operand.hh"

class Doperand : public Operand {
public:
    // Constructor
    Doperand(OpCode *opcode, const string &raw) : Operand(opcode, raw) {
        setSize(3); // Example: Set size to 3 bits
        setBinary("binary_value"); // Set binary value based on raw
    }

    // Destructor
    virtual ~Doperand() {}

    // Override identifyChild
    virtual void identifyChild() const override {
        cout << "This is a Doperand" << endl;
    }
};

#endif
