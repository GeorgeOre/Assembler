#include "ALU_OpCode.hh"
#include "Operand.hh"
#include "OpCode.hh"

#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

class Operand;

// string ALU_OpCode::get_hex(){
// 	string to_return = format + pichex;
// 	if (code != "MOVWF") {
// 		to_return = to_return + operands.back().getBinary() ;
// 	}
// 	return to_return + operands.front().getBinary();
// }

string ALU_OpCode::get_hex(){
    return "oh wow";
}
string ALU_OpCode::get_code(){
    return "";
}
list<Operand> ALU_OpCode::get_operands(){
    return this->operands;
}
string ALU_OpCode::get_format(){
    return "";
}

bool ALU_OpCode::is_pseudo_op(){
    return false;
}