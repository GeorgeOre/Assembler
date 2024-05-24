#include <iostream>
#include <string>
#include <fstream>
#include "Translator.hh"
#include "EventEnum.hh"

void printHelp() {
    printf(R"(

             ▄▄    ▄▄            ▄▄▄▄
             ██    ██            ▀▀██
             ██    ██   ▄████▄     ██      ██▄███▄
             ████████  ██▄▄▄▄██    ██      ██▀  ▀██
             ██    ██  ██▀▀▀▀▀▀    ██      ██    ██
             ██    ██  ▀██▄▄▄▄█    ██▄▄▄   ███▄▄██▀
             ▀▀    ▀▀    ▀▀▀▀▀      ▀▀▀▀   ██ ▀▀▀
                                           ██


MAIN MENU OPTIONS:
Run: Processes the input assembly file and generates the output file.
Options: Allows you to set the input and output file paths.
Help: Displays this help screen.
Exit: Closes the application.

    )");

// OLD INSTRUCTIONS
// Welcome to Use My Assembler (USA)! This program assembles source code
// from an assembly language file into a machine code output file.\n
// To use this assembler, input the following into the command line:
//     ./assemble <INPUT_FILE> <OUTPUT_FILE>\n

}

void runAssembler(Translator &translator) {
    // Check that the input file path is good

    // Create lines

    // Bruhber

    EventEnum result = translator.first_pass();
    if (result == EventEnum::SUCCESS) {
        result = translator.second_pass();
    }

    if (result == EventEnum::SUCCESS) {
        std::cout << "Translation successful! Output written to " << translator.get_output_file_path() << std::endl;
    } else {
        std::cerr << "Translation failed: " << translator.get_error_message() << std::endl;
    }
}

int main() {
    Translator translator;

    std::string inputPath;
    std::string outputPath;
    bool exit = false;

    while (!exit) {
        std::cout << "----------------------------\n";
        std::cout << " Use My Assembler (USA) Menu\n";
        std::cout << "----------------------------\n";
        std::cout << "1. Run\n";
        std::cout << "2. Options\n";
        std::cout << "3. Help\n";
        std::cout << "4. Exit\n";
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (!inputPath.empty() && !outputPath.empty()) {
                    translator.set_input_file_path(inputPath);
                    translator.set_output_file_path(outputPath);
                    runAssembler(translator);
                } else {
                    std::cerr << "Please set the input and output file paths in Options first.\n";
                }
                break;
            case 2:
                std::cout << "Enter assembly file path: ";
                std::cin >> inputPath;
                std::cout << "Enter output file path: ";
                std::cin >> outputPath;
                break;
            case 3:
                printHelp();
                break;
            case 4:
                exit = true;
                break;
            default:
                std::cerr << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}


// TERMINAL MAIN (DEPRICATED)
// int main(int argc, char *argv[]) {
//     if (argc == 2){
// 		if (argv[1] == "help" or argv[1] == "-h"){
// 			print_help();
// 		}
// 		else {
// 			printf("Improper format. For help, enter './assemble help' or './assemble -h'.");
// 		}
// 		return;
// 	}
// 	if (argc == 1 or argc > 3){
// 		printf("Improper format. For help, enter './assemble help' or './assemble -h'.");
// 		return;
// 	}
// 	string inputPath = argv[1];
// 	string outputPath = argv[2];
// 	UI ui = UI(inputPath, outputPath);
// 	ui.run();


//     return 0;
// }



