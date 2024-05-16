#ifndef OPCODE_HH
#define OPCODE_HH

#include <string>

class OpCode {
public:
    // Constructor
    OpCode(const std::string& name = "");

    // Accessors
    std::string get_hex() const;
    std::string get_code() const;
    std::string get_operands() const;
    std::string get_format() const;
    std::string get_name() const; // Add this method

private:
    std::string code;
    std::string pichex;
    std::string format;
    std::string name; // Add this member
};

#endif
