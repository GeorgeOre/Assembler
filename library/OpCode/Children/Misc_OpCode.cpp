#include "Misc_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

string Misc_OpCode::get_hex(){
	string to_return = format + pichex;
	if (code == "TRIS") {
		to_return = to_return + operands.front().getBinary();
	}
	return to_return;
}