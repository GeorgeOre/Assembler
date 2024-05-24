#include "Line.hh"
#include "B_OpCode.hh"
#include "Boperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"
#include "Koperand.hh"
#include <cassert>
#include <iostream>
#include <sstream>
#include <functional>
#include <memory>

// Function to capture output for testing
std::string captureOutput(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old_cout);
    return oss.str();
}

void test_LineInitialization() {
    Line line(1, ".text", "MOVWF 0x30", "test.asm");
    assert(line.get_line_number() == 1);
    assert(line.get_section() == ".text");
    assert(line.get_raw_line() == "MOVWF 0x30");
    assert(line.get_file_name() == "test.asm");
    assert(line.get_contains_error() == false);
    assert(line.get_contains_user_defined() == false);
    std::cout << "Line initialization tests passed!\n" << std::endl;
}

void test_LineParse() {
    Line line(1, ".text", "MOVWF 0x30", "test.asm");
    // line.parseLine();
    assert(line.get_opcode().get_code_str() == "MOVWF");
    assert(line.get_operands().size() == 1);
    assert(line.get_operands()[0]->get_raw() == "0x30");
    std::cout << "Line parse tests passed!\n" << std::endl;
}

void test_LineToPichex() {
    Line line(1, ".text", "MOVWF 0x30", "test.asm");
    line.parseLine();
    std::string pichex = line.to_pichex();
    assert(!pichex.empty()); // Assuming to_pichex() returns some valid pichex string
    std::cout << "Line to_pichex tests passed!\n" << std::endl;
}

void test_LineAccessorsAndSetters() {
    Line line(1, ".text", "MOVWF 0x30", "test.asm");
    line.set_line_number(2);
    assert(line.get_line_number() == 2);
    
    line.set_memory_address(100);
    assert(line.get_memory_address() == 100);
    
    line.set_file_name("new_test.asm");
    assert(line.get_file_name() == "new_test.asm");
    
    line.set_section(".data");
    assert(line.get_section() == ".data");
    
    line.set_raw_line("MOVF 0x40");
    assert(line.get_raw_line() == "MOVF 0x40");
    
    line.set_contains_error(true);
    assert(line.get_contains_error() == true);
    
    line.set_contains_user_defined(true);
    assert(line.get_contains_user_defined() == true);
    
    line.set_error_message("Test error");
    assert(line.get_error_message() == "Test error");
    
    std::cout << "Line accessors and setters tests passed!\n" << std::endl;
}

int main() {
    std::cout << "Line tests start!\n" << std::endl;

    test_LineInitialization();
    test_LineParse();
    test_LineToPichex();
    test_LineAccessorsAndSetters();

    std::cout << "All Line tests passed!\n" << std::endl;
    return 0;
}


// // LineTest.cpp
// #include <iostream>
// #include <vector>
// #include <memory>
// #include <cassert>
// #include <functional>
// #include <sstream>

// #include "Line.hh"
// #include "OpCode.hh"
// #include "Boperand.hh"

// // Function to capture output for testing
// std::string captureOutput(std::function<void()> func) {
//     std::ostringstream oss;
//     std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
//     func();
//     std::cout.rdbuf(old_cout);
//     return oss.str();
// }

// void test_LineInitialization() {
//     std::cout << "Starting test_LineInitialization" << std::endl;

//     Line line(1, ".text", "MOVWF 0x20", "test.asm");

//     assert(line.getLineNumber() == 1);
//     assert(line.getSection() == ".text");
//     // std::cout << line.hasError() << !line.hasError() << std::endl;
//     assert(!line.hasError());

//     std::cout << "test_LineInitialization passed!" << std::endl;
// }

// void test_LineParsing() {
//     std::cout << "Starting test_LineParsing" << std::endl;

//     Line line(2, ".text", "MOVWF 0x20", "test.asm");

//     // std::cout << line.getOpCode().get_code() << std::endl;
//     // std::cout << line.getOperands().size() << std::endl;
//     // std::cout << line.getOperands()[0]->getRaw() << std::endl;

//     assert(line.getOpCode().get_code() == "MOVWF");
//     assert(line.getOperands().size() == 1);
//     assert(line.getOperands()[0]->getRaw() == "0x20");

//     std::cout << "test_LineParsing passed!" << std::endl;
// }

// void test_LineErrorHandling() {
//     std::cout << "Starting test_LineErrorHandling" << std::endl;

//     Line line(3, ".text", "INVALID_OP 0x20", "test.asm");

//     assert(line.hasError());

//     // std::cout << line.getErrorMessage() << "<ERR: " << line.getErrorMessage().compare("Unknown opcode: INVALID_OP") << std::endl;
    
//     assert(line.getErrorMessage().compare("Unknown opcode: INVALID_OP") == 0);

//     std::cout << "test_LineErrorHandling passed!" << std::endl;
// }

// void test_LineGetters() {
//     std::cout << "Starting test_LineGetters" << std::endl;

//     // Line line(4, ".data", "MYVAR .EQU 10");
//     Line line(4, ".data", "MOVWF 0x20", "test.asm");


//     assert(line.getLineNumber() == 4);
//     assert(line.getSection() == ".data");
    
//     std::cout << line.getOpCode().get_code() << "YOOO" << std::endl;
    
    
//     assert(line.getOpCode().get_code() == "MOVWF");
//     assert(line.getOperands().size() == 1);
//     assert(line.getOperands()[0]->getRaw() == "0x20");

//     std::cout << "test_LineGetters passed!" << std::endl;
// }

// int main() {
//     std::cout << "Line tests start!" << std::endl;

//     test_LineInitialization();
//     test_LineParsing();
//     test_LineErrorHandling();
//     test_LineGetters();

//     std::cout << "All Line tests passed!" << std::endl;
//     return 0;
// }
