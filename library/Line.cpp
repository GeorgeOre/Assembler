#include "../include/Line.hh"
#include "../include/OpCode/Children/ALU_OpCode.hh"
#include "../include/OpCode/Children/B_OpCode.hh"
#include "../include/OpCode/Children/CTRL_OpCode.hh"
#include "../include/OpCode/Children/Misc_OpCode.hh"
#include "../include/OpCode/Children/W_OpCode.hh"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string>
#include <list>
#include <inttypes.h>

using namespace std;


Line::Line(u_int64_t line_num, string line, Segment segment){
	line_number = line_num;
	line = line;
	segment = segment;
	contains_error = false;
	list<string> words = line_to_list(line);
	string op_code = words.pop_front();
	list<string> operands;
	for (auto word : words)
	try {
		string op_type = op_type_map.at(op_code);
	}
	catch (out_of_range) {
		contains_error = true;
		printf("Undefined OpCode: line %" PRIu64 "\n", line_number);
	}
	if (op_type == "ALU") {
		opcode = ALU_OpCode(op_code, )
	}
}

list<string> line_to_list(string line){
	list<string> to_return;
	string temp_word = "";
	for (auto c : line){
		if (c == " "){
			if (temp_word != ""){
				to_return.push_back(temp_word);
				temp_word = "";
			}
			else {continue;}
		}
		else {
			temp_word = temp_word + c;
		}
	}
	return to_return;
}

u_int64_t Line::get_line_num(){
	return line_number;
}

string Line::to_pichex(){
	return "00" + opcode.get_hex();
}

