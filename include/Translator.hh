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
    EventEnum first_pass();
    EventEnum second_pass();


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