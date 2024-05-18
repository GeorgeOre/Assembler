#ifndef __LINE_H__
#define __LINE_H__
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "OpCode.hh"
#include "Segment.hh"
#include <map>



//Data Members:
class Line
{
private:
  u_int64_t line_number;
  string line;
  OpCode opcode;
  Segment segment;
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
		{"TRIS", "MISC"}, {"ADDLW", "W"}
    {"MOVLW", "W"}, {"RETLW", "W"},
		{"IORLW", "W"}, {"ANDLW", "W"},
		{"XORLW", "W"}, {"SUBLW", "W"}
  };
  
public:
  Line(u_int64_t line_num, string line, Segment segment);
  string to_pichex();
  u_int64_t get_line_num();

  bool contains_error;
};

// Line::Line(/* args */)
// {
// }

// Line::~Line()
// {
// }
// Line
// {

// /*
//   Description: The assembly file line number of a line.
//   Applicability: Instance
//   Derivability: Derived from line number of a specific line.
//   Constraints: Must be equal to the line of assembly it is reading.
//   Type: Unsigned int
// */

//   string get_line_pseudo_ops;
// /*
//   Description: The pseudo-op of the line.
//   Applicability: instance
//   Derivability: Taken from line parsing.
//   Constraints: Must be a supported pseudo-op.
//   Type: pseudo_op_enum
// */

//   OpCode line_op_code;
// /*
//   Description: The op-code of a specific line.
//   Applicability: instance
//   Derivability: Take from the line parsing.
//   Constraints: Must be a defined op-code.
//   Type: op-code-enum
  
//   general op code that can represent anything

//   OPERANDS SHOULD HAVE A CHECK VALID FUCNTION THAT IS 
//   SPECIFIC TO EVERY ONE AND TELLS YOU WHETHER OR NOT 
//   THE LINE IS VALID SO YOU CAN EASILY THROW AN ERROR

// */

//   OpCode line_section;
// /*
//   Description: The section a line is in.
//   Applicability: instance
//   Derivability: Whatever section the parsed line is in.
//   Constraints: Must be a supported section.
//   Type: section_enum
//   opcode->SECTIONpsudoop
// */

//   string line_labels;
// /*
//   Description: The label a line has.
//   Applicability: instance
//   Derivability: From the parsed line of code, if it contains a label.
//   Constraints: Has to have an occurrence in the label hashtable.
//   Type: String
// */

//   Operand line_constants;
// /*
//   Description: Any user-defined constants on the line.
//   Applicability: instance
//   Derivability: Taken from the parsed line of code.
//   Constraints: Must be a user defined symbol in the corresponding hashtable.
//   Type: String
// */

//   list<string> line_operands;
// /*
//   Description: The operands of the op-code.
//   Applicability: instance
//   Derivability: Taken from the parsed line of code.
//   Constraints: Must be proper type of operand, must have correct number for corresponding op-code.
//   Type: array
// */

// error;
// /*
//   Description: Indicates if the line contains an error.
//   Applicability: Instance.
//   Derivability: Can only be determined/set by inside of the init_line function.
//   Constraints: None.
//   Type: line_error
// */

// } line_t;



// /*  Constructors:
//   Description: Takes a string and parses it into a line object.
//   Arguments: String (expecting one line)
//   Return Value: None.   */
// line_t *init_line(char *line_str);

// /*
// Destructors:
//   None (command line interrupt or alt+f4).
// */

// /*
//   Methods:  
// */
// /*Accessors:*/

// int get_line_number(line_t);/*
// Description: Return the line number.
// Arguments: None.
// Return Value: Unsigned int.
// */

// char *get_line_pseudo_ops();/*
// Description: Return the pseudo-op.
// Arguments: none
// Return Value: pseudo_op_enum
// */

// char *get_line_op_codes()/*
// Description: Return the line’s op-code.
// Arguments: none
// Return Value: op_code_enum.
// */

// char *get_line_section();/*
// Description: Return the line’s section.
// Arguments: none
// Return Value: section_enum.
// */

// char *get_line_labels();/*
// Description: Return the line’s label.
// Arguments: none
// Return Value: String.
// */

// char *get_line_constants()/*
// Description: Return the line’s constants.
// Arguments: none
// Return Value: String array.
// */

// char *get_line_operands();/*
// Description: Return the line’s operands.
// Arguments: none
// Return Value: Array.
// */

// /*Mutators:*/

// void set_line_number(line_t *line);/*
// Description: Sets the line number of the line.
// Arguments: none
// Return Value: None
// */

// void set_line_op_codes(line_t *line);/*
// Description:Sets the line’s op-code.
// Arguments: none
// Return Value: None.
// */

// void set_line_operands(line_t *line);/*
// Description: Sets the line’s operands.
// Arguments: none
// Return Value: None.
// */


// /*General:*/

// void write_PICHEX(line_t *line);/*
// Description: Translates a line to PIC HEX. Writes line to output_file_path file.
// Arguments: output_file_path
// Return Value: None
// */

// bool check_error(line_t *line);/*
// Description: Checks if a line has an error
// Arguments: error_file_path
// Return Value: error_enum or void
// */

// /*Private:
//   None. 
// */


// /*Operators:
//   None.
// */

// /*Type Conversions:
// None.
// */

// /*Error Handling:
// None.
// */

// /*Helper Functions:
// None.
// */

// /*Simple Types

// event_enum
// Description:
// An enumerated representation of all possible events. This includes everything from user response events,
// to all error events.
// Scope:
// Global
// Type:
// Enum

// line_error
// Description:
// A structure that contains a string and event_enum to contain the details of an error.
// Scope:
// Line instance
// Type:
// Line_error (custom)
// */

#endif // #ifndef __LINE_H__