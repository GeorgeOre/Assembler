# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -Iinclude/OpCode/Parent -Iinclude/OpCode/Children -Iinclude/Operand/Parent -Iinclude/Operand/Children

# Directories
SRC_DIR = library
OBJ_DIR = out
BIN_DIR = bin
TEST_DIR = test

# Source files
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Test files
TEST_FILES = $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Create necessary directories
$(OBJ_FILES): | $(OBJ_DIR)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Main executable
$(BIN_DIR)/myprogram: $(OBJ_FILES) demo/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Operand test executable
$(BIN_DIR)/operand_test: $(OBJ_FILES) $(TEST_DIR)/OperandTest.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# OpCode test executable
$(BIN_DIR)/opcode_test: $(OBJ_FILES) $(TEST_DIR)/OpCodeTest.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Other test executables can be added similarly...

# Phony targets
.PHONY: all clean run test

# Default target
all: $(BIN_DIR)/myprogram $(BIN_DIR)/operand_test $(BIN_DIR)/opcode_test

# Run the main program
run: $(BIN_DIR)/myprogram
	./$(BIN_DIR)/myprogram

# Run tests
test: $(BIN_DIR)/operand_test $(BIN_DIR)/opcode_test
	./$(BIN_DIR)/operand_test
	./$(BIN_DIR)/opcode_test

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
