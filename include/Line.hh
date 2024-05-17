#ifndef LINE_HH
#define LINE_HH

#include <string>
#include <vector>
#include "OpCode.hh"
#include "Segment.hh"
#include "Operand.hh" // Include Operand

class Line {
public:
    Line(int lineNumber, const std::string& lineContent, const OpCode& opcode, const Segment& segment);

    int get_line_number() const;
    std::string get_line_content() const;
    OpCode get_opcode() const;
    Segment get_segment() const;

    void set_line_number(int lineNumber);
    void set_line_content(const std::string& lineContent);
    void set_opcode(const OpCode& opcode);
    void set_segment(const Segment& segment);

    std::string ToPicHEX(const OpCode& opcode, const std::vector<Operand*>& operands);
    bool CheckFormat() const;

private:
    int line_number;
    std::string line_content;
    OpCode opcode;
    Segment segment;
};

#endif
