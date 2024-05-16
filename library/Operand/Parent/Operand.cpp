#include "Operand.hh"

// Constructor
Operand::Operand(OpCode *opcode, const string &raw)
    : opcode(opcode), size(0), raw(raw), binary("") {}

// Destructor
Operand::~Operand() {}

// Accessors
uint64_t Operand::getSize() const {
    return size;
}

const string &Operand::getRaw() const {
    return raw;
}

const string &Operand::getBinary() const { // Use camelCase
    return binary;
}

// Modifiers
void Operand::setSize(uint64_t size) {
    this->size = size;
}

void Operand::setRaw(const string &raw) {
    this->raw = raw;
}

void Operand::setBinary(const string &binary) {
    this->binary = binary;
}

// Inheritance
void Operand::identifyChild() const {
    cout << "This is an Operand" << endl;
}
