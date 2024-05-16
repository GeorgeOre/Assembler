#include <iostream>
#include "OpCode.hh"
#include "Operand.hh"
#include "Boperand.hh"

void test_op_code_default_constructor() {
    OpCode opcode("LOAD");
    std::cout << "Testing default constructor:" << std::endl;
    std::cout << "Hex: " << (opcode.get_hex().empty() ? "Pass" : "Fail") << std::endl;
    std::cout << "Code: " << (opcode.get_code().empty() ? "Pass" : "Fail") << std::endl;
    std::cout << "Operands: " << (opcode.get_operands().empty() ? "Pass" : "Fail") << std::endl;
    std::cout << "Format: " << (opcode.get_format().empty() ? "Pass" : "Fail") << std::endl;
}

void test_operand_constructor() {
    OpCode opcode("LOAD");
    Boperand boperand(&opcode, "raw_data");
    std::cout << "Testing Boperand constructor:" << std::endl;
    std::cout << "Size: " << (boperand.getSize() == 3 ? "Pass" : "Fail") << std::endl;
    std::cout << "Raw: " << (boperand.getRaw() == "raw_data" ? "Pass" : "Fail") << std::endl;
    std::cout << "Binary: " << (boperand.getBinary() == "binary_value" ? "Pass" : "Fail") << std::endl;
}

void run_all_tests() {
    test_op_code_default_constructor();
    test_operand_constructor();
    // Add more tests here as needed
}

int main() {
    run_all_tests();
    return 0;
}
