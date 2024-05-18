#ifndef TRANSLATOR_HH
#define TRANSLATOR_HH

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>  // Include algorithm for std::all_of
#include "Line.hh"
#include "EventEnum.hh"
#include "OpCode.hh"
#include "PseudoOpCode.hh"
#include "Section.hh"
#include "ConstPrefix.hh"

class Translator {
public:
    // Constructors
    Translator();
    Translator(const std::string& inputFilePath, const std::string& outputFilePath);

    // Destructor
    ~Translator();

    // Accessors
    std::string get_asmFilePath() const;
    std::string get_outputFilePath() const;
    std::string get_errorFilePath() const;

    // Mutators
    void set_asmFilePath(const std::string& newInputFilePath);
    void set_outputFilePath(const std::string& newOutputFilePath);
    void set_errorFilePath(const std::string& newErrorFilePath);

    // General methods
    EventEnum define_lines();
    EventEnum define_lines(const std::string& filePath);
    void first_pass();
    void second_pass();


    // Method to handle translation process
    EventEnum translate(const std::string& asmFilePath);


private:
    std::string asmFilePath;
    std::string outputFilePath;
    std::string errorFilePath;
    std::vector<Line> lines_array;
    std::ofstream output_file;
    bool contains_error = false;

    static std::unordered_map<std::string, PseudoOpCode> pseudo_op_enum;
    static std::unordered_map<std::string, Section> section_enum;
    static std::unordered_map<std::string, ConstPrefix> const_prefix_enum;
    static std::unordered_map<std::string, std::string> text_label_hashmap;
    static std::unordered_map<std::string, std::string> data_label_hashmap;
    static std::unordered_map<std::string, std::string> const_hashmap;

    EventEnum return_message(EventEnum event);
    EventEnum make_error_file();
};

#endif

// Translator Class
// Description:
// This class accesses files, parses them, and builds the outputs. This class also sends and receives event
// messages from the UI class instance. This class is not available to the user and has access to all
// information necessary for its designated tasks.
// Base Class:
// None.
// Data Members:
// output_file_path
// Description: The output file path to place all of the translator’s generated files.
// Applicability: Instance.
// Derivability: Derived from the UI calling translator methods to set output file path.
// Constraints: Can be either relative or absolute path, does not necessarily need to be an existing file
// already.
// Type: String
// input_file_path
// Description: The current state of the application.
// Applicability: Instance.
// Derivability: Derived from UI class calling method to set the file path based on user input.
// Constraints: Must be an actual file with PIC assembly code.
// Type: String
// lines_array
// Description: The ordered array of line objects ready to translate.
// Applicability: Instance.
// Derivability: Derived solely from the lines of the input file.
// Constraints: Each line must have the proper formatting, but this is handled by the line class.
// Type: Line array
// output_file
// Description: The output file to write to.
// Applicability: Instance.
// Derivability: Derived from the output file path.
// Constraints: Same as output file path.
// Type: file/fstream
// contains_error
// Description: Indicates if the input file contains an error.
// Applicability: Instance.
// Derivability: Can only be determined/set by the return value of the define_lines function.
// Constraints: Initialized as false.
// Type: Boolean
// op_code_enum
// Description: An enumeration of all of the possible op codes.
// Applicability: Class.
// Derivability: Predefined by the assembler developers.
// Constraints: Must be hashable. Must be one of the defined messages. Otherwise it means undefined
// behavior.
// Type: Enum
// pseudo_op_enum
// Description: An enumeration of all of the possible pseudo op codes.
// Applicability: Class.
// Derivability: Predefined by the assembler developers.
// Constraints: Must be hashable. Must be one of the defined messages. Otherwise it means undefined
// behavior.
// Type: Enum
// section_enum
// Description: An enumeration of all of the sections.
// Applicability: Class.
// Derivability: Predefined by the assembler developers.
// Constraints: Must be hashable. Must be one of the defined messages. Otherwise it means undefined
// behavior.
// Type: Enum
// const_prefix_enum
// Description: An enumeration of all of the possible constant prefixes.
// Applicability: Class.
// Derivability: Predefined by the assembler developers.
// Constraints: Must be hashable. Must be one of the defined messages. Otherwise it means undefined
// behavior.
// Type: Enum
// text_label_hashmap
// Description: A hashmap used for storing user defined program memory space labels.
// Applicability: Class.
// Derivability: All entries are user defined.
// Constraints: Labels names must be unique.
// Type: Hashmap
// data_label_hashmap
// Description: A hashmap used for storing user defined data memory space labels.
// Applicability: Class.
// Derivability: All entries are user defined.
// Constraints: Label names must be unique.
// Type: Hashmap
// const_hashmap
// Description: A hashmap used for storing user defined program constants.
// Applicability: Class.
// Derivability: All entries are user defined.
// Constraints: Constant names must be unique.
// Type: Hashmap
// Constructors:
// init_translator
// Description: Creates and returns a new translator instance with the given input and output file paths.
// Arguments: input file path (String); output file path (String)
// Return Value: translator
// Destructors:
// None (command line interrupt or alt+f4).
// Methods:
// Accessors:
// get_input_file_path
// Description: Return the absolute file path of the input file
// Arguments: none
// Return Value: String
// get_output_file_path
// Description: Return the absolute file path of the output file
// Arguments: none
// Return Value: String
// get_error_file_path
// Description: Return the absolute file path of the error file
// Arguments: none
// Return Value: String
// Mutators:
// set_intput_file_path
// Description: Update the absolute file path of the input file.
// Arguments: new_input_file_path (String)
// Return Value: None.
// set_output_file_path
// Description: Update the absolute file path of the output file.
// Arguments: new_output_file_path (String)
// Return Value: None.
// set_error_file_path
// Description: Update the absolute file path of the error file
// Arguments: none
// Return Value: String
// General:
// *** NOTE: Include files are not handled until after the original file has been handled. This is to
// easily preserve program memory space line enumeration.
// define_lines (without parameter)
// Description: Opens the instance’s input_file_path String’s file and parses every line into line objects with
// the line constructor init_line. Empty, space/tab only, or commented-out lines will not be included. If any
// errors are encountered while translating the code, it will set contains_error to true and return an error
// event_enum. If a line contains the “.include” pseudo op without errors, then it will instead append the line
// into a local list. Once it has defined all the lines in the default input file, it will call the overloaded version of
// define_lines with the include file path.
// Arguments: None.
// Return Value: event_enum.
// define_lines (with parameter)
// Description: Same as the other version of define_lines but defines lines from the given path instead.
// Arguments: file_path (String)
// Return Value: event_enum.
// first_pass
// Description: Asserts that the lines_array data member has been initiated. Loops through every line inside
// of the instance’s lines_array and stores any constants, or labels that it encounters into the
// const_hashmap, text_label_hasmap, and data_label_hashmap structures.
// Arguments: None.
// Return Value: None.
// second_pass
// Description: Asserts that the lines_array data member has been initiated. Loops through every line inside
// of the lines_array. If the line has symbolic parameters, it translates it into PICHEX format using the data in
// the hashmap structures.
// Arguments: None.
// Return Value: None.
// Private:
// return_message
// Description: Returns message for use of UI.
// Arguments: event_enum
// Return Value: event_enum
// make_error_file
// Description: Takes in line array, iterates through each line and appends to the output file line numbers and
// their corresponding error types. Returns a confirmation event when done
// Arguments: None.
// Return Value: event_enum
// Operators:
// None.
// Type Conversions:
// None.
// Error Handling:
// All of the error handling detection in this class will occur in the define_lines. The specific types of errors
// that this function handles are syntax errors, undefined symbol errors, and file formatting errors. Because
// we will output every single error to an error file, if at least one error occurs, the define lines function will
// not assemble the code into the expected PICHEX output file. Instead it will create an error output file and
// return a generic error enum, since adding specificity to this would make for redundancy in our error
// handling. The UI class handles the communication of the errors to the user.
// Helper Functions:
// None.
