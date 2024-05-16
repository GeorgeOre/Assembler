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
