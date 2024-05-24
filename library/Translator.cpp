#include "Translator.hh"
#include "EventEnum.hh"

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// Initialize maps
std::unordered_map<std::string, std::string> Translator::text_label_hashmap = {};
std::unordered_map<std::string, std::string> Translator::data_label_hashmap = {};
std::unordered_map<std::string, std::string> Translator::const_hashmap = {};
// std::unordered_map<std::string, Section> Translator::section_enum;
// std::unordered_map<std::string, ConstPrefix> Translator::const_prefix_enum;


// Constructors and destructors
Translator::Translator(){}
Translator::Translator(const std::string& inputPath, const std::string& outputPath)
    : input_file_path(inputPath), output_file_path(outputPath), contains_error(false) {}
// Translator::~Translator() {}

// Accessors and setters
std::string Translator::get_input_file_path() const {return this->input_file_path;}
std::string Translator::get_output_file_path() const {return this->output_file_path;}
std::string Translator::get_error_file_path() const {return this->error_file_path;}
std::string Translator::get_cur_section() const {return this->cur_section;}
EventEnum Translator::get_message() const {return this->message;}
std::string Translator::get_error_message() const {return this->error_message;}
bool Translator::get_contains_error() const {return this->contains_error;}
std::vector<std::shared_ptr<Line>> Translator::get_lines_array() {return this->lines_array;}
void Translator::set_input_file_path(const std::string& new_input_file_path){
    this->input_file_path = new_input_file_path;
    }
void Translator::set_output_file_path(const std::string& new_output_file_path){
    this->output_file_path = new_output_file_path;
}
void Translator::set_error_file_path(const std::string& new_error_file_path){
    this->error_file_path = new_error_file_path;
}
void Translator::set_cur_section(const std::string& new_section){
    this->cur_section = new_section;
}
void Translator::set_message(EventEnum new_message){
    this->message = new_message;
}
void Translator::set_error_message(const std::string& new_error_message){
    this->error_message = new_error_message;
}
void Translator::set_contains_error(bool new_result){
    this->contains_error = new_result;
}

// Essential translator functions
EventEnum Translator::define_lines(const std::string& file_info) {
    // Error handle that the file path is valid and open
    std::string filePath = file_info;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return EventEnum::FILE_NOT_FOUND;
    }
    
    // Make sure that section is defined
    //UNTIL WE INPLEMENT PSEUDO OPS LETS DEFAULT SECTION TO .data
    this->cur_section = ".text";
    if (this->cur_section.compare("")==0) {
        this->contains_error = true;
        this->error_message = "Section is not defined!";
        return EventEnum::FILE_FORMAT_ERROR;
    }

    // Parse file line by line
    std::string lineContent;
    int lineNumber = 1; 
    while (std::getline(file, lineContent)) {
        // Search file for URGENT pseudo ops
        std::istringstream iss(lineContent);
        std::string word;
        iss >> word;
        if(word == ".include") {
            std::string includeFile;
            iss >> includeFile;
            if(!includeFile.empty()) {
                // Remove quotes if present
                if(includeFile.front() == '"' && includeFile.back() == '"') {
                    includeFile = includeFile.substr(1, includeFile.size() - 2);
                }
                define_lines(includeFile); // Recursive call to include the file
            }
        } else if((word.compare(".text")==0) || (word.compare(".data")==0) || (word.compare(".info")==0)) {
            this->cur_section = word;
        } 
        
        // Check that section is working well
        // Line line(lineNumber, lineSection, lineContent, this->asmFilePath);
        std::shared_ptr<Line> line = std::make_shared<Line>(lineNumber, this->cur_section, lineContent, this->input_file_path);
        this->lines_array.push_back(std::move(line));

        // Check if the line is a pseudo op

        lineNumber++;
    }

    return EventEnum::SUCCESS;
}

EventEnum Translator::first_pass() {
    int currentProgramAddress = 1;
    int currentDataAddress = 1;

    // Loop through each line
    for (size_t i = 0; i < this->lines_array.size(); ++i) {
        // Remove empty or commented out lines from the array
        if (this->lines_array[i]->get_raw_line().empty() == true) {
            this->lines_array.erase(this->lines_array.begin() + i);
            i--;
            currentProgramAddress--;
        } 
        
        // Store user defined values into corresponding hashmaps
        else if (this->lines_array[i]->get_contains_user_defined())
        {
            // Handle constant declarations
            if (this->lines_array[i]->get_opcode().get_code_str().compare(".EQU") == 0)
            {
                // Fetch key value pair
                std::string user_key = this->get_lines_array()[i]->get_operands()[0]->get_raw();
                std::string user_value = this->get_lines_array()[i]->get_operands()[1]->get_raw();

                // Store in hashmap
                const_hashmap.insert(std::make_pair(user_key, user_value));

                // Remove line from array
                this->lines_array.erase(this->lines_array.begin() + i);
                i--;
                currentProgramAddress--;
            } 
            // Handle label definitions
            else if (this->lines_array[i]->get_opcode().get_code_str().back() == ':')
            {
                // Handle text section label
                if (this->lines_array[i]->get_section().compare(".text") == 0) {
                    // Fetch key value pair
                    std::string user_key = this->lines_array[i]->get_opcode().get_code_str().substr(0, this->lines_array[i]->get_opcode().get_code_str().size()-2);
                    std::string user_value = std::to_string(currentProgramAddress);

                    // Store in hashmap
                    const_hashmap.insert(std::make_pair(user_key, user_value));
                } 
                // Handle data section label
                else if (this->get_lines_array()[i]->get_section().compare(".data") == 0) {
                    // Fetch key value pair
                    std::string user_key = this->get_lines_array()[i]->get_opcode().get_code_str().substr(0, this->lines_array[i]->get_opcode().get_code_str().size()-2);
                    std::string user_value = std::to_string(currentDataAddress);

                    // Update data addresses
                    currentDataAddress++;

                    // Store in hashmap
                    const_hashmap.insert(std::make_pair(user_key, user_value));
                }
                
                
            }
            
        }
        // Store program address here??
        currentProgramAddress++;
        
        // std::cout << "Address: " << lines[i].getAddress() << " Content: " << lines[i].getContent() << std::endl;
    }    
    // Optionally, you can print the symbol table for debugging
    // for (const auto& symbol : symbolTable) {
    //     std::cout << "Label: " << symbol.first << " Address: " << symbol.second << std::endl;
    // }
    
    return EventEnum::SUCCESS;
}

EventEnum Translator::second_pass() {
    // Check to make sure that the output file is valid
    std::ofstream outputFile(this->output_file_path);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << this->output_file_path << std::endl;
        return EventEnum::FILE_NOT_FOUND;
    }

    for (const auto& line : this->lines_array) {
        // Translate instruction
        outputFile << line->to_pichex() << std::endl;
    }

    outputFile.close();
    return EventEnum::SUCCESS;
}


void Translator::write_output() {
    // Implementation
}

EventEnum Translator::handle_message(EventEnum event) {
    // Implementation
    this->message = event;
    return EventEnum::SUCCESS;
}

// void Translator::receive_message(EventEnum event) {
//     // Implementation
//     this->message = event;
// }

// EventEnum Translator::return_message() {
//     // Implementation
//     return EventEnum::SUCCESS;
// }

// EventEnum Translator::make_error_file() {
//     // Implementation
//     return EventEnum::SUCCESS;
// }
