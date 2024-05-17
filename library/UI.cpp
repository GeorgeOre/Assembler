#include "UI.hh"
#include <iostream>
#include <sstream>

// Default Constructor
UI::UI() : state(StateEnum::START), translator("", "") {
    initialize_tables();
}

// Parameterized Constructor
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
    std::string input = getInput();
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
        translator.set_asmFilePath(input_file);
        state = StateEnum::WAITING_FOR_INPUT;
        return EventEnum::SUCCESS;
    } else if (command == "set_output") {
        std::string output_file;
        iss >> output_file;
        if (output_file.empty()) {
            return EventEnum::INVALID_FILE_PATH;
        }
        translator.set_outputFilePath(output_file);
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

// Launches the CLI and prompts the user for input
void UI::launchCLI() {
    std::cout << "Assembler CLI launched. Please enter a command:" << std::endl;
}

// Gets input from the user
std::string UI::getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// Displays help information
void UI::displayHelp() const {
    std::cout << "Help information: Use 'translate <file path>' to translate an assembly file." << std::endl;
    std::cout << "Use 'help' to display this information." << std::endl;
}

// Displays an error message
void UI::displayError() const {
    std::cout << "An error occurred. Please try again." << std::endl;
}

// Displays a success message
void UI::displaySuccess() const {
    std::cout << "Operation successful." << std::endl;
}
