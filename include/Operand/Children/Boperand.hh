#ifndef BOPERAND_HH
#define BOPERAND_HH

#include "Operand.hh"

class Boperand : public Operand {
public:
    // Constructor
    Boperand(OpCode *opcode, const string &raw) : Operand(opcode, raw) {
        setSize(3); // Example: Set size to 3 bits
        setBinary("binary_value"); // Set binary value based on raw
    }

    // Destructor
    virtual ~Boperand() {}

    // Override identifyChild
    virtual void identifyChild() const override {
        cout << "This is a Boperand" << endl;
    }
};

#endif
