#include "OpCode.hh"
#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std;

int main() {

	OpCode obj = OpCode("ADD", "1000");

	cout << obj.code << endl;
	cout << obj.PICHEX << endl;

}
