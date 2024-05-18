#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std;

string OpCode::get_code(){
	return code;
}

bool is_pseudo_op(){
    return false;
}