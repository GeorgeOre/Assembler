#ifndef W_OPCODE_HH
#define W_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <list>
#include <memory>
#include <unordered_map>

class W_OpCode : public OpCode {
public:
    static std::unordered_map<std::string, std::string> op_format_map;
    static std::unordered_map<std::string, std::string> op_bin_map;
    static std::unordered_map<std::string, std::string> op_operand_map;

    W_OpCode(const std::string& opcode);
    
//     std::string get_hex() const override;
//     std::string get_code() const override;
//     std::list<std::shared_ptr<Operand>> get_operands() const override;
//     std::string get_format() const override;
//     bool is_pseudo_op() const override;

// private:
//     std::map<std::string, std::string> w_map = {
//         {"MOVLW", "0000"}, {"RETLW", "0100"},
// 		{"IORLW", "1000"}, {"ANDLW", "1001"},
// 		{"XORLW", "1010"}, {"SUBLW", "1100"},
// 		{"ADDLW", "1110"}
//         // Add other W opcodes and their corresponding values
//     };
};

#endif


