#ifndef UI_HH
#define UI_HH

#include <string>
#include <unordered_map>
#include "Translator.hh"
#include "EventEnum.hh"
#include "Line.hh"  // Include Line class

// Define the state_enum
enum class StateEnum {
    START,
    WAITING_FOR_INPUT,
    PROCESSING,
    ERROR,
    DONE
};

class UI {
public:
    // Constructors
    UI();

    UI(const std::string& inputFilePath, const std::string& outputFilePath);

    // General methods
    EventEnum parse_request();
    void set_response(EventEnum event);

// Launches the CLI and prompts the user for input
    void launchCLI();

    // Gets input from the user
    std::string getInput();

    // Displays help information
    void displayHelp() const;

    // Displays an error message
    void displayError() const;

    // Displays a success message
    void displaySuccess() const;

private:
    StateEnum state;
    Translator translator;
    std::unordered_map<std::string, std::string> response_table;
    std::unordered_map<std::string, std::string> command_table;

    void initialize_tables();
};

#endif
