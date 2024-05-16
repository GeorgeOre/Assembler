#ifndef __OPCODEHH__
#define __OPCODEHH__
#include "Operand.hh"
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

class OpCode
{
private:
	string code;
	string pichex;
<<<<<<< Updated upstream:include/Parent/OpCode.hh
	list<Operand<string>> operands;
=======
	string format;
	//list<Operand> operands;
>>>>>>> Stashed changes:include/OpCode/Parent/OpCode.hh

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