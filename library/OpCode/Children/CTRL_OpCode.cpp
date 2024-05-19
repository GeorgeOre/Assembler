#include "CTRL_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <Operand.hh>
#include <OpCode.hh>
using namespace std;

class Operand;

string CTRL_OpCode::get_hex(){
	return format + pichex + operands.front().getBinary();
}

list<Operand> CTRL_OpCode::get_operands(){
	return operands;
}

string CTRL_OpCode::get_code(){
	return code;
}

string CTRL_OpCode::get_format(){
	return format;
}

bool CTRL_OpCode::is_pseudo_op(){
    return false;
}

