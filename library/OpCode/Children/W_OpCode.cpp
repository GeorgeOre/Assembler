#include "W_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <Operand.hh>
using namespace std;

class Operand;

string W_OpCode::get_hex(){
	return format + pichex + operands.front().getBinary();
}

list<Operand> W_OpCode::get_operands(){
	return operands;
}

string W_OpCode::get_code(){
	return code;
}

string W_OpCode::get_format(){
	return format;
}

bool W_OpCode::is_pseudo_op(){
    return false;
}