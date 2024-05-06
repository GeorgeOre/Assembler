// Operand.hh

#ifndef Operand_HH  // Include guard to prevent multiple inclusion
#define Operand_HH



template <typename O>

// Declarations of classes, functions, and variables go here

class Operand {
private:
    // Member variables
    string Raw; //  This is the raw string that was parsed

protected:
    O value;  //  This is a polymorphism enabled representation of the value

public:
    // Constructor
    Operand();

    // Destructor
    ~Operand();

    // Member functions
    void someFunction();

    Parent(const O& val) : value(val) {}
    void printValue() {
        std::cout << "Parent value: " << value << std::endl;
    }

};

/*
Operand: part of a line
- can have differnt types
  - value operand
  - index operand
  - string operand


Operand object
	- Value string
	- Expression
	- In MyCPU Operands
		○ Define specific operand types

Opcode object
	- Knows how to generate machine code
	- Knows valid operand types
	- Search operands
		○ MyCPU first
		○ Generic second
	- Checks types

*/
#endif  // End of include guard