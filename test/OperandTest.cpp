// Custom headers
#include "Operand.hh"

// Utils
#include <iostream>
#include <vector>
#include <string>


using namespace std;    // This is if you don't want to use ::

int main()
{
    // vector<string> msg {"This is proof that this works"};

    // for (const string& word : msg)
    // {
    //     cout << word << " ";
    // }
    // cout << endl;

    // Create an instance of Operand with int type
    Operand<int> intOperand;
    
    // Create an instance of Operand with double type
    //Operand<double> doubleOperand;

    // Example of printing value
    intOperand.printValue();
    //doubleOperand.printValue();
    return 0;

}