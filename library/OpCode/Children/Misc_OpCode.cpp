#include "Misc_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
#include <Operand.hh>
using namespace std;

class Operand;

string Misc_OpCode::get_hex(){
	string to_return = format + pichex;
	if (code == "TRIS") {
		to_return = to_return + operands.front().getBinary();
	}
	return to_return;
}

list<Operand> Misc_OpCode::get_operands(){
	return operands;
}

string Misc_OpCode::get_code(){
	return code;
}

string Misc_OpCode::get_format(){
	return format;
}
bool Misc_OpCode::is_pseudo_op(){
    return false;
}