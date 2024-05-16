#ifndef TRANSLATOR_HH
#define TRANSLATOR_HH

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Line.hh"  // Assuming you have a Line class
#include "EventEnum.hh"  // Assuming you have an EventEnum for return messages

class Translator {
public:
    // Constructor
    Translator(const std::string& inputFilePath, const std::string& outputFilePath);

    // Destructor
    ~Translator();

    // Accessors
    std::string get_input_file_path() const;
    std::string get_output_file_path() const;
    std::string get_error_file_path() const;

    // Mutators
    void set_input_file_path(const std::string& newInputFilePath);
    void set_output_file_path(const std::string& newOutputFilePath);
    void set_error_file_path(const std::string& newErrorFilePath);

    // General methods
    EventEnum define_lines();
    EventEnum define_lines(const std::string& filePath);
    void first_pass();
    void second_pass();

private:
    std::string input_file_path;
    std::string output_file_path;
    std::string error_file_path;
    std::vector<Line> lines_array;
    std::ofstream output_file;
    bool contains_error = false;

    static std::unordered_map<std::string, OpCode> op_code_enum;
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
