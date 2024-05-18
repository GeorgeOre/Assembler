#ifndef ALU_OpCode_HH
#define ALU_OpCode_HH
#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
using namespace std;

class ALU_OpCode : public OpCode
{
private:
	string format = "00";
	map<string, string> pichex_map = {
		{"MOVWF", "00001"}, {"CLR", "0001"},
		{"SUBWF", "0010"}, {"DECF", "0011"},
		{"IORWF", "0100"}, {"ANDWF", "0101"},
		{"XORWF", "0110"}, {"ADDWF", "0111"},
		{"MOVF", "1000"}, {"COMF", "1001"},
		{"INCF", "1010"}, {"DECFSZ", "1011"},
		{"RRF", "1100"}, {"RLF", "1101"},
		{"SWAPF", "1110"}, {"INFSZ", "1111"}
	};
	list<Operand> operands;
	string code;
	string pichex;

public:
	ALU_OpCode(const string opcode, list<Operand> ob_operands){
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