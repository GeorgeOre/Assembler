#ifndef __LINE_H__
#define __LINE_H__
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "OpCode.hh"
#include "Segment.hh"
#include <map>

class Segment;

//Data Members:
class Line
{
private:
  map<string, string> op_type_map = {
    {"BCF", "B"}, {"BSF", "B"},
	{"BTFSC", "B"}, {"BTFSS", "B"},
    {"MOVWF", "ALU"}, {"CLR", "ALU"},
	{"SUBWF", "ALU"}, {"DECF", "ALU"},
	{"IORWF", "ALU"}, {"ANDWF", "ALU"},
	{"XORWF", "ALU"}, {"ADDWF", "ALU"},
	{"MOVF", "ALU"}, {"COMF", "ALU"},
	{"INCF", "ALU"}, {"DECFSZ", "ALU"},
	{"RRF", "ALU"}, {"RLF", "ALU"},
	{"SWAPF", "ALU"}, {"INFSZ", "ALU"},
    {"CALL", "CTRL"}, {"GOTO", "CTRL"},
    {"NOP", "MISC"}, {"RETURN", "MISC"},
	{"RETFIE", "MISC"}, {"OPTION", "MISC"},
	{"SLEEP", "MISC"}, {"CLRWDT", "MISC"},
	{"TRIS", "MISC"}, {"ADDLW", "W"},
    {"MOVLW", "W"}, {"RETLW", "W"},
	{"IORLW", "W"}, {"ANDLW", "W"},
	{"XORLW", "W"}, {"SUBLW", "W"}
  };
  
public:
  Line(u_int64_t line_num, u_int64_t address, string line, Segment segment);

  string to_pichex();

  u_int64_t get_line_num();
  OpCode opcode;
  string line;
  u_int64_t line_number;
  u_int64_t address;
  Segment segment;
  string error_message;

  bool contains_error;
};

#endif // #ifndef __LINE_H__