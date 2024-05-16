#include "UI.hh"

int main() {
    UI ui;
    EventEnum event;
    do {
        event = ui.parse_request();
        ui.set_response(event);
    } while (event != EventEnum::SUCCESS || event != EventEnum::OTHER_ERROR);
    return 0;
}
