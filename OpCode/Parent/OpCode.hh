#ifndef __OPCODEHH__
#define __OPCODEHH__

using namespace std;

class OpCode
{
public:
	string code;
	string PICHEX;
	OpCode(const string opcode, const string obPICHEX){
		code = opcode;
		PICHEX = obPICHEX;
	}
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