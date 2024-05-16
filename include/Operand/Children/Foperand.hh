#ifndef FOPERAND_HH
#define FOPERAND_HH

#include "Operand.hh"

class Foperand : public Operand {
public:
    // Constructor
    Foperand(OpCode *opcode, const string &raw) : Operand(opcode, raw) {
        setSize(3); // Example: Set size to 3 bits
        setBinary("binary_value"); // Set binary value based on raw
    }

    // Festructor
    virtual ~Foperand() {}

    // Override identifyChild
    virtual void identifyChild() const override {
        cout << "This is a Foperand" << endl;
    }
};

#endif
