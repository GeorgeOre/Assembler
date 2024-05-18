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

private:
    // File paths
    std::string asmFilePath;
    std::string outputFilePath;
    std::string errorFilePath;

    // File stream
    std::ofstream input_file;
    std::ofstream output_file;

    // Lines
    std::vector<Line> lines_array;

    // Error bool
    bool contains_error = false;

    // Private functions
    EventEnum return_message();
    EventEnum make_error_file();

    // Hashmaps
    static std::unordered_map<std::string, PseudoOpCode> pseudo_op_enum;
    static std::unordered_map<std::string, Section> section_enum;
    static std::unordered_map<std::string, ConstPrefix> const_prefix_enum;
    static std::unordered_map<std::string, std::string> text_label_hashmap;
    static std::unordered_map<std::string, std::string> data_label_hashmap;
    static std::unordered_map<std::string, std::string> const_hashmap;

public:
    EventEnum message;

    // Constructors
    Translator();
    Translator(const std::string& inputFilePath, const std::string& outputFilePath);

    // Destructor
    ~Translator();

    // Accessors
    std::string get_asmFilePath() const;
    std::string get_outputFilePath() const;
    std::string get_errorFilePath() const;

    std::vector<Line> get_lines_array();

    // Mutators
    void set_asmFilePath(const std::string& newInputFilePath);
    void set_outputFilePath(const std::string& newOutputFilePath);
    void set_errorFilePath(const std::string& newErrorFilePath);

    // General methods
    EventEnum define_lines();
    EventEnum define_lines(const std::string& filePath);

    EventEnum first_pass();

    EventEnum second_pass();

    // Method to handle translation process
    // EventEnum translate(const std::string& asmFilePath);

    void receive_message(EventEnum event);

};

#endif
