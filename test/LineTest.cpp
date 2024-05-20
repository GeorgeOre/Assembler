// LineTest.cpp
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <functional>
#include <sstream>

#include "Line.hh"
#include "OpCode.hh"
#include "Boperand.hh"

// Function to capture output for testing
std::string captureOutput(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old_cout);
    return oss.str();
}

void test_LineInitialization() {
    std::cout << "Starting test_LineInitialization" << std::endl;

    Line line(1, ".text", "MOVWF 0x20");

    assert(line.getLineNumber() == 1);
    assert(line.getSection() == ".text");
    // std::cout << line.hasError() << !line.hasError() << std::endl;
    assert(!line.hasError());

    std::cout << "test_LineInitialization passed!" << std::endl;
}

void test_LineParsing() {
    std::cout << "Starting test_LineParsing" << std::endl;

    Line line(2, ".text", "MOVWF 0x20");

    // std::cout << line.getOpCode().get_code() << std::endl;
    // std::cout << line.getOperands().size() << std::endl;
    // std::cout << line.getOperands()[0]->getRaw() << std::endl;

    assert(line.getOpCode().get_code() == "MOVWF");
    assert(line.getOperands().size() == 1);
    assert(line.getOperands()[0]->getRaw() == "0x20");

    std::cout << "test_LineParsing passed!" << std::endl;
}

void test_LineErrorHandling() {
    std::cout << "Starting test_LineErrorHandling" << std::endl;

    Line line(3, ".text", "INVALID_OP 0x20");

    assert(line.hasError());

    // std::cout << line.getErrorMessage() << "<ERR: " << line.getErrorMessage().compare("Unknown opcode: INVALID_OP") << std::endl;
    
    assert(line.getErrorMessage().compare("Unknown opcode: INVALID_OP") == 0);

    std::cout << "test_LineErrorHandling passed!" << std::endl;
}

void test_LineGetters() {
    std::cout << "Starting test_LineGetters" << std::endl;

    // Line line(4, ".data", "MYVAR .EQU 10");
    Line line(4, ".data", "MOVWF 0x20");


    assert(line.getLineNumber() == 4);
    assert(line.getSection() == ".data");
    
    std::cout << line.getOpCode().get_code() << "YOOO" << std::endl;
    
    
    assert(line.getOpCode().get_code() == "MOVWF");
    assert(line.getOperands().size() == 1);
    assert(line.getOperands()[0]->getRaw() == "0x20");

    std::cout << "test_LineGetters passed!" << std::endl;
}

int main() {
    std::cout << "Line tests start!" << std::endl;

    test_LineInitialization();
    test_LineParsing();
    test_LineErrorHandling();
    test_LineGetters();

    std::cout << "All Line tests passed!" << std::endl;
    return 0;
}
