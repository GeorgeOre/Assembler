#include <iostream>
#include "UI.hh"
#include "Translator.hh"
#include "EventEnum.hh"

enum ProgramState {
    STARTUP,
    PROCESSING,
    HELP,
    ERROR,
    SUCCESS
};

int main() {
    UI ui;
    Translator translator;
    ProgramState state = STARTUP;

    while (true) {
        switch (state) {
            case STARTUP:
                ui.launchCLI();
                state = PROCESSING;
                break;

            case PROCESSING: {
                std::string command = ui.getInput();
                if (command == "help") {
                    state = HELP;
                } else if (command.substr(0, 9) == "translate") {
                    std::string asmFilePath = command.substr(10); // assuming 'translate <path>' format
                    EventEnum result = translator.translate(asmFilePath);
                    if (result == EventEnum::SUCCESS) {
                        std::cout << "Translation successful. Output file path: " << translator.getOutputFilePath() << std::endl;
                        state = SUCCESS;
                    } else {
                        std::cout << "Translation failed. See error file: " << translator.getErrorFilePath() << std::endl;
                        state = ERROR;
                    }
                } else {
                    std::cout << "Unknown command." << std::endl;
                    state = ERROR;
                }
                break;
            }

            case HELP:
                ui.displayHelp();
                state = STARTUP;
                break;

            case ERROR:
                ui.displayError();
                state = STARTUP;
                break;

            case SUCCESS:
                ui.displaySuccess();
                state = STARTUP;
                break;

            default:
                std::cerr << "Unknown state. Exiting." << std::endl;
                return 1;
        }
    }

    return 0;
}


/*
Main Loop
Here we define the pseudocode for the flow of the main loop of the program. The main loop consists of a
switch statement that executes a code based on what state the program is. Therefore, the program
operates as a state machine that changes its state according to defined events. This summary will cover
several paths that the states can flow through. For example, a successful and unsuccessful assembler
operation leads to different paths. However, they can converge to the same state later under the right
sequence of events. Also included is how the execution relies on the UI, Line, and Translator classes, as
well as some high-level descriptions of major methods in the classes.
1. User executes the assembler program. This includes instantiating the UI and translator class.
2. Startup state begins. CLI gets launched and the user is prompted for input by the UI instance.
3. Input is parsed by the UI instance. Begins processing state. Much of the input handling and parsing will
be done with the help of existing C++ libraries such as stdio. Parsed input will be stored in array format.
4. UI cross-references the parsed command and arguments with the user commands table.
5a. Begins error state. Throws error upon unknown command or undefined file path into the error state.
Wait for acknowledgement before going back to start state.
5b. If there are no errors here, continue in the processing state.
6a. Help command was parsed, displays pre-defined help output.
6b. Sends information to the translator.
7a. Receives success or error message from translator. If successful, return with a message showing
output file path. Wait for acknowledgement before going back to the start state.
7b. Error state begin. Error message was received, which includes error output file path. Report errors
thrown and give absolute file path as output to user. Wait for acknowledgement before going back to the
start state.
Translator main loop
1. Receives “translate” command executed in UI processing state. Inputs are assembly the file path and
the output file path.
2. Mutates the asm file path and, optionally, output file path attributes of itself.
3. Call the self.define_lines (see below) method.
4. Receives success or error message from define_lines. If error, returns error message. If success,
continue.
5. Success message was received. From this point on, no errors will be thrown, since all the error
handling was done in the define_lines method.
6. Calls first pass method (see below), then calls second pass method (see below).
7. Returns a success event enum message.
Define_lines method
1. Receives execution command, with input file path as argument.
2. Reads from file using ifstream library.
3. Line by line, parses line of assembly code to line class. Appends this line to translator.line_array
attribute. Does error handling for each line, reporting syntax errors, undefined symbol errors, file format
errors. Processes include lines after the end of the current one recursively.
5. Terminates with translator.line_array fully constructed, returns success or error message.
First pass method
1. Receives execution command, no arguments.
2. For each line in the list of user-defined symbol lines, define each symbol in the corresponding line
object of the line_array attribute in Translator. Handles labels depending on the section they are in.
3. Return first pass success event enum.
Second pass method
1. Receives execution command, with hex code output file as output.
2. Using ofstream library, open file.
3. For each line of the line array, look up each symbol, and translate into the corresponding hex code,
stored in a table as a translator attribute. Append each to a string, using the hex code line format as a
template. Return completed string, which is a full translation of an assembly instruction and its
argument(s).
4. Write each completed string to the output file. Returns first pass success event enum.
*/
