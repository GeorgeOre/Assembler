<<<<<<< Updated upstream
/*
UseMyAssembler Object Descriptions
By Jeb Brysacz and George Ore (name of assembler is a WIP)
*/

/*  UI Class
  Description:
    This class implements the command line user interface. It is the only layer that interacts with the user as
    the assembler application runs. It contains all of the necessary logic to run the program in all possible
    states. It has access to all information necessary for state management and user interaction.
  Base Class:
    None.
*/

//Data Members:
typedef struct Line
{
  int current_state;
/*
  Description: The current state of the application.
  Applicability: Instance
  Derivability: State is derived from the user’s inputs and/or a Translator instance’s messages.
  Constraints: Must be one of the defined states. Otherwise it means undefined behavior.
  Type: state_enum
*/

  char *user_request;
/*
  Description: A message from the user attained via the terminal.
  Applicability: Instance
  Derivability: Can only be derived from user terminal input while the UI instance is in an appropriate state.
  Constraints: Only on the choice of user (must understand the functional specification).
  Type: String
*/

  char *user_response;
/*
  Description: A message to be returned to the user via the terminal.
  Applicability: Instance
  Derivability: Can be derived from the current state or from a message from a Translator instance.
  Constraints: Must be one of the predefined responses in the response_table.
  Type: String
*/

  char *state_enum;
/*
  Description: An enumerated representation of all possible states.
  Applicability: Class
  Derivability: Is predefined by assembler programmers.
  Constraints: None.
  Type: Enum
*/

  response_table
Description: A table containing every possible message to be returned to the user via the terminal.
Applicability: Class
Derivability: Values are preset by the developers of the assembler and can be found in the functional
specifications.
Constraints: Cannot be changed or accessed by the user.
Type: Hashtable

command_table
Description: A table containing all possible command input values. These are used to compare to newly
fetched user_requests.
Applicability: Class
Derivability: Values are preset by the developers of the assembler and can be found in the functional
specifications.
Constraints: Cannot be changed or accessed by the user.
Type: Hashtable

}

Constructors:


UI_init
Description: Initializes the UI instance with the default starting state.
Arguments: None.
Return Value: event_enum
Destructors:
None (command line interrupt or alt+f4).
Methods:
Accessors:
None.
Mutators:
None.
General:
parse_request
Description: Get an input from the user with STDIO. Parse the command and compare it to valid
commands in the command_table. If valid, parses the request to ensure that the arguments are valid.
Returns an appropriate event_enum.
Arguments: None.
Return Value: event_enum
Error Handling: A special event_emun will be returned in the case of an invalid command.
set_response
Description: Handles the given event_enum. If the event_enum specifies sending a message to the user,
it will send the appropriate message.
Arguments: event_enum
Return Value: void
Private:
None.
Operators:
None.
Type Conversions:
None.
Error Handling:
Certain event enumerations are defined as “error message events” which will inform the user of the error
that has occurred. The UI class is only able to detect “invalid command input” errors and invalid file path
errors. However, the other errors such as syntax errors, undefined symbol errors, and file format errors
are still returned to the user through the terminal. Those are detected by other classes but passed
through event messages.
Helper Functions:
None.
=======
#ifndef UI_HH
#define UI_HH

#include <string>
#include <unordered_map>
#include "Translator.hh"

// Define the state_enum
enum class StateEnum {
    START,
    WAITING_FOR_INPUT,
    PROCESSING,
    ERROR,
    DONE
};

// Define the event_enum
enum class EventEnum {
    SUCCESS,
    INVALID_COMMAND,
    INVALID_FILE_PATH,
    SYNTAX_ERROR,
    UNDEFINED_SYMBOL,
    FILE_FORMAT_ERROR,
    OTHER_ERROR
};

struct Line {
    StateEnum current_state;
    std::string user_request;
    std::string user_response;
};

class UI {
public:
    // Constructor
    UI();

    // General methods
    EventEnum parse_request();
    void set_response(EventEnum event);

private:
    StateEnum state;
    Translator translator;
    std::unordered_map<std::string, std::string> response_table;
    std::unordered_map<std::string, std::string> command_table;

    void initialize_tables();
};

#endif
>>>>>>> Stashed changes
