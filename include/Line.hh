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
    std::shared_ptr<OpCode> opcode;      // OpCode in the line 
    std::vector<std::shared_ptr<Operand>> operands; // List of Operands
    // std::vector<std::shared_ptr<Operand>> operands; // List of pointers to Operands
    bool contains_user_defined;

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

    // Define move constructor and move assignment operator
    Line(Line&& other) noexcept = default;
    Line& operator=(Line&& other) noexcept = default;

    // Delete copy constructor and copy assignment operator
    Line(const Line& other) = delete;
    Line& operator=(const Line& other) = delete;

    // Accessors
    uint64_t get_line_number(); //const;
    u_int64_t get_memory_address(); //const;
    std::string& get_file_name(); //const;
    std::string& get_section(); //const;
    std::string& get_raw_line(); //const;
    OpCode& get_opcode(); //const;
    std::vector<std::shared_ptr<Operand>>& get_operands(); //const;
    // const std::vector<std::shared_ptr<Operand>>& getOperands() const;
    bool get_contains_user_defined(); //const;
    bool get_contains_error(); //const;
    std::string& get_error_message(); //const;

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
    void set_contains_user_defined(bool result);
    void set_error_message(std::string message);

    // Parse line should be used to simplify the parsing process visually
    void parseLine();

    // to_pichex should return the pichex output of the line to be printed to the output file
    std::string to_pichex() const;
};

#endif // LINE_HH
