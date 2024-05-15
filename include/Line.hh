// MyClass.h

#ifndef __LINE_H__
#define __LINE_H__

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string>

#include "OpCode.hh"
#include "Operand.hh"

/*
  Line Class
  Description:
    This class represents a singular line of assembly to be assembled.
  Base Class:
    None

EXAMPLE:
	- Line object
		○ Operand list member
			§ Index OP
			§ Value OP
			§ String OP
		○ HOW WILL YOU HANDLE ALL OF THE DIFFERENT TYPES
		○ LINE # (IN THE FILE)
		○ FILE STRING
			§ Which file you are in and what line number of the string you 

OP Codes
	- Instruction op code
		○ Index opcodes
		○ Value opcodes
		○ No operand opcode
	- Specific psudo op 1 code
	- Specific psudo op 2 code
	- Specific psudo op 3 code
	- So on
	- Memory space pseudo op
		○ Data
		○ Text
		○ Info
		○ It is structured very similarly but a with maybe a different function pointer
		
		

*/
class Line
{   // Data Members:
    private:
        uint64_t line_number;
        String content;
        Opcode opcode;
        Operand operands[];
        
    public:
        /*  Constructors:
            Description: Takes a string and parses it into a line object.
            Arguments: String (expecting one line)
            Return Value: None.   
        */
        Line(char* line_str);
        
        /*  Destructors:
            None (command line interrupt or alt+f4).
        */
        ~Line();

/*
  Methods:  
*/
        /*Accessors:*/

u_int64_t get_line_number(line_t);/*
Description: Return the line number.
Arguments: None.
Return Value: Unsigned int.
*/

char *get_line_op_codes()/*
Description: Return the line’s op-code.
Arguments: none
Return Value: op_code_enum.
*/

char *get_line_pseudo_ops();/*
Description: Return the pseudo-op.
Arguments: none
Return Value: pseudo_op_enum
*/

char *get_line_section();/*
Description: Return the line’s section.
Arguments: none
Return Value: section_enum.
*/

char *get_line_labels();/*
Description: Return the line’s label.
Arguments: none
Return Value: String.
*/

char *get_line_constants()/*
Description: Return the line’s constants.
Arguments: none
Return Value: String array.
*/

char *get_line_operands();/*
Description: Return the line’s operands.
Arguments: none
Return Value: Array.
*/

/*Mutators:*/

void set_line_number(line_t *line);/*
Description: Sets the line number of the line.
Arguments: none
Return Value: None
*/

void set_line_op_codes(line_t *line);/*
Description:Sets the line’s op-code.
Arguments: none
Return Value: None.
*/

void set_line_operands(line_t *line);/*
Description: Sets the line’s operands.
Arguments: none
Return Value: None.
*/


/*General:*/

void write_PICHEX(line_t *line);/*
Description: Translates a line to PIC HEX. Writes line to output_file_path file.
Arguments: output_file_path
Return Value: None
*/

bool check_error(line_t *line);/*
Description: Checks if a line has an error
Arguments: error_file_path
Return Value: error_enum or void
*/

/*Private:
  None. 
*/


/*Operators:
  None.
*/

/*Type Conversions:
None.
*/

/*Error Handling:
None.
*/

/*Helper Functions:
None.
*/

/*Simple Types

event_enum
Description:
An enumerated representation of all possible events. This includes everything from user response events,
to all error events.
Scope:
Global
Type:
Enum

line_error
Description:
A structure that contains a string and event_enum to contain the details of an error.
Scope:
Line instance
Type:
Line_error (custom)
*/

#endif // #ifndef __LINE_H__
