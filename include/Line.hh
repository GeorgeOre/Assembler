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
    int memoryAddress;

    std::string file_info;

    std::string section;
    
    std::string raw_line;
    
    OpCode opcode;
    std::vector<std::shared_ptr<Operand>> operands;
    
    bool user_defined;

    bool containsError;
    std::string errorMessage;

    // Constructors
    Line(int lineNumber, const std::string& section, const std::string& line, const std::string& f_info);

    // Parse?
    void parseLine(const std::string& line);

    // Return pixhex
    std::string& to_pichex() const;

    // Accessors
    int getLineNumber() const;
    int getMemoryAddress() const;
    const std::string& getSection() const;
    const std::string& getRawStr() const;
    const OpCode& getOpCode() const;
    const std::vector<std::shared_ptr<Operand>>& getOperands() const;
    bool hasError() const;
    bool is_user_defined() const;
    const std::string& getErrorMessage() const;

    // Setters
    void setMemoryAddress(int address);
};

#endif // LINE_HH
