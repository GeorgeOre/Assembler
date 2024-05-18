#include "CTRL_OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

string CTRL_OpCode::get_hex(){
	return format + pichex + operands.front().getBinary();
}