#include "PseudoOpCode.hh"

// Initialize the static member
std::unordered_map<std::string, PseudoOpCode> PseudoOpCode::pseudo_op_codes;

// Constructor
PseudoOpCode::PseudoOpCode(const std::string& name) : name(name) {}

// Get the name
std::string PseudoOpCode::get_name() const {
    return name;
}

// Get a PseudoOpCode by name
const PseudoOpCode& PseudoOpCode::get(const std::string& name) {
    return pseudo_op_codes.at(name);
}

// Add a new PseudoOpCode
void PseudoOpCode::add(const std::string& name) {
    pseudo_op_codes.emplace(name, PseudoOpCode(name));
}
