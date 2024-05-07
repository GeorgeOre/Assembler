#ifndef __OPCODEHH__
#define __OPCODEHH__
#include "../../Operand/Parent/Operand.hh"
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

class OpCode
{
private:
	string code;
	string pichex;
	list<Operand<string>> operands;

public:
	OpCode(const string opcode, const string ob_pichex, list<Operand<string>> ob_operands){
		code = opcode;
		pichex = ob_pichex;
		operands = ob_operands;
	}
	string get_hex();
	string get_code();
	string get_operands();
	
};

/*
Operand object
	- Value string
	- HEX Expression
	- In MyCPU Operands
		○ Define specific operand types

Opcode object
	- Knows how to generate machine code
	- Knows valid operand types
	- Search operands
		○ MyCPU first
		○ Generic second
	- Checks types

*/

#endif