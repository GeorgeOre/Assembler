#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std;

string OpCode::get_hex(){
	return pichex;
}

string OpCode::get_code(){
	return code;
}
