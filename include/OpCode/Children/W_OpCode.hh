#ifndef W_OpCode_HH
#define W_OpCode_HH
#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
using namespace std;

class W_OpCode : public OpCode
{
private:
	string format = "11";
	map<string, string> pichex_map = {
		{"MOVLW", "0000"}, {"RETLW", "0100"},
		{"IORLW", "1000"}, {"ANDLW", "1001"},
		{"XORLW", "1010"}, {"SUBLW", "1100"},
		{"ADDLW", "1110"}
	};
	list<Operand> operands;
	string code;
	string pichex;

public:
	W_OpCode(const string opcode, list<Operand> ob_operands) : OpCode(){
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