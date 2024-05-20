#ifndef OPERAND_HH
#define OPERAND_HH

#include <string>
#include <iostream>
#include <memory>

//class OpCode;  // Forward declaration of OpCode

class Operand {
protected:
    std::string raw;      // Raw string that was parsed
    std::string binary;   // Binary value in string format
    uint64_t size;        // Size of the operand in bits

public:
    Operand(const std::string& raw);
    virtual ~Operand() = default;

    // Method to parse raw operand to binary
    void parseRawToBinary();

    // Helper methods to parse different bases
    std::string parseBinary(const std::string& raw);
    std::string parseOctal(const std::string& raw);
    std::string parseDecimal(const std::string& raw);
    std::string parseHexadecimal(const std::string& raw);

    // Accessors
    uint64_t getSize() const;
    const std::string& getRaw() const;
    const std::string& getBinary() const;

    // Modifiers
    void setSize(uint64_t size);
    void setRaw(const std::string& raw);
    void setBinary(const std::string& binary);

    // Inheritance
    virtual void identifyChild() const = 0;

    // Print value
    virtual void printValue() const;

    // Equality operators
    bool operator==(const Operand &other) const {
        return raw == other.raw && size == other.size && binary == other.binary;
    }

    bool operator!=(const Operand &other) const {
        return !(*this == other);
    }
};

#endif
