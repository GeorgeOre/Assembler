#ifndef __OPCODEHH__
#define __OPCODEHH__
//#include "../../Operand/Parent/Operand.hh"

#include "Operand.hh"

#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

class OpCode
{
private:

public:
	string code;
	string pichex;
	string format;
	list<Operand> operands;

	OpCode();
	string get_hex();
	string get_code();
	string get_operands();
	string get_format();

    bool is_pseudo_op();
	
};

#endif