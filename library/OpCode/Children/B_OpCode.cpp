#include "B_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

string B_OpCode::get_hex(){
	return format + pichex + operands.back().getBinary()
		+ operands.front().getBinary();
}