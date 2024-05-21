#include "Translator.hh"

#include <sstream>
#include <unordered_map>

// Initialize static members
std::unordered_map<std::string, Section> Translator::section_enum;
std::unordered_map<std::string, ConstPrefix> Translator::const_prefix_enum;

std::unordered_map<std::string, std::string> Translator::text_label_hashmap;
std::unordered_map<std::string, std::string> Translator::data_label_hashmap;
std::unordered_map<std::string, std::string> Translator::const_hashmap;

// Constructors and destructors
Translator::Translator(){}
Translator::Translator(const std::string& inputPath, const std::string& outputPath)
    : asmFilePath(inputPath), outputFilePath(outputPath), contains_error(false) {}
Translator::~Translator() {}

// Accessors and setters
std::string Translator::get_asmFilePath() const {return this->asmFilePath;}
std::string Translator::get_outputFilePath() const {return this->outputFilePath;}
std::string Translator::get_errorFilePath() const {return this->errorFilePath;}
std::vector<Line> Translator::get_lines_array() {return this->lines_array;}
void Translator::set_asmFilePath(const std::string& newInputFilePath) {asmFilePath = newInputFilePath;}
void Translator::set_outputFilePath(const std::string& newOutputFilePath) {outputFilePath = newOutputFilePath;}
void Translator::set_errorFilePath(const std::string& newErrorFilePath) {errorFilePath = newErrorFilePath;}

// Essential translator functions
EventEnum Translator::define_lines(const std::string& file_info) {
    // Error handle that the file path is valid and open
    std::string filePath = this->asmFilePath; 
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return EventEnum::FILE_NOT_FOUND;
    }
    
    // Make sure that section is defined
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
        if (word == ".include") {
            std::string includeFile;
            iss >> includeFile;
            if (!includeFile.empty()) {
                // Remove quotes if present
                if (includeFile.front() == '"' && includeFile.back() == '"') {
                    includeFile = includeFile.substr(1, includeFile.size() - 2);
                }
                define_lines(includeFile); // Recursive call to include the file
            }
        } else if ((word.compare(".text")==0) || (word.compare(".data")==0) || (word.compare(".info")==0)) {
            this->cur_section = word;
        } 
        
        
        // Check that section is working well
        // Line line(lineNumber, lineSection, lineContent, this->asmFilePath);
        Line line(lineNumber, this->cur_section, lineContent, this->asmFilePath);
        this->lines_array.push_back(line);

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
        if (this->lines_array[i].getRawStr().empty() == true) {
            this->lines_array.erase(this->lines_array.begin() + i);
            i--;
            currentProgramAddress--;
        } 
        
        // Store user defined values into corresponding hashmaps
        else if (this->lines_array[i].is_user_defined())
        {
            // Handle constant declarations
            if (this->lines_array[i].getOpCode().get_code().compare(".EQU") == 0)
            {
                // Fetch key value pair
                auto user_key = this->lines_array[i].getOperands()[0].get()->getRaw();
                auto user_value = this->lines_array[i].getOperands()[1].get()->getRaw();

                // Store in hashmap
                // const_hashmap.insert(user_key, user_value);

                // Remove line from array
                this->lines_array.erase(this->lines_array.begin() + i);
                i--;
                currentProgramAddress--;
            } 
            // Handle label definitions
            else if (this->lines_array[i].getOpCode().get_code().back() == ':')
            {
                // Handle text section label
                if (this->lines_array[i].getSection().compare(".text") == 0) {
                    // Fetch key value pair
                    auto user_key = this->lines_array[i].getOpCode().get_code().substr(0, this->lines_array[i].getOpCode().get_code().size()-2);
                    auto user_value = std::to_string(currentProgramAddress);

                    // Store in hashmap
                    // const_hashmap.insert(user_key, user_value);
                } 
                // Handle data section label
                else if (this->lines_array[i].getSection().compare(".data") == 0) {
                    // Fetch key value pair
                    auto user_key = this->lines_array[i].getOpCode().get_code().substr(0, this->lines_array[i].getOpCode().get_code().size()-2);
                    auto user_value = std::to_string(currentDataAddress);

                    // Update data addresses
                    currentDataAddress++;

                    // Store in hashmap
                    // const_hashmap.insert(user_key, user_value);
                }
                
                
            }
            
        }
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
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << outputFilePath << std::endl;
        return EventEnum::FILE_NOT_FOUND;
    }

    for (const auto& line : this->lines_array) {
        // Translate instruction
        outputFile << line.to_pichex() << std::endl;
    }

    outputFile.close();
    return EventEnum::SUCCESS;
}

void Translator::write_output() {
    // Implementation
}

void Translator::receive_message(EventEnum event) {
    // Implementation
    this->message = event;
}

EventEnum Translator::return_message() {
    // Implementation
    return EventEnum::SUCCESS;
}

EventEnum Translator::make_error_file() {
    // Implementation
    return EventEnum::SUCCESS;
}
