#ifndef DOPERAND_HH
#define DOPERAND_HH

#include "Operand.hh"

class Doperand : public Operand {
public:
    Doperand(OpCode *opcode, const std::string &raw) : Operand(opcode, raw) {}
};

#endif

#ifndef DOPERAND_HH  // Include guard to prevent multiple inclusion
#define DOPERAND_HH

#include "Operand.hh"  // Include the parent class header file

class Doperand : public Operand {
public:
    // Constructor
    Doperand(const std::string &raw);

    // Destructor
    ~Doperand();

    // Member functions
    void printValue() const;

};

#endif  // End of include guard
