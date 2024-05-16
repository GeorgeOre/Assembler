#include "W_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

string W_OpCode::get_hex(){
	return format + pichex + operands.front().operand_get_value();
}