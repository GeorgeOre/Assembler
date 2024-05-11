# {[(	Compiler and Linker Settings	)]}

# C Compiler
CC := gcc
# C++ Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -Wall -Wextra -O3 -g #-std=c++11
# Linker flags
LDFLAGS := -lm  # Example of additional linker flags if needed


# {[(	Main Project Config	)]}

# Output directory for object files
OBJ_DIR := obj
# Source files
SRCS := $(wildcard *.cpp)
# Create object file paths
OBJS := $(OBJ_DIR)/$(subst .cpp,.o,$(notdir $(SRCS)))
# Create the name of the assembler executable
EXEC := assembler

# {[(	Test Configs	)]}

# Test files directory
TEST_DIR := Tests
# Build test source files
TEST_SRC := $(wildcard $(TEST_DIR)/*.cpp)
# Build test object files
TEST_OBJ := $(OBJ_DIR)/$(subst .cpp,.o,$(notdir $(TEST_SRC)))
# Name the test executable
TEST_BIN := runtest

# Test_Operand files directory
TEST_OPERAND_DIR := Operand
# Build test source files
TEST_OPERAND_SRC := $(wildcard $(TEST_OPERAND_DIR)/*.cpp) $(wildcard $(TEST_OPERAND_DIR)/*/*.cpp)
# Build test object files
TEST_OPERAND_OBJ := $(OBJ_DIR)/$(subst .cpp,.o,$(notdir $(TEST_SRC)))
# Name the test executable
TEST_OPERAND_BIN := operand_test

# {[(	Target Configs	)]}

# Default target for the assembler
all: $(EXEC)
	./$(EXEC)
# Link the object files into the assembler
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o bins/$(EXEC) $(LDFLAGS)
# Compile source files into object files
$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS) -o $(OBJS)

# Run the test executable
test: $(TEST_BIN)
	./$(TEST_BIN)
# Link the test object files into test executable
$(TEST_BIN): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o bins/$(TEST_BIN) $(LDFLAGS)
# Compile the test source files
$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

# Run the test_operand executable
test_operand: $(TEST_BIN)
	./$(TEST_BIN)
# Link the test object files into test executable
$(TEST_BIN): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o bins/$(TEST_BIN) $(LDFLAGS)
# Compile the test source files
$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

check:
	echo $(TEST_SRC)

.PHONY: clean test all check

# Clean
clean:
	rm -f $(EXEC) $(OBJS) $(TEST_BIN) $(TEST_OBJ)









