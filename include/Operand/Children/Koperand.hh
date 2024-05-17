#ifndef KOPERAND_HH
#define KOPERAND_HH

#include "Operand.hh"

class Koperand : public Operand {
public:
    Koperand(OpCode *opcode, const std::string &raw) : Operand(opcode, raw) {}
};

#endif
