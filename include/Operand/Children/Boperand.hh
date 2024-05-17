#ifndef BOPERAND_HH
#define BOPERAND_HH

#include "Operand.hh"

class Boperand : public Operand {
public:
    Boperand(OpCode *opcode, const std::string &raw) : Operand(opcode, raw) {}
};

#endif
