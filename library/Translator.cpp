// Translator.cpp
#include "Translator.hh"

// Messaging events
#include "EventEnum.hh"

// Structures
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

// C utils
#include <stdexcept>
#include <cctype>


// Math utils
#include <cmath>
#include <algorithm>

// String utils
#include <string>
#include <string.h>

// Streams
#include <iostream>
#include <fstream>
#include <sstream>


// Initialize maps
std::unordered_map<std::string, std::string> Translator::text_label_hashmap = {};
std::unordered_map<std::string, std::string> Translator::data_label_hashmap = {};
std::unordered_map<std::string, std::string> Translator::const_hashmap = {};
// std::unordered_map<std::string, Section> Translator::section_enum;
// std::unordered_map<std::string, ConstPrefix> Translator::const_prefix_enum;

// Foreward declarations
std::string evaluate_expression(const std::string &expression, const std::unordered_map<std::string, std::string> &symbol_table);

// Constructors and destructors
Translator::Translator(){}  // WE DONT NEED THIS FOO???
Translator::Translator(const std::string& inputPath, const std::string& outputPath) : 
    input_file_path(inputPath), 
    output_file_path(outputPath), 
    cur_section(".text"),
    contains_error(false) {}
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
EventEnum Translator::define_lines(const std::string& file_info, uint64_t starting_line) {
    // Error handle that the file path is valid and open
    std::string filePath = file_info;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return EventEnum::FILE_NOT_FOUND;
    }

    // Parse file line by line
    std::string lineContent;
    // MAYBE GET RID OF STARTING LINE BECAUSE IT SHOULD ALWAYS BE SET TO 0
    uint64_t lineNumber = starting_line; 
    // uint64_t file_line_number = 1; 


    while (std::getline(file, lineContent)) {
std::cout << "inside \"" << file_info << "\"'s define_lines at line "  << lineNumber << ""<< std::endl;// << file_line_number << " and array has: " << lineNumber << "\n"<< std::endl;

        // ".include" is an important pseudo op and must be handled first
        std::istringstream iss(lineContent);
        std::string word;
        iss >> word;
// std::cout << "\topened iss steam about to test for include\n" << std::endl;
        if(word == ".include") {
// std::cout << "\tfound include" << std::endl;
            std::string includeFile;

            iss >> includeFile;
            if(!includeFile.empty()) {
                // Remove quotes if present
                if(includeFile.front() == '"' && includeFile.back() == '"') {
                    includeFile = includeFile.substr(1, includeFile.size() - 2);
                }
printf("\t\tBefore include recursion we have %zu lines\n", this->lines_array.size());
                define_lines(includeFile, 1); // Recursive call to include the file
printf("\t\tAfter include recursion we have %zu lines\n", this->lines_array.size());
            }
        } 
        // Other urgent speudo ops are the section modifiers but those can be implemented later
        else if((word.compare(".text")==0) || (word.compare(".data")==0) || (word.compare(".info")==0)) {
std::cout << "\tmatched with either text or data\n" << std::endl;
            this->cur_section = word;
        } 
        
// std::cout << "\tnot pseudo about to make the line\n" << std::endl;
        // Now we must decide if we should attempy to init the line
        else if (!lineContent.empty() && !word.empty() && word.at(0) != ';') {

// printf("\tLine preview: \n\t\tlineN:%ld,\n\t\tsec:%s,\n\t\tline:%s,\n\t\tfile:%s,\n\t\tWORD:%s\n", lineNumber, this->cur_section.c_str(), lineContent.c_str(), this->input_file_path.c_str(), word.c_str());
            std::shared_ptr<Line> line = std::make_shared<Line>(lineNumber, this->cur_section, lineContent, file_info);
std::cout << "\tDecided to make the line: |" << line->no_comments << "|\n" << std::endl;
            // We must also decide if we should put the line in our array IDEALLY COMBINE THESE
            if (!line->no_comments.empty()) {
            this->lines_array.push_back(std::move(line));
// std::cout << "\tpushed that shit into the array" << std::endl;
            }
        }
        // Increment file line number
        lineNumber++;
    }

    return EventEnum::SUCCESS;
}

EventEnum Translator::first_pass() {
    // Init address counters to 0
    uint64_t currentProgramAddress = 0;
    uint64_t currentDataAddress = 0;

std::cout << "\n\n\nInside first pass\n" << std::endl;

    // Make sure that section is defined
    //UNTIL WE INPLEMENT PSEUDO OPS LETS DEFAULT SECTION TO .data
    this->cur_section = ".text";
    if (this->cur_section.compare("")==0) {
        this->contains_error = true;
        this->error_message = "Section is not defined!";
        return EventEnum::FILE_FORMAT_ERROR;
    }

    // Loop through each line
    for (size_t i = 0; i < this->lines_array.size(); ++i) {
// std::cout << "First pass PC: " << i << std::endl;
std::cout << "Lines in line array: " << this->lines_array.size() << "" << std::endl;
        // Remove empty or commented out lines from the array
        if (this->lines_array[i]->get_raw_line().empty() == true) {
            this->lines_array.erase(this->lines_array.begin() + i);
            i--;
            currentProgramAddress--;
std::cout << "Removed line in first pass for being empty\n" << std::endl;
        } 
        
        // Store user defined values into corresponding hashmaps
        else if (this->lines_array[i]->get_contains_user_defined())
        {
std::cout << "\tSomething was user defined" << std::endl;
// printf("\t\traw line: %s\n\t\tstripped line: %s\n\t\tline number: %ld\n\t\topcode: %s\n", this->lines_array[i]->raw_line.c_str(), this->lines_array[i]->no_comments.c_str(), this->lines_array[i]->line_number, this->lines_array[i]->opcode->code_str.c_str());
// for (size_t j = 0; j < this->lines_array[i]->operands.size(); j++) {
//     printf("\t\toperand %zu: %s\n", j, this->lines_array[i]->operands[j]->get_raw().c_str());
// }

// std::cout << "\tOPCODE was user defined:" << this->lines_array[i]->get_opcode().get_is_user_defined() << std::endl;


            // Handle constant declarations
            if (this->lines_array[i]->get_opcode().get_code_str().compare(".EQU") == 0
                || this->lines_array[i]->get_opcode().get_code_str().compare(".equ") == 0)
            {
std::cout << "\t\tit was a constant" << std::endl;
                // Fetch key value pair
                std::string user_key = this->get_lines_array()[i]->get_operands()[0]->get_raw();
// std::cout << "proposed key: " << user_key << std::endl;
                std::string user_value = this->get_lines_array()[i]->get_operands()[1]->get_raw();
// std::cout << "proposed val: " << user_value << std::endl;
                // Make sure that the value is in terms of another predefined value
                if (const_hashmap.find(user_value) != const_hashmap.end()) {
                    // If user_value is found in the map, use the mapped value
                    std::string actual_value = const_hashmap[user_value];
std::cout << "Predefined value found: " << actual_value << std::endl;

                    // You can now use actual_value for further processing
                    // For example, updating the user_value with actual_value
                    user_value = actual_value;
                } else {
                    // Handle expressions

                    // First handle the first operand
                    if (this->get_lines_array()[i]->get_operands()[0]->get_is_expression()) {
// std::cout << "EXPRESSION befor: " << this->get_lines_array()[i]->get_operands()[0]->get_raw() << std::endl;
                        // Split the expression
                        std::vector<std::string> words = split_string(this->get_lines_array()[i]->get_operands()[0]->get_raw(), ' ');
                        // Substitute expression elements with defined symbol table values
                        for (auto& word : words) {
                            if (const_hashmap.find(word) != const_hashmap.end()) {
                                word = const_hashmap.at(word);
                            }
                        }

                        // Update the operand
                        this->get_lines_array()[i]->get_operands()[0]->set_raw(join_strings(words, " "));
                        // this->get_lines_array()[i]->get_operands()[0]->parseRawToBinary();
// std::cout << "EXPRESSION after: " << this->get_lines_array()[i]->get_operands()[0]->get_raw() << std::endl;

                        // Update the key-value pair
                        user_key = this->get_lines_array()[i]->get_operands()[0]->get_raw();
                        // VALUE DOES NOT NEED UPDATING IN THIS CASE user_value = NEW;
                    }
                    
                    // First handle the first operand
                    if (this->get_lines_array()[i]->get_operands()[1]->get_is_expression()) {
// std::cout << "EXPRESSION befor: " << this->get_lines_array()[i]->get_operands()[1]->get_raw() << std::endl;
                        // Split the expression
                        std::vector<std::string> words = split_string(this->get_lines_array()[i]->get_operands()[1]->get_raw(), ' ');
                        // Substitute expression elements with defined symbol table values
                        for (auto& word : words) {
                            if (const_hashmap.find(word) != const_hashmap.end()) {
                                word = const_hashmap.at(word);
                            }
                        }
                        // Update the operand
                        this->get_lines_array()[i]->get_operands()[1]->set_raw(join_strings(words, " "));
                        // this->get_lines_array()[i]->get_operands()[1]->parseRawToBinary();
// std::cout << "EXPRESSION after: " << this->get_lines_array()[i]->get_operands()[1]->get_raw() << std::endl;

                        // Update the key-value pair
                        // KEY DOES NOT NEED UPDATING IN THIS CASE
                        user_value = this->get_lines_array()[i]->get_operands()[1]->get_raw();
                    }

std::cout << "\tNo predefined value found OR EXPRESSION HANDLED for: " << user_value << std::endl;
                }

                // Store in hashmap
                const_hashmap.insert(std::make_pair(user_key, user_value));
std::cout << "\tHashmap value stored: " << user_key << " maps to " << user_value << std::endl;
                // Remove line from array
std::cout << "\tremoving line: " << i << std::endl;
                this->lines_array.erase(this->lines_array.begin() + i);
                i--;
                continue;
                
                // currentProgramAddress -= 2;

            } 
            // Handle label definitions
            else if (this->lines_array[i]->get_opcode().get_is_user_defined()) //USED TO BE  OPCODE.get_code_str().back() == ':'
            {   // Only labels have user defined opcodes
// std::cout << "\t\twe are now testing for section labels. We have: " << this->lines_array[i]->get_section()<< std::endl;
                // Handle text section label
                if (this->lines_array[i]->get_section().compare(".text") == 0) {
// std::cout << "\t\tit was a text section label\n" << std::endl;
                    // Fetch key value pair
                    std::string user_key = this->lines_array[i]->get_opcode().get_code_str().substr(0, this->lines_array[i]->get_opcode().get_code_str().size()-1);
                    std::string user_value = std::to_string(currentProgramAddress);
                    
                    // Store in hashmap
                    const_hashmap.insert(std::make_pair(user_key, user_value));
// std::cout << "Hashmap value stored: " << user_key << " maps to " << user_value << std::endl;

                } 
                // Handle data section label
                else if (this->get_lines_array()[i]->get_section().compare(".data") == 0) {
// std::cout << "\t\tit was a data section label\n" << std::endl;
                    // Fetch key value pair
                    std::string user_key = this->get_lines_array()[i]->get_opcode().get_code_str().substr(0, this->lines_array[i]->get_opcode().get_code_str().size()-1);
                    std::string user_value = std::to_string(currentDataAddress);

                    // Update data addresses by one byte
                    currentDataAddress++;

                    // Store in hashmap
                    const_hashmap.insert(std::make_pair(user_key, user_value));
// std::cout << "Hashmap value stored: " << user_key << " maps to " << user_value << std::endl;

                }

                // Remove line from array
// std::cout << "removing lines" << std::endl;
                this->lines_array.erase(this->lines_array.begin() + i);
                i--;
                continue;
                
            }
            
        }
        else
        {
            // This runs if not emppy and not user defed
        }
        
        // Store program address value in line
        this->lines_array[i]->set_memory_address(currentProgramAddress);

        // After every instruction, increment the address by two bytes
        currentProgramAddress += 2;

        // std::cout << "Address: " << lines[i].getAddress() << " Content: " << lines[i].getContent() << std::endl;
    }    
    // Optionally, you can print the symbol table for debugging
    // for (const auto& symbol : symbolTable) {
    //     std::cout << "Label: " << symbol.first << " Address: " << symbol.second << std::endl;
    // }
    
    return EventEnum::SUCCESS;
}

EventEnum Translator::second_pass() {
printf("\n\n\nSECOND PASS START:\n");

    // Check to make sure that the output file is valid
    std::ofstream outputFile(this->output_file_path);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << this->output_file_path << std::endl;
        return EventEnum::FILE_NOT_FOUND;
    }

    // The start of hex files should be an extended linear address record
    // The standard format is :02000004AAAACC
    // - : required start of all lines
    // - 02 2 bytes of address data 
    // - 0000 address section, must be zero
    // - 04 denotes the extended linear addresss data
    // - AAAA actual extended linear address
    // - CC checksum
    // For PIC we can use :020000040000FA
    outputFile << ":020000040000FA" << std::endl;    

    for (const auto& line : this->lines_array) {
printf("\tevaling line %ld in file %s: %s\n", line->get_line_number(), line->get_file_name().c_str(), line->get_raw_line().c_str());
        // Before translating, expressions must be resolved
        for (const auto& operand : line->get_operands()) {
printf("\t\tevaling operand %s with bin %s\n", operand->get_raw().c_str(), operand->get_binary().c_str());
            if (operand->get_is_expression()) {
printf("It was an expression\n");
                try {
                    operand->set_raw(evaluate_expression(operand->get_raw(), this->const_hashmap));
printf("raw changed to %s\n", operand->get_raw().c_str());
                    operand->set_is_expression(false);

                    // DONT FORGET TO UPDATE THE BIN
                    operand->parseRawToBinary();

                } catch (const std::exception &e) {

                    std::cerr << "Error evaluating expression: " << operand->get_raw() << " - " << e.what() << std::endl;
                }
            }
        }

        // Translate instruction
        outputFile << line->to_pichex(const_hashmap) << std::endl;
    }

    // Hex files must end with ":00000001FF" by convention
    // This is called the end of file record
    outputFile << ":00000001FF" << std::endl;
    outputFile.close();
    return EventEnum::SUCCESS;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

std::string evaluate_expression(const std::string &expression, const std::unordered_map<std::string, std::string> &symbol_table) {
    std::stack<int> values;
    std::stack<char> operators;

    auto apply_operator = [](std::stack<int> &values, char op) {
        int b = values.top(); values.pop();
        int a = values.top(); values.pop();
        switch (op) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/': values.push(a / b); break;
        }
    };

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isspace(ch)) {
            continue;
        } else if (isdigit(ch)) {
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                ++i;
            }
            --i;
            values.push(value);
        } else if (isalpha(ch)) {
            std::string symbol;
            while (i < expression.length() && (isalnum(expression[i]) || expression[i] == '_')) {
                symbol += expression[i];
                ++i;
            }
            --i;
            if (symbol_table.find(symbol) != symbol_table.end()) {
                int value = std::stoi(symbol_table.at(symbol));
                values.push(value);
            } else {
                throw std::runtime_error("Undefined symbol: " + symbol);
            }
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                apply_operator(values, operators.top());
                operators.pop();
            }
            
            if (!operators.empty()) {
                operators.pop();
            }
        } else if (strchr("+-*/", ch)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                apply_operator(values, operators.top());
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        apply_operator(values, operators.top());
        operators.pop();
    }
    return std::to_string(values.top());
}
void Translator::write_output() {
    // Implementation
}

EventEnum Translator::handle_message(EventEnum event) {
    // Implementation
    this->message = event;
    return EventEnum::SUCCESS;
}

void Translator::reset() {
    this->input_file_path.clear();
    this->output_file_path.clear();
    this->error_file_path.clear();
    this->cur_section = ".text";
    this->message = EventEnum::SUCCESS;
    this->error_message.clear();
    this->contains_error = false;
    this->lines_array.clear();

    this->text_label_hashmap.clear();
    this->data_label_hashmap.clear();
    this->const_hashmap.clear();
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
