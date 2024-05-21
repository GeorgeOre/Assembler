#ifndef TRANSLATOR_HH
#define TRANSLATOR_HH

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

#include "Line.hh"
#include "OpCode.hh"
#include "Operand.hh"

#include "Section.hh"
#include "Segment.hh"

#include "EventEnum.hh"
#include "ConstPrefix.hh"

class Translator {
public:
    // File streams
    std::ifstream inputFile;
    std::ofstream outputFile;

    // Object instance arrays
    std::vector<Line> lines_array;
    std::vector<Section> sections_array;
    std::vector<Segment> segments_array;

    // File paths
    std::string asmFilePath;
    std::string outputFilePath;
    std::string errorFilePath;

    // Other data members
    std::string cur_section;
    EventEnum message;
    std::string error_message;
    bool contains_error;

    // Hashmaps
    static std::unordered_map<std::string, Section> section_enum;
    static std::unordered_map<std::string, ConstPrefix> const_prefix_enum;
    static std::unordered_map<std::string, std::string> text_label_hashmap;
    static std::unordered_map<std::string, std::string> data_label_hashmap;
    static std::unordered_map<std::string, std::string> const_hashmap;

    // Constructors and destructors
    Translator();
    //Translator(const Translator&);    // Delete copy constructor and assignment operator = delete;
    // Translator& operator=(const Translator&);       // Delete copy constructor and assignment operator = delete;
    Translator(const std::string& inputPath, const std::string& outputPath);
    ~Translator();

    // Getter methods
    std::string get_asmFilePath() const;
    std::string get_outputFilePath() const;
    std::string get_errorFilePath() const;
    std::vector<Line> get_lines_array();

    // Setter methods
    void set_asmFilePath(const std::string& newInputFilePath);
    void set_outputFilePath(const std::string& newOutputFilePath);
    void set_errorFilePath(const std::string& newErrorFilePath);


    // Essential translation methods
    EventEnum define_lines(const std::string& file_info);
    EventEnum first_pass();
    EventEnum second_pass();

    // IO methods
    void write_output();
    void receive_message(EventEnum event);
    EventEnum return_message();
    EventEnum make_error_file();

private:
};

#endif
