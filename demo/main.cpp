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


int main(int argc, char *argv[]) {
    if (argc == 2){
		if (argv[1] == "help" or argv[1] == "-h"){
			print_help();
		}
		else {
			printf("Improper format. For help, enter './assemble help' or './assemble -h'.");
		}
		return;
	}
	if (argc == 1 or argc > 3){
		printf("Improper format. For help, enter './assemble help' or './assemble -h'.");
		return;
	}
	string inputPath = argv[1];
	string outputPath = argv[2];
	UI ui = UI(inputPath, outputPath);
	ui.run();


    return 0;
}


void print_help(){
	printf("------------------------------------------------------------- \n");
	printf("-----------------------------HELP---------------------------- \n");
	printf("------------------------------------------------------------- \n \n");
	printf("To use this assembler, input the following into command line: \n");
	printf("            ./assemble <INPUT_FILE> <OUTPUT_FILE>             \n");
	printf("------------------------------------------------------------- \n");

}

