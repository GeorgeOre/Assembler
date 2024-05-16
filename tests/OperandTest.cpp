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
