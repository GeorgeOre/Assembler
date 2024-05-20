#ifndef TRANSLATOR_HH
#define TRANSLATOR_HH

#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "EventEnum.hh"
#include "Line.hh"
#include "Section.hh"
#include "Segment.hh"
#include "ConstPrefix.hh"

class Translator {
public:
    Translator(const std::string& inputPath, const std::string& outputPath);
    ~Translator();
    
    EventEnum first_pass();
    EventEnum second_pass();
    void write_output();

    // Getter methods
    std::string get_asmFilePath() const;
    std::string get_outputFilePath() const;
    std::string get_errorFilePath() const;
    std::vector<Line> get_lines_array();

    // Setter methods
    void set_asmFilePath(const std::string& newInputFilePath);
    void set_outputFilePath(const std::string& newOutputFilePath);
    void set_errorFilePath(const std::string& newErrorFilePath);

    // Other methods
    EventEnum define_lines();
    void receive_message(EventEnum event);
    EventEnum return_message();
    EventEnum make_error_file();

    EventEnum message;

private:
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::vector<Line> lines_array;
    std::vector<Section> sections_array;
    std::vector<Segment> segments_array;

    std::string asmFilePath;
    std::string outputFilePath;
    std::string errorFilePath;
    bool contains_error;

    static std::unordered_map<std::string, Section> section_enum;
    static std::unordered_map<std::string, ConstPrefix> const_prefix_enum;
    static std::unordered_map<std::string, std::string> text_label_hashmap;
    static std::unordered_map<std::string, std::string> data_label_hashmap;
    static std::unordered_map<std::string, std::string> const_hashmap;

    // Delete copy constructor and assignment operator
    Translator(const Translator&) = delete;
    Translator& operator=(const Translator&) = delete;
};

#endif
