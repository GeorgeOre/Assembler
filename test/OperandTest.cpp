#include <iostream>
#include <vector>
#include "Operand/Parent/Operand.hh"
#include "Operand/Children/Boperand.hh"
#include "Operand/Children/Koperand.hh"
#include "Operand/Children/Doperand.hh"
#include "Operand/Children/Foperand.hh"

int main() {
    // Create a dummy OpCode object
    OpCode dummyOpCode;

    // Create a list of operands
    std::vector<Operand*> operandList;

    // Add different types of operands to the list
    operandList.push_back(new Boperand(&dummyOpCode, "B_raw_data"));
    operandList.push_back(new Koperand(&dummyOpCode, "K_raw_data"));
    operandList.push_back(new Doperand(&dummyOpCode, "D_raw_data"));
    operandList.push_back(new Foperand(&dummyOpCode, "F_raw_data"));

    // Print the value of each operand
    for (Operand* operand : operandList) {
        operand->printValue();
    }

    // Clean up
    for (Operand* operand : operandList) {
        delete operand;
    }

    return 0;
}

/*
#include <iostream>
#include "Boperand.hh"
#include "Koperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"

void testOperand(Operand* operand) {
    //operand->printValue();
    std::cout << "Size: " << operand->getSize() << " bits" << std::endl;
    std::cout << "Raw: " << operand->getRaw() << std::endl;
    std::cout << "Binary: " << operand->getBinary() << std::endl;
    std::cout << "-----------------------" << std::endl;
}

int main() {
    Boperand b("B_raw_data");
    Koperand k("K_raw_data");
    Doperand d("D_raw_data");
    Foperand f("F_raw_data");

    std::cout << "Testing Boperand" << std::endl;
    testOperand(&b);

    std::cout << "Testing Koperand" << std::endl;
    testOperand(&k);

    std::cout << "Testing Doperand" << std::endl;
    testOperand(&d);

    std::cout << "Testing Foperand" << std::endl;
    testOperand(&f);

    return 0;
}

*/