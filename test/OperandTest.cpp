#include <iostream>
#include <vector>
#include "Operand.hh"
#include "Boperand.hh"
#include "Koperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"

int main() {
    // Create a vector of Operand pointers
    std::vector<Operand*> operandList;

    // Add different types of operands to the list
    operandList.push_back(new Boperand("B_raw_data"));
    operandList.push_back(new Koperand("K_raw_data"));
    operandList.push_back(new Doperand("D_raw_data"));
    operandList.push_back(new Foperand("F_raw_data"));

    // Iterate over the list and call a method on each operand
    for (Operand* operand : operandList) {
        operand->printValue();
        std::cout << "Size: " << operand->getSize() << " bits" << std::endl;
        std::cout << "Raw: " << operand->getRaw() << std::endl;
        std::cout << "Binary: " << operand->getBinary() << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

    // Clean up: delete each operand to avoid memory leaks
    for (Operand* operand : operandList) {
        delete operand;
    }

    return 0;
}
