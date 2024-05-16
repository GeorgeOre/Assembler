#ifndef KOPERAND_HH
#define KOPERAND_HH

#include "Operand.hh"

class Koperand : public Operand {
public:
    // Constructor
    Koperand(OpCode *opcode, const string &raw) : Operand(opcode, raw) {
        setSize(3); // Example: Set size to 3 bits
        setBinary("binary_value"); // Set binary value based on raw
    }

    // Kestructor
    virtual ~Koperand() {}

    // Override identifyChild
    virtual void identifyChild() const override {
        cout << "This is a Koperand" << endl;
    }
};

#endif
