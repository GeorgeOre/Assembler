#ifndef B_OpCode_HH
#define B_OpCode_HH
#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
using namespace std;

class B_OpCode : public OpCode
{
private:
	string format = "01";
	map<string, string> pichex_map = {
		{"BCF", "00"}, {"BSF", "01"},
		{"BTFSC", "10"}, {"BTFSS", "11"}
	};
	list<Operand> operands;
	string code;
	string pichex;

public:
	B_OpCode(const string opcode, list<Operand> ob_operands) : OpCode() {
		code = opcode;
		pichex = pichex_map.at(opcode);
		operands = ob_operands;
	};
    
	string get_hex() override;
	string get_code() override;
	list<Operand> get_operands() override;
	string get_format() override;
	bool is_pseudo_op() override;

};

#endif