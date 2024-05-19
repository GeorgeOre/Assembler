#ifndef __OPCODEHH__
#define __OPCODEHH__
//#include "../../Operand/Parent/Operand.hh"

#include "Operand.hh"

#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

class Operand;

class OpCode
{
private:
	
public:
	string code;
	string pichex;
	string format;
	list<Operand> operands;

    OpCode();
    
    // virtual ~OpCode() = default;

	virtual string get_hex();
	virtual string get_code();
	virtual list<Operand> get_operands();
	virtual string get_format();

    virtual bool is_pseudo_op();
	
};

#endif