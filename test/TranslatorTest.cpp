#include <iostream>
#include "Translator.hh"
#include "Line.hh"
#include "OpCode.hh"
#include "ALU_OpCode.hh"
#include <cassert>
#include <sstream>
#include <functional>

// Function to capture output for testing
std::string capture_output(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old_cout);
    return oss.str();
}

void test_translator_initialization() {
    Translator translator("input.txt", "output.txt");

    assert(translator.get_input_file_path() == "input.txt");
    assert(translator.get_output_file_path() == "output.txt");
    assert(translator.get_cur_section().empty());
    assert(!translator.get_contains_error());

    std::cout << "Translator initialization tests passed!\n" << std::endl;
}

void test_define_lines() {
    Translator translator("input.txt", "output.txt");
    std::ofstream test_file("input.txt");
    test_file << ".text\nMOVWF some_operands\n";
    test_file.close();

    EventEnum result = translator.define_lines("input.txt");
    assert(result == EventEnum::SUCCESS);
    assert(translator.get_lines_array().size() == 2);

    std::remove("input.txt");

    std::cout << "Define lines tests passed!\n" << std::endl;
}

void test_first_pass() {
    Translator translator("input.txt", "output.txt");
    std::ofstream test_file("input.txt");
    test_file << ".text\nMOVWF some_operands\n";
    test_file.close();

    translator.define_lines("input.txt");
    EventEnum result = translator.first_pass();
    assert(result == EventEnum::SUCCESS);

    std::remove("input.txt");

    std::cout << "First pass tests passed!\n" << std::endl;
}

void test_second_pass() {
    Translator translator("input.txt", "output.txt");
    std::ofstream test_file("input.txt");
    test_file << ".text\nMOVWF some_operands\n";
    test_file.close();

    translator.define_lines("input.txt");
    translator.first_pass();
    EventEnum result = translator.second_pass();
    assert(result == EventEnum::SUCCESS);

    std::ifstream output_file("output.txt");
    assert(output_file.is_open());
    std::string line;
    std::getline(output_file, line);
    assert(!line.empty());
    output_file.close();

    std::remove("input.txt");
    std::remove("output.txt");

    std::cout << "Second pass tests passed!\n" << std::endl;
}

int main() {
    std::cout << "Translator tests start!\n" << std::endl;

    test_translator_initialization();
    test_define_lines();
    test_first_pass();
    test_second_pass();

    std::cout << "All Translator tests passed!\n" << std::endl;
    return 0;
}


// #include "Translator.hh"
// #include <cassert>
// #include <iostream>
// #include <sstream>

// using namespace std;

// void test_constructor(){

//     // try {   // First we need to see that the no param constructor fails
//     //     Translator translator1();
//     //     assert(false); // If no exception is thrown, this will fail the test
//     // } catch (const std::invalid_argument& e) {
//     //     // This makes sure that the right failure was caught
//     //     assert(std::string(e.what()) == "Please make sure that you init traslator with file paths");
//     // } catch (...) {
//     //     assert(false); // If some other exception is thrown, this will fail the test
//     // }

//     // Check good inialization
//     Translator translator2("input.asm", "output.hex");
//     assert(translator2.get_asmFilePath() == "input.asm");
//     assert(translator2.get_outputFilePath() == "output.hex");

//     printf("Constructor test: PASS\n");
// }

// void test_define_lines(){
//     // Check that define lines works
//     Translator translator("input.asm", "output.hex");
//     EventEnum result = translator.define_lines("input.asm");
//     assert(result == EventEnum::SUCCESS);

//     // Check the contents to make sure they are as expected
//     // std::vector<Line> lines = translator.get_lines_array();
//     // assert(lines.empty);

//     printf("Define lines test: PASS\n");
// }

// void test_first_pass(){
//     // Check that first pass works
//     Translator translator("input.asm", "output.hex");

//     printf("First pass test: PASS\n");
// }

// void test_second_pass(){
//     // Check that second pass works
//     Translator translator("input.asm", "output.hex");
//     printf("Second pass test: PASS\n");
// }

// // void test_translate(){
// //     Translator translator("input.asm", "output.hex");
// // }

// int main() {
//     test_constructor();
//     test_define_lines();
//     test_first_pass();
//     test_second_pass();
//     // test_translate();

//     std::cout << "All Translator tests passed!" << std::endl;
//     return 0;
// }
