// Line.hh
#ifndef LINE_HH
#define LINE_HH

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "OpCode.hh"
#include "Operand.hh"

class Line {
private:

public:
    // Data members
    uint64_t line_number;     // Line number in source file
    uint64_t memory_address;  // Memory address (either data or program memory)
    std::string file_name;  // Name of source file
    std::string section;    // Name of section
    std::string raw_line;   // Raw line info
    std::unique_ptr<OpCode> opcode;      // OpCode in the line 
    std::vector<Operand> operands; // List of Operands
    // std::vector<std::shared_ptr<Operand>> operands; // List of pointers to Operands

    // This must be changed to map from a string to a constructor
    // STATIC IS NEEDED SO THAT THE SAME ONE CAN BE USED IN ALL INSTANCES OF LINE
    static std::unordered_map<std::string, std::string> op_type_map;   // This is for knowing which child class constructor to call

    bool contains_error;    // Boolean that represents if the line contains an error
    std::string error_message;  // Error message in case the line's error needs to be identified

    // Constructors
    // Lines should be initalized by the Translator class. 
    // The Translator instance should be able to provide all these parameters.
    Line(uint64_t line_number, const std::string& section,
     const std::string& line, const std::string& f_name);

    // Accessors
    uint64_t get_line_number(); //const;
    u_int64_t get_memory_address(); //const;
    const std::string& get_file_name(); //const;
    const std::string& get_section(); //const;
    const std::string& get_raw_line(); //const;
    const OpCode& get_opcode(); //const;
    const std::vector<Operand>& get_operands(); //const;
    // const std::vector<std::shared_ptr<Operand>>& getOperands() const;
    bool get_contains_error(); //const;
    const std::string& get_error_message(); //const;

    // Setters
    void set_line_number(uint64_t line);
    void set_memory_address(uint64_t address);
    void set_file_name(std::string name);
    void set_section(std::string section);
    void set_raw_line(std::string line);
    // void set_opcode(std::string name);
    // void set_operands(std::string name);
    // const std::vector<std::shared_ptr<Operand>>& getOperands() const;
    void set_contains_error(bool result);
    void set_error_message(std::string message);

    // Parse line should be used to simplify the parsing process visually
    void parseLine();

    // to_pichex should return the pichex output of the line to be printed to the output file
    std::string& to_pichex() const;
};

#endif // LINE_HH
