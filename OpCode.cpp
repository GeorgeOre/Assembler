#include "OpCode.hh"
#include <stdio.hh>
#include <iostream>
#include <assert.hh>

using namespace std;

int main() {

	OpCode obj("ADD", "1000");

	cout << obj.code << endl;
	cout << obj.PICHEX <<endl;

}
