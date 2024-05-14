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
	list<Operand<string>> operands;
	string code;
	string pichex;

public:
	CTRL_OpCode(const string opcode, string pichex, list<Operand<string>> ob_operands){
		code = opcode;
		pichex = pichex_map.at(opcode);
		operands = ob_operands;
	};
	string get_hex();
	string get_code();
	string get_operands();
	string get_format();

};

#endif