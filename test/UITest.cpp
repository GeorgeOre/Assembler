#include "UI.hh"
#include <cassert>
#include <iostream>
#include <sstream>

// Function to simulate user input for testing
void simulateInput(const std::string& input) {
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());
}

// Function to capture output for testing
std::string captureOutput(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old_cout);
    return oss.str();
}

void test_launchCLI() {
    UI ui;
    std::string output = captureOutput([&]() { ui.launchCLI(); });
    assert(output == "Assembler CLI launched. Please enter a command:\n");
}

void test_parse_request() {
    UI ui("input.asm", "output.hex");

    // Test invalid command
    simulateInput("invalid_command\n");
    EventEnum result = ui.parse_request();
    assert(result == EventEnum::INVALID_COMMAND);

    // Test load command with valid file path
    simulateInput("load valid_path.asm\n");
    result = ui.parse_request();
    assert(result == EventEnum::SUCCESS);

    // Test set_output command with valid file path
    simulateInput("set_output valid_output.hex\n");
    result = ui.parse_request();
    assert(result == EventEnum::SUCCESS);

    // Test translate command
    simulateInput("translate\n");
    result = ui.parse_request();
    assert(result == EventEnum::SUCCESS || result == EventEnum::ERROR_DETECTED);

    // Test quit command
    simulateInput("quit\n");
    result = ui.parse_request();
    assert(result == EventEnum::SUCCESS);
}

void test_set_response() {
    UI ui;
    std::string output;

    output = captureOutput([&]() { ui.set_response(EventEnum::SUCCESS); });
    assert(output == "Operation completed successfully.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::INVALID_COMMAND); });
    assert(output == "Invalid command. Please try again.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::INVALID_FILE_PATH); });
    assert(output == "Invalid file path. Please check and try again.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::SYNTAX_ERROR); });
    assert(output == "Syntax error in the input file.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::UNDEFINED_SYMBOL); });
    assert(output == "Undefined symbol encountered.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::FILE_FORMAT_ERROR); });
    assert(output == "File format error detected.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::OTHER_ERROR); });
    assert(output == "An unspecified error occurred.\n");
}

void test_displayHelp() {
    UI ui;
    std::string output = captureOutput([&]() { ui.displayHelp(); });
    assert(output == "Help information: Use 'translate <file path>' to translate an assembly file.\nUse 'help' to display this information.\n");
}

void test_displayError() {
    UI ui;
    std::string output = captureOutput([&]() { ui.displayError(); });
    assert(output == "An error occurred. Please try again.\n");
}

void test_displaySuccess() {
    UI ui;
    std::string output = captureOutput([&]() { ui.displaySuccess(); });
    assert(output == "Operation successful.\n");
}

int main() {
    test_launchCLI();
    test_parse_request();
    test_set_response();
    test_displayHelp();
    test_displayError();
    test_displaySuccess();

    std::cout << "All UI tests passed!" << std::endl;
    return 0;
}
