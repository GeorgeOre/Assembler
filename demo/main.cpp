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