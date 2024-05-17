#include <iostream>
#include "Line.hh"
#include "OpCode.hh"
#include "Segment.hh"
#include "Operand.hh"
#include "Boperand.hh"


int main() {
    // Create a Line object for testing
    Line line(1, "test line content", OpCode(), Segment());
    
    // Test getSize and other methods here
    std::cout << "Line created with content: " << line.get_line_content() << std::endl;
    
    // Add more tests as needed
    return 0;
}

/*
int main() {
    OpCode opcode("LOAD"); // Assuming OpCode has a constructor that takes a string
    Segment segment("segment_data"); // Assuming Segment has a constructor that takes a string
    Line line(1, "LOAD R1, #100", opcode, segment);

    // Print line details
    std::cout << "Line Number: " << line.get_line_number() << std::endl;
    std::cout << "Line Content: " << line.get_line_content() << std::endl;

    // Create operand array
    std::vector<Operand*> operands;
    operands.push_back(new Boperand("100")); // Assuming Boperand has a constructor that takes a string

    // Convert to PICHEX
    std::string pichex = line.ToPicHEX(opcode, operands);
    std::cout << "PICHEX: " << pichex << std::endl;

    // Check format
    bool is_format_correct = line.CheckFormat();
    std::cout << "Format Correct: " << (is_format_correct ? "Yes" : "No") << std::endl;

    // Clean up
    for (Operand* operand : operands) {
        delete operand;
    }

    return 0;
}
*/