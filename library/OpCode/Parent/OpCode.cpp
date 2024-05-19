#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std;

OpCode::OpCode(){
	code = "";
	pichex = "";
	format = "";
}

string OpCode::get_hex(){
    return "";
}

string OpCode::get_code(){
    return "";
}

list<Operand> OpCode::get_operands(){
    list<Operand> g;
    return g;
}

string OpCode::get_format(){
    return "";
}

bool OpCode::is_pseudo_op(){
    return false;
}

// OpCode::~OpCode() = default;