#include "Operand.hh"
#include "OpCode.hh"

// Constructor
Operand::Operand(OpCode *opcode, const std::string &raw) : opcode(opcode), raw(raw), size(0) {
    // Conversion from raw to binary could be added here if needed
}

// Destructor
Operand::~Operand() {
    // Clean up resources if necessary
}

// Accessors
uint64_t Operand::getSize() const {
    return size;
}

const std::string& Operand::getRaw() const {
    return raw;
}

const std::string& Operand::getBinary() const {
    return binary;
}

// Modifiers
void Operand::setSize(uint64_t size) {
    this->size = size;
}

void Operand::setRaw(const std::string &raw) {
    this->raw = raw;
    // Update binary value based on the new raw value if needed
}

void Operand::setBinary(const std::string &binary) {
    this->binary = binary;
}

// Inheritance
void Operand::identifyChild() const {
    std::cout << "I am an Operand" << std::endl;
}

// Print value
void Operand::printValue() const {
    std::cout << "Operand value: " << raw << std::endl;
}

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
