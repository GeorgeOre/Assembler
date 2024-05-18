#include "../include/Line.hh"
#include "../include/OpCode/Children/ALU_OpCode.hh"
#include "../include/OpCode/Children/B_OpCode.hh"
#include "../include/OpCode/Children/CTRL_OpCode.hh"
#include "../include/OpCode/Children/Misc_OpCode.hh"
#include "../include/OpCode/Children/W_OpCode.hh"
#include "Operand.hh"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string>
#include <bitset>
#include <list>
#include <inttypes.h>
#include <sstream>

using namespace std;


Line::Line(u_int64_t line_num, u_int64_t address, string line, Segment segment){
	line_number = line_num;
	line = line;
	segment = segment;
	address = address;
	contains_error = false;
	error_message = "";
	list<string> words = line_to_list(line);
	string op_code = words.front();
	words.pop_front();
	list<Operand> operands;
	string op_type;
	for (string word : words) {
		operands.push_back(Operand(word));
	}
	try {
		op_type = op_type_map.at(op_code);
	}
	catch (out_of_range) {
		contains_error = true;
		error_message = "Undefined OpCode: line %" PRIu64 "\n", line_number;
	}
	if (op_type == "ALU") {
		opcode = ALU_OpCode(op_code, operands);
	}
	if (op_type == "B") {
		opcode = B_OpCode(op_code, operands);
	}
	if (op_type == "CTRL") {
		opcode = CTRL_OpCode(op_code, operands);
	}
	if (op_type == "MISC") {
		opcode = Misc_OpCode(op_code, operands);
	}
	if (op_type == "W") {
		opcode = W_OpCode(op_code, operands);
	}
}

list<string> line_to_list(string line){
	list<string> to_return;
	string temp_word = "";
	for (auto c : line){
		const char*  ch = (const char*) c;
		if (ch == " "){
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
	string to_return = "";
	unsigned long binary = bitset<16>(opcode.get_hex()).to_ulong();
	std::stringstream stream;
	stream << std::hex << binary;
	string data = stream.str();
	size_t length = data.size();
	if (length % 2 == 1){	
		data.insert(0, 1, '0');
	}
	string all_but_checksum = get_size(data.size()) +  get_addr(address) + "02" + data;
	return all_but_checksum + checksum(data.size(), get_addr(address), "02", data);
}

string get_addr(u_int64_t addr){
	std::stringstream stream;
	stream << std::hex << addr;
	string address = stream.str();
	size_t length = address.size();
	size_t to_add = 4 - length;
	address.insert(0, to_add, '0');
	return address;
}

string get_size(u_int64_t size){
	std::stringstream stream;
	stream << std::hex << size;
	string address = stream.str();
	size_t length = address.size();
	size_t to_add = 2 - length;
	address.insert(0, to_add, '0');
	return address;
}

string checksum(int size, string line2, string line3, string line4){
	int sum = size;
	for (int i = 0; i < line2.size(); i += 2){
		string sub = line2.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	for (int i = 0; i < line3.size(); i += 2){
		string sub = line3.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	for (int i = 0; i < line4.size(); i += 2){
		string sub = line4.substr(i,i+2);
		sum += std::stoi(sub, nullptr, 16);
	}
	int modded = sum % 256;
	int next = 256 - modded;
	std::stringstream stream;
	stream << std::hex << next;
	string cs = stream.str();
	return cs;
}