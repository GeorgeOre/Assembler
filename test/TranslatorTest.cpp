#include "Translator.hh"

int main() {
    Translator translator("input.asm", "output.hex");

    EventEnum result = translator.define_lines();
    if (result == EventEnum::SUCCESS) {
        translator.first_pass();
        translator.second_pass();
    } else {
        std::cerr << "Error occurred: " << static_cast<int>(result) << std::endl;
    }

    return 0;
}
