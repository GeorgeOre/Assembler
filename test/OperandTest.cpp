#include <iostream>
// #include <vector>
#include <list>

#include "Operand.hh"
#include "Boperand.hh"
#include "Koperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"


void test_parent_operand_constructor() {
    std::cout << "Testing parent constructor:" << std::endl;

    // Create a dummy OpCode object
    OpCode code;

    // Create a list of operands
    list<Operand> operandList;

    // Add different types of operands to the list
    operandList.push_back(new Boperand(code, "B_raw_data"));
    operandList.push_back(new Koperand(code, "K_raw_data"));
    operandList.push_back(new Doperand(code, "D_raw_data"));
    operandList.push_back(new Foperand(code, "F_raw_data"));

    // Print the value of each operand
    for (Operand* operand : operandList) {
        operand->printValue();
    }

    // Clean up

    printf("omg test is done\n");


    // std::cout << "Hex: " << (opcode.get_hex().empty() ? "Pass" : "Fail") << std::endl;
    // std::cout << "Code: " << (opcode.get_code().empty() ? "Pass" : "Fail") << std::endl;
    // std::cout << "Operands: " << (opcode.get_operands().empty() ? "Pass" : "Fail") << std::endl;
    // std::cout << "Format: " << (opcode.get_format().empty() ? "Pass" : "Fail") << std::endl;
    
    std::cout << "Parent constructor SUCCESS!!" << std::endl;
}

void test_children_opereand_constructor() {
    std::cout << "Testing parent constructor:" << std::endl;
    // Create a dummy OpCode object
    OpCode code;

    // Create a list of operands
    list<Operand> operandList;

    // Add different types of operands to the list
    operandList.push_back(new Boperand(code, "B_raw_data"));
    operandList.push_back(new Koperand(code, "K_raw_data"));
    operandList.push_back(new Doperand(code, "D_raw_data"));
    operandList.push_back(new Foperand(code, "F_raw_data"));

    // Print the value of each operand
    for (Operand* operand : operandList) {
        operand->printValue();
    }
    std::cout << "Children constructor SUCCESS!!" << std::endl;
}

void run_all_tests() {
    test_parent_operand_constructor();
    test_children_operand_constructor();
}

int main() {
    run_all_tests();
    return 0;
}

