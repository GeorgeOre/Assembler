#ifndef KOPERAND_HH
#define KOPERAND_HH

#include "Operand.hh"

class Koperand : public Operand {
public:
    Koperand(OpCode *opcode, const std::string &raw) : Operand(opcode, raw) {}
};

#endif

#ifndef KOPERAND_HH  // Include guard to prevent multiple inclusion
#define KOPERAND_HH

#include "Operand.hh"  // Include the parent class header file

class Koperand : public Operand {
public:
    // Constructor
    Koperand(const std::string &raw);

    // Destructor
    ~Koperand();

    // Member functions
    void printValue() const;

};

#endif  // End of include guard
