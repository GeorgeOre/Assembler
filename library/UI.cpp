#include "UI.hh"
#include <iostream>
#include <sstream>

// Constructor
UI::UI(const std::string& inputFilePath, const std::string& outputFilePath)
    : state(StateEnum::START), translator(inputFilePath, outputFilePath) {
    initialize_tables();
}

// Initialize the command and response tables
void UI::initialize_tables() {
    // Example commands and responses; you should expand these based on your functional specs
    command_table = {
        {"load", "Load an input file"},
        {"set_output", "Set output file path"},
        {"translate", "Translate the input file"},
        {"quit", "Quit the application"}
    };

    response_table = {
        {"SUCCESS", "Operation completed successfully."},
        {"INVALID_COMMAND", "Invalid command. Please try again."},
        {"INVALID_FILE_PATH", "Invalid file path. Please check and try again."},
        {"SYNTAX_ERROR", "Syntax error in the input file."},
        {"UNDEFINED_SYMBOL", "Undefined symbol encountered."},
        {"FILE_FORMAT_ERROR", "File format error detected."},
        {"OTHER_ERROR", "An unspecified error occurred."}
    };
}

// Get an input from the user, parse the command, and validate it
EventEnum UI::parse_request() {
    std::string input;
    std::cout << "Enter command: ";
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string command;
    iss >> command;

    if (command_table.find(command) == command_table.end()) {
        return EventEnum::INVALID_COMMAND;
    }

    if (command == "load") {
        std::string input_file;
        iss >> input_file;
        if (input_file.empty()) {
            return EventEnum::INVALID_FILE_PATH;
        }
        translator.set_input_file_path(input_file);
        state = StateEnum::WAITING_FOR_INPUT;
        return EventEnum::SUCCESS;
    } else if (command == "set_output") {
        std::string output_file;
        iss >> output_file;
        if (output_file.empty()) {
            return EventEnum::INVALID_FILE_PATH;
        }
        translator.set_output_file_path(output_file);
        state = StateEnum::WAITING_FOR_INPUT;
        return EventEnum::SUCCESS;
    } else if (command == "translate") {
        state = StateEnum::PROCESSING;
        EventEnum result = translator.define_lines();
        if (result == EventEnum::SUCCESS) {
            translator.first_pass();
            translator.second_pass();
            state = StateEnum::DONE;
        } else {
            state = StateEnum::ERROR;
        }
        return result;
    } else if (command == "quit") {
        state = StateEnum::DONE;
        return EventEnum::SUCCESS;
    }

    return EventEnum::INVALID_COMMAND;
}

// Handle the given event_enum and send the appropriate message to the user
void UI::set_response(EventEnum event) {
    std::string response = response_table[std::to_string(static_cast<int>(event))];
    std::cout << response << std::endl;
}
