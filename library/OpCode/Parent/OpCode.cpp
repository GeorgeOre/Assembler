#include "OpCode.hh"

// Constructor
OpCode::OpCode(const std::string& name) : code(""), pichex(""), format(""), name(name) {}

// Accessors
std::string OpCode::get_hex() const {
    return pichex;
}

std::string OpCode::get_code() const {
    return code;
}

std::string OpCode::get_operands() const {
    // Assuming this should return a representation of operands
    // This can be updated based on actual operand storage and representation
    return ""; 
}

std::string OpCode::get_format() const {
    return format;
}

std::string OpCode::get_name() const {
    return name;
}
