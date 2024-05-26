#ifndef OPERAND_HH
#define OPERAND_HH

#include <string>
#include <iostream>
#include <memory>
#include <functional>

#include <unordered_map>
#include <unordered_set>

//class OpCode;  // Forward declaration of OpCode

class Operand {
protected:
    std::string raw;      // Raw string that was parsed
    std::string binary;   // Binary value in string format
    uint64_t size;        // Size of the operand in bits
    bool is_user_defined; // Boolean that represents if the operand is user defined
    bool is_expression;   // Boolean that indicates that this is an expression

public:
    Operand(const std::string& raw);
    virtual ~Operand() = default;

    // Accessors and modifiers
    uint64_t get_size();
    std::string& get_raw();
    std::string& get_binary();
    bool get_is_user_defined();
    
    void set_size(uint64_t size);
    void set_raw(const std::string& raw);
    void set_binary(const std::string& binary);
    void set_is_user_defined(bool result);
    void set_is_expression(bool result);

    // Method to parse raw operand to binary
    void parseRawToBinary();

    // Helper methods to parse different bases
    static std::string parseBinary(const std::string& raw);
    static std::string parseOctal(const std::string& raw);
    static std::string parseDecimal(const std::string& raw);
    static std::string parseHexadecimal(const std::string& raw);

    static std::unordered_map<std::string, std::function<std::string(const std::string&)>> prefix_map;
    static std::unordered_map<std::string, std::function<std::string(const std::string&)>> suffix_map;
    // Equality operators
    // bool operator==(Operand &other) {
    //     return raw == other.raw && size == other.size && binary == other.binary;
    // }

    // bool operator!=(Operand &other) {
    //     return !(*this == other);
    // }

    // Testing functions
    virtual void identifyChild() const = 0;
    // virtual void printValue() const;

};

#endif
