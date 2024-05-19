#ifndef Misc_OpCode_HH
#define Misc_OpCode_HH
#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
using namespace std;

class Misc_OpCode : public OpCode
{
private:
	string format = "0000000";
	map<string, string> pichex_map = {
		{"NOP", "0000000"}, {"RETURN", "0001000"},
		{"RETFIE", "0001001"}, {"OPTION", "1100010"},
		{"SLEEP", "1100011"}, {"CLRWDT", "1100100"},
		{"TRIS", "11001"}
	};
	list<Operand> operands;
	string code;
	string pichex;

public:
	Misc_OpCode(const string opcode, list<Operand> ob_operands) : OpCode(){
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