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
    bool is_user_defined;   // Boolean that represents if the operand is user defined

public:
    Operand(const std::string& raw);
    // virtual ~Operand() = default;

    // Accessors and modifiers
    uint64_t get_size() const;
    const std::string& get_raw() const;
    const std::string& get_binary() const;
    bool is_user_defined;
    
    void set_size(uint64_t size);
    void set_raw(const std::string& raw);
    void set_binary(const std::string& binary);
    void set_is_user_defined(bool result);

    // Method to parse raw operand to binary
    void parseRawToBinary();

    // Helper methods to parse different bases
    std::string parseBinary(const std::string& raw);
    std::string parseOctal(const std::string& raw);
    std::string parseDecimal(const std::string& raw);
    std::string parseHexadecimal(const std::string& raw);

    // Inheritance
    // virtual void identifyChild() const = 0;

    // Print value
    // virtual void printValue() const;

    // Equality operators
    bool operator==(const Operand &other) const {
        return raw == other.raw && size == other.size && binary == other.binary;
    }

    bool operator!=(const Operand &other) const {
        return !(*this == other);
    }
};

#endif
