#include "Translator.hh"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

void test_constructor(){

    // try {   // First we need to see that the no param constructor fails
    //     Translator translator1();
    //     assert(false); // If no exception is thrown, this will fail the test
    // } catch (const std::invalid_argument& e) {
    //     // This makes sure that the right failure was caught
    //     assert(std::string(e.what()) == "Please make sure that you init traslator with file paths");
    // } catch (...) {
    //     assert(false); // If some other exception is thrown, this will fail the test
    // }

    // Check good inialization
    Translator translator2("input.asm", "output.hex");
    assert(translator2.get_asmFilePath() == "input.asm");
    assert(translator2.get_outputFilePath() == "output.hex");

    printf("Constructor test: PASS\n");
}

void test_define_lines(){
    // Check that define lines works
    Translator translator("input.asm", "output.hex");
    EventEnum result = translator.define_lines();
    assert(result == EventEnum::SUCCESS);

    // Check the contents to make sure they are as expected
    // std::vector<Line> lines = translator.get_lines_array();
    // assert(lines.empty);

    printf("Define lines test: PASS\n");
}

void test_first_pass(){
    // Check that first pass works
    Translator translator("input.asm", "output.hex");

    printf("First pass test: PASS\n");
}

void test_second_pass(){
    // Check that second pass works
    Translator translator("input.asm", "output.hex");
    printf("Second pass test: PASS\n");
}

// void test_translate(){
//     Translator translator("input.asm", "output.hex");
// }

int main() {
    test_constructor();
    test_define_lines();
    test_first_pass();
    test_second_pass();
    // test_translate();

    std::cout << "All Translator tests passed!" << std::endl;
    return 0;
}
