#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}

// #include "Operand.hh"
// #include <iostream>


// // Example of using the Operand class
// int main() {
//     /*
//     // Create an instance of Operand with int type
//     Operand<int> intOperand;
    
//     // Create an instance of Operand with double type
//     Operand<double> doubleOperand;

//     // Example usage
//     intOperand.someFunction();
//     doubleOperand.someFunction();

//     // Example of printing value
//     intOperand.printValue();
//     doubleOperand.printValue();
//     */
//     return 0;
// }