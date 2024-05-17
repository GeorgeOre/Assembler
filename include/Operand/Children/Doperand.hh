#ifndef DOPERAND_HH
#define DOPERAND_HH

#include "Operand.hh"

class Doperand : public Operand {
public:
    Doperand(OpCode *opcode, const std::string &raw) : Operand(opcode, raw) {}
};

#endif
