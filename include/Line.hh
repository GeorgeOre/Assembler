// Line.hh
#ifndef LINE_HH
#define LINE_HH

#include <string>
#include <vector>
#include <memory>
#include "OpCode.hh"
#include "Operand.hh"

class Line {
private:

public:
    int lineNumber;
    int programMemoryAddress;
    std::string section;
    std::string raw_line;
    OpCode opcode;
    std::vector<std::shared_ptr<Operand>> operands;
    bool containsError;
    std::string errorMessage;

    Line(int lineNumber, const std::string& section, const std::string& line);

    void parseLine(const std::string& line);

    // Accessors
    int getLineNumber() const;
    int getProgramMemoryAddress() const;
    const std::string& getSection() const;
    const OpCode& getOpCode() const;
    const std::vector<std::shared_ptr<Operand>>& getOperands() const;
    bool hasError() const;
    const std::string& getErrorMessage() const;

    // Setters
    void setProgramMemoryAddress(int address);
};

#endif // LINE_HH
