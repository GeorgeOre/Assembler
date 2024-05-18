#ifndef FOPERAND_HH
#define FOPERAND_HH

#include "Operand.hh"

class Foperand : public Operand {
public:
    Foperand(OpCode *opcode, const std::string &raw) : Operand(opcode, raw) {}
};

#endif

#ifndef FOPERAND_HH  // Include guard to prevent multiple inclusion
#define FOPERAND_HH

#include "Operand.hh"  // Include the parent class header file

class Foperand : public Operand {
public:
    // Constructor
    Foperand(const std::string &raw);

    // Destructor
    ~Foperand();

    // Member functions
    void printValue() const;

};

#endif  // End of include guard
