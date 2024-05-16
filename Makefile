# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR)
LDFLAGS = 

# Directories
SRC_DIR = library
OBJ_DIR = out
BIN_DIR = bin
INC_DIR = include
TEST_DIR = tests
DEMO_DIR = demo

# Files
MAIN_SRC = $(DEMO_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/OperandTest.cpp
EXECUTABLE = $(BIN_DIR)/myprogram
TEST_EXECUTABLE = $(BIN_DIR)/runtest

# Source files
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Operand specific source and object files
OPERAND_SRC_FILES = $(shell find $(SRC_DIR)/Operand -name '*.cpp')
OPERAND_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(OPERAND_SRC_FILES))

# Create the necessary directories
$(OBJ_FILES): | $(OBJ_DIR)
$(EXECUTABLE): | $(BIN_DIR)
$(TEST_EXECUTABLE): | $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/OpCode/Children
	mkdir -p $(OBJ_DIR)/OpCode/Parent
	mkdir -p $(OBJ_DIR)/Operand/Children
	mkdir -p $(OBJ_DIR)/Operand/Parent

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Target for the main executable
$(EXECUTABLE): $(OBJ_FILES) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Operand tests executable
operand_test: $(OPERAND_OBJ_FILES) $(TEST_DIR)/OperandTest.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/operand_test $^ $(LDFLAGS)

# Phony targets
.PHONY: all clean run test operand_test operand_test_run

# Default target
all: $(EXECUTABLE)

# Run the main program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Run the operand tests
operand_test_run: operand_test
	./$(BIN_DIR)/operand_test

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(EXECUTABLE) $(TEST_EXECUTABLE)
