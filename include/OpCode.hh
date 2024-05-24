#ifndef __OPCODEHH__
#define __OPCODEHH__

//MAYBE WE DONT NEED THIS
// #include "Operand.hh"
// #include <list>
// #include <memory>

// THIS IS ONLY FOR TESTING
#include <string>
#include <cstdint>
#include <iostream>
#include <list>
#include <memory>

// THIS CAN BE ADDED LATER TO ADD SOME SORT OF VALIDATION FUNCTION
// extern std::unordered_map<std::string, std::string> valid_opcodes;

class Operand;

class OpCode
{
protected:

public:
    // Data members
    std::string code_str;   // *** OpCode in string representation
    
    // THE FOLLOWING REQUIRES THE CHILD TO SET BASED ON A MAP IN THE CHILD FILES BUT ALL SHOULD HAVE
    u_int64_t size;         // Size of the OpCode portion in bits (This is parts of the 14 bit instruction that are non-negotiables)
    std::string operand_info; // String representation of the OpCode operand_info
    std::string format;     // Regex expression of the OpCode
    std::string binary;     // Binary in string form (CAN BE CHANGED TO BITSET OR BITWISE SOMETHIGN LATER)
    // THIS ONE MAYBE CAN BE REMOVED
    // bool is_pseudo_op;     // Boolean that indicates whether or not the opcode is a pseudo op

    // Constructor
    // Should I delete this or make it virtual? i feel like it can just be set default
    // THE GOAL IS THAT THIS ONLY SETS code_str AND THE REST IS HANDLED BY THE CHILD
    OpCode(const std::string& code);


    // virtual ~OpCode() = default;

    // Accessors and modifiers
    std::string get_code_str();
    u_int64_t get_size();
    std::string get_operand_info();
    std::string get_format();
    std::string get_binary();
    // bool get_is_pseudo_op();

    // THESE THREE SHOULD BE SET BY THE CHLIDREN
    // virtual void set_code(std::string code); THIS SHOULD NEVER CHANGE AFTER CONSTRUCTION
    virtual void set_size(u_int64_t size);
    virtual void set_operand_info(std::string operand_info);
    virtual void set_format(std::string format);
    virtual void set_binary(std::string binary);
    // virtual void set_is_pseudo_op(bool result);

// OLD INPLEMENTATOINS BELOW

    // THESE DO NOT NEED TO BE VIRTUAL
    // virtual std::string get_code_str();
    // virtual u_int64_t get_size();
    // virtual std::string get_operand_info();
    // virtual std::string get_format();
    // virtual bool get_is_pseudo_op();

    // virtual void set_code(std::string code);
    // virtual void set_size(u_int64_t size);
    // virtual void set_operand_info(std::string operand_info);
    // virtual void set_format(std::string format);
    // virtual void set_is_pseudo_op(bool result);

    // MAYBE EXTERN THESE??
    // std::map<std::string, std::string> op_type_map;
    // std::map<std::string, std::string> valid_opcodes;
};



#endif
