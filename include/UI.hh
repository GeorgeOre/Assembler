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

    UI(string input, string output);
	void run();


private:
	string inputPath;
	string outputPath;
	void check_error(EventEnum);

};

#endif