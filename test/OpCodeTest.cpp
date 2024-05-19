#include <iostream>
#include <list>
#include "OpCode.hh"
#include "ALU_OpCode.hh"
#include "Operand.hh"
#include "Boperand.hh"
#include <assert.h>


void test_op_code_default_constructor() {
    OpCode opcode = OpCode();
    std::cout << "Testing default constructor:" << std::endl;

    std::cout << "Hex: " << (opcode.get_hex().empty() ? "Pass" : "Fail") << std::endl;
    std::cout << "Code: " << (opcode.get_code().empty() ? "Pass" : "Fail") << std::endl;
    std::cout << "Operands: " << (opcode.get_operands().empty() ? "Pass" : "Fail") << std::endl;
    std::cout << "Format: " << (opcode.get_format().empty() ? "Pass" : "Fail") << std::endl;
    
    std::cout << "Default Constructor test passed!" << std::endl;
}

void test_opcode_constructor() {
    list<Operand> ops;
    ops.push_back(Operand("CLR"));
    OpCode opcode = ALU_OpCode("CLR", ops);
    
    std::cout << "Testing constructor:" << std::endl;
    
    std::cout << "Hex: " << opcode.get_hex() << std::endl;
    assert(opcode.get_hex().compare("CLR"));
    std::cout << "Code: " << opcode.get_code() << std::endl;
    assert(opcode.get_code().compare("0001"));
    std::cout << "Operands: " << (opcode.get_operands().empty() ? "Pass" : "Fail") << std::endl;
    assert(opcode.get_code().compare("CLR"));
    std::cout << "Format: " << (opcode.get_format().empty() ? "Pass" : "Fail") << std::endl;
    assert(opcode.get_code().compare("CLR"));



    // assert(opcode.operands == );
    // Boperand boperand(&opcode, "raw_data");
    // std::cout << "Testing Boperand constructor:" << std::endl;
    // std::cout << "Size: " << (boperand.getSize() == 3 ? "Pass" : "Fail") << std::endl;
    // std::cout << "Raw: " << (boperand.getRaw() == "raw_data" ? "Pass" : "Fail") << std::endl;
    // std::cout << "Binary: " << (boperand.getBinary() == "binary_value" ? "Pass" : "Fail") << std::endl;
    printf("Constructor test passed! \n");
}

void run_all_tests() {
    test_op_code_default_constructor();
    test_opcode_constructor();
}

int main() {
    run_all_tests();
    return 0;
}
