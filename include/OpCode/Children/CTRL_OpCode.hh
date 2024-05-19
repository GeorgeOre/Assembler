#ifndef CTRL_OpCode_HH
#define CTRL_OpCode_HH
#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
using namespace std;

class CTRL_OpCode : public OpCode
{
private:
	string format = "10";
	map<string, string> pichex_map = {
		{"CALL", "0"}, {"GOTO", "1"}
	};
	list<Operand> operands;
	string code;
	string pichex;

public:
	CTRL_OpCode(const string opcode, list<Operand> ob_operands) : OpCode(){
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