#include "Operand.hh"
#include "OpCode.hh"

// Constructor
Operand::Operand(OpCode *opcode, const string &raw)
    : opcode(opcode), raw(raw), size(0), binary("") {}

// Destructor
Operand::~Operand() {}

// Accessors
uint64_t Operand::getSize() const {
    return size;
}

const string &Operand::getRaw() const {
    return raw;
}

const string &Operand::getBinary() const {
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
    // Example implementation, to be customized based on actual child classes
    cout << "Unknown operand type" << endl;
}
