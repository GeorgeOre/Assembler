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
	string format;
	list<Operand> operands;

public:
	OpCode();
	string get_hex();
	string get_code();
	string get_operands();
	string get_format();
	
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