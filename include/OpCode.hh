#ifndef __OPCODEHH__
#define __OPCODEHH__

#include "Operand.hh"
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <string>

//#include <unordered_set>
extern std::unordered_map<std::string, std::string> op_type_map;
extern std::unordered_map<std::string, std::string> valid_opcodes;

class OpCode
{
protected:

public:
    std::string code;
    std::string pichex;
    std::string format;
    std::list<std::shared_ptr<Operand>> operands;

    OpCode() = default;
    OpCode(const std::string& code);
    virtual ~OpCode() = default;

    virtual std::string get_hex() const;
    virtual std::string get_code() const;
    virtual std::list<std::shared_ptr<Operand>> get_operands() const;
    virtual std::string get_format() const;
    virtual bool is_pseudo_op() const;

    // std::map<std::string, std::string> op_type_map;
    // std::map<std::string, std::string> valid_opcodes;
};



#endif
