#include <iostream>
#include <vector>
#include "Operand.hh"
#include "Boperand.hh"
#include "Koperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"

// #include "Operand/Parent/Operand.hh"
// #include "Operand/Children/Boperand.hh"
// #include "Operand/Children/Koperand.hh"
// #include "Operand/Children/Doperand.hh"
// #include "Operand/Children/Foperand.hh"

int main() {
    // Create a dummy OpCode object
    OpCode dummyOpCode;

    // Create a list of operands
    std::vector<Operand*> operandList;

    // Add different types of operands to the list
    operandList.push_back(new Boperand("B_raw_data"));
    operandList.push_back(new Koperand("K_raw_data"));
    operandList.push_back(new Doperand("D_raw_data"));
    operandList.push_back(new Foperand("F_raw_data"));

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