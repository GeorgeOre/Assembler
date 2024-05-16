#include "Line.hh"
#include <sstream>

// Constructor
Line::Line(int lineNumber, const std::string& lineContent, const OpCode& opcode, const Segment& segment)
    : line_number(lineNumber), line_content(lineContent), opcode(opcode), segment(segment) {}

// Accessors
int Line::get_line_number() const {
    return line_number;
}

std::string Line::get_line_content() const {
    return line_content;
}

OpCode Line::get_opcode() const {
    return opcode;
}

Segment Line::get_segment() const {
    return segment;
}

// Setters
void Line::set_line_number(int lineNumber) {
    line_number = lineNumber;
}

void Line::set_line_content(const std::string& lineContent) {
    line_content = lineContent;
}

void Line::set_opcode(const OpCode& opcode) {
    this->opcode = opcode;
}

void Line::set_segment(const Segment& segment) {
    this->segment = segment;
}

// Convert the line to PICHEX format
std::string Line::ToPicHEX(const OpCode& opcode, const std::vector<Operand*>& operands) {
    std::ostringstream oss;
    oss << std::hex << line_number << " "; // Convert line number to hex and add to stream
    oss << opcode.get_name();  // Assuming OpCode has a method get_name() that returns a string

    for (const Operand* operand : operands) {
        oss << " " << operand->get_binary(); // Assuming Operand has a method get_binary() that returns a string
    }

    return oss.str();
}

// Check if the line format is correct
bool Line::CheckFormat() const {
    // Implement format check logic
    // For now, let's assume a simple check where line content should not be empty
    return !line_content.empty();
}
