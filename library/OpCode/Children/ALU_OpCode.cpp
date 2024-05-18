#include "ALU_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

string ALU_OpCode::get_hex(){
	string to_return = format + pichex;
	if (code != "MOVWF") {
		to_return = to_return + operands.back().getBinary() ;
	}
	return to_return + operands.front().getBinary();
}