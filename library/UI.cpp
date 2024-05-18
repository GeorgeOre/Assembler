#include "UI.hh"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

// Default Constructor
UI::UI(string input, string output) {
	inputPath = input;
	outputPath = output;
}

void UI::run(){
    Translator translator = Translator(inputPath, outputPath);
	EventEnum overall = EventEnum::SUCCESS;
	overall = translator.define_lines();
	if (overall != EventEnum::SUCCESS) {
		check_error(overall);
		return;
	}
	overall = translator.first_pass();
	if (overall != EventEnum::SUCCESS) {
		check_error(overall);
		return;
	}
	overall = translator.second_pass();
	if (overall != EventEnum::SUCCESS) {
		check_error(overall);
		return;
	}
	printf("-------------------------------------------------- \n");
	printf("Success! File %s has been assembled to output file %s \n", inputPath, outputPath);
	return;
}

void UI::check_error(EventEnum event){
	printf("-------------------------------------------------- \n");
	string error = "";
	switch(event){
		case EventEnum::INVALID_FILE_PATH:
			error = "Invalid File Path";
		case EventEnum::SYNTAX_ERROR:
			error = "Syntax Error";
		case EventEnum::UNDEFINED_SYMBOL:
			error = "Undefined Symbol";
		case EventEnum::FILE_FORMAT_ERROR:
			error = "File Format Error";
		default:
			error = "Unknown Error";
	}
	string message = "Error: " + error + "!";
	printf("%s \n", message);
	printf("Please see output file %s for more details. \n", outputPath);
}