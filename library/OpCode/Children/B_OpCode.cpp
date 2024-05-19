#include "B_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <Operand.hh>
using namespace std;

class Operand;

string B_OpCode::get_hex(){
	return format + pichex + operands.back().getBinary()
		+ operands.front().getBinary();
}

list<Operand> B_OpCode::get_operands(){
	return operands;
}

string B_OpCode::get_code(){
	return code;
}

string B_OpCode::get_format(){
	return format;
}

bool B_OpCode::is_pseudo_op(){
    return false;
}