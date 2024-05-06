// Operand.cpp

#include "Operand.hh"
#include <iostream>

// Define constructor
template<typename O>
Operand<O>::Operand() {
    // Constructor implementation
}

// Define destructor
template<typename O>
Operand<O>::~Operand() {
    // Destructor implementation
}

// Define member function
template<typename O>
void Operand<O>::someFunction() {
    // Member function implementation
}

// Example of using the Operand class
int main() {
    // Create an instance of Operand with int type
    Operand<int> intOperand;
    
    // Create an instance of Operand with double type
    Operand<double> doubleOperand;

    // Example usage
    intOperand.someFunction();
    doubleOperand.someFunction();

    // Example of printing value
    intOperand.printValue();
    doubleOperand.printValue();

    return 0;
}
