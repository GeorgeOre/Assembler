// Operand.cpp

#include "Operand.hh"
#include <iostream>

// Constructors
template<typename O>
Operand<O>::Operand() : size(0), raw(""), value(0) {}

// Parameterized constructor
template<typename O>
Operand<O>::Operand(int size, string raw, O value): 
    size(size), raw(raw), value(value) {}

// Destructor
template<typename O>
Operand<O>::~Operand(){}


// Member functions
template<typename O>
Parent(const O& val) : value(val) {}
void printValue() {
    std::cout << "Parent value: " << this.value << std::endl;
}

// Accessors and modifiers
template<typename O>
int Operand<O>::operand_get_size() const {
    return size;
}

template<typename O>
string Operand<O>::operand_get_raw() const {
    return raw;
}

template<typename O>
O Operand<O>::operand_get_value() const {
    return value;
}

template<typename O>
void Operand<O>::operand_set_size(int size) {
    this->size = size;
}

template<typename O>
void Operand<O>::operand_set_raw(const string& raw) {
    this->raw = raw;
}

template<typename O>
void Operand<O>::operand_set_value(const O& value) {
    this->value = value;
}