#ifndef FOPERAND_HH
#define FOPERAND_HH

#include "Operand.hh"

class Foperand : public Operand {
public:
    Foperand(OpCode *opcode, const std::string &raw) : Operand(opcode, raw) {}
};

#endif
